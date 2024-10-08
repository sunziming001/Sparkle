#include "SpkFileHelper.h"
#include <filesystem>
#include <vector>
#include "SLogger.h"
#include <string>
#include <vector>
#include <functional>
#include <stdint.h>
#include <fstream>
#include <iostream>
#include <set>

namespace fs = std::filesystem;

enum class SpkCompressType
{
	None,
	Zip,
};

typedef struct SpkFileHeader
{
	uint32_t mask;
	uint32_t version;
	uint32_t fileCnt;
}SpkFileHeader;

typedef struct SpkFileBriefHeader
{
	uint32_t blockSize = 0;
	SpkCompressType compressType = SpkCompressType::None;
	uint64_t startPos = 0;
	uint64_t compressedSize = 0;

}SpkFileBriefHeader;

typedef struct SpkFileBrief
{
	SpkFileBriefHeader header;
	SString packPath=SWS("");			//required. 
	SString localPath = SWS("");		//only used in compress data
	SString belongPackPath = SWS("");	//only used in load data

	bool operator<(const SpkFileBrief& brief)const
	{
		return std::wstring(packPath.wc_str()) < std::wstring(brief.packPath.wc_str());
	}
}SpkFileBrief;


typedef struct SpkCompressData
{
	std::vector<SpkFileBrief> fileBriefs;
}SpkCompressData;

typedef struct SpkLoadData
{
	std::set<SpkFileBrief> fileBriefs;;
}SpkLoadData;

struct SpkFileHelper::Data {
	SpkCompressData compressData;
	SpkLoadData loadData;

	void iterateFile(const SString& curDir, const SString& rootDir, std::function<void(const SString& file, const SString& rootPath)> iterFunc);
	void clearCompressData();
	void addCompressFileBrief(const SpkFileBrief& brief);
	void addLoadFileBrief(const SpkFileBrief& brief);
	SpkFileBrief findFileBrief(const SString& resPath);
};

void SpkFileHelper::Data::clearCompressData()
{
	compressData.fileBriefs.clear();
}

void SpkFileHelper::Data::addCompressFileBrief(const SpkFileBrief& brief)
{
	compressData.fileBriefs.push_back(brief);
}

void SpkFileHelper::Data::iterateFile(const SString& curDir, const SString& rootDir, std::function<void(const SString& file, const SString& rootPath)> iterFunc)
{
	for (const auto& entry : fs::directory_iterator(curDir.wc_str()))
	{
		fs::path e = entry.path();
		if (fs::is_directory(e))
		{
			iterateFile(e.wstring().c_str(), rootDir, iterFunc);
		}
		else {
			if (iterFunc)
			{
				iterFunc(e.wstring().c_str(), rootDir);
			}

		}

	}
}

void SpkFileHelper::Data::addLoadFileBrief(const SpkFileBrief& brief)
{
	loadData.fileBriefs.insert(brief);
}

SpkFileBrief SpkFileHelper::Data::findFileBrief(const SString& resPath)
{
	SpkFileBrief ret = { 0 };
	ret.packPath = resPath;
	auto iter = loadData.fileBriefs.find(ret);
	if (iter != loadData.fileBriefs.end())
	{
		ret = *iter;
	}
	return ret;
}



SpkFileHelper* SpkFileHelper::instance=nullptr;

SpkFileHelper::SpkFileHelper()
	:d_(new Data())
{

}

SpkFileHelper::~SpkFileHelper()
{
	delete d_;
}

SpkFileHelper* SpkFileHelper::getInstance()
{
	if (nullptr == instance)
		instance = new SpkFileHelper();

	return instance;
}



bool SpkFileHelper::compressDir(const SString& dir,
	const SString& name,
	uint32_t version)
{
	bool ret=true;
	uint64_t headerSize = 0;
	fs::path rootPath = toPathString(dir).wc_str();
	std::ofstream outStream;
	SpkFileHeader fileHeader = { 0 };

	outStream.open(name.wc_str(), std::ofstream::trunc| std::ofstream::binary);
	
	//write header
	fileHeader.mask = 'SPK0';
	fileHeader.version = version;
	outStream.write((char*)&fileHeader, sizeof(SpkFileHeader));


	d_->clearCompressData();
	d_->iterateFile(rootPath.wstring().c_str(), rootPath.wstring().c_str(), [this, &headerSize, &fileHeader](const SString& filePath, const SString& rootDir) {
		fs::path truePath = filePath.wc_str();
		SString fp = fs::relative(truePath, rootDir.wc_str()).wstring().c_str();
		

		SpkFileBrief brief;
		brief.header.blockSize = sizeof(SpkFileBriefHeader) + fp.toUtf8().size();
		brief.header.compressType = SpkCompressType::None;
		brief.header.compressedSize = 0;
		brief.header.startPos = 0;
		
		brief.packPath = fp;
		brief.localPath = filePath;

		d_->addCompressFileBrief(brief);

		headerSize += brief.header.blockSize;
		fileHeader.fileCnt += 1;
	});

	//write empty file content header
	outStream << outStream.width(headerSize);

	//write file content
	for (auto iter = d_->compressData.fileBriefs.begin();
		iter != d_->compressData.fileBriefs.end();
		iter++)
	{
		unsigned char* buffer = nullptr;
		uint64_t bufferSize = 0;
		std::ifstream inputStream;

		iter->header.startPos = outStream.tellp();

		inputStream.open(iter->localPath.wc_str(), std::ifstream::binary);
		inputStream.seekg(0, std::ios::end);
		

		bufferSize = inputStream.tellg();
		buffer = (unsigned char*)calloc(1, (size_t)bufferSize);
		inputStream.seekg(0, std::ios::beg);
		inputStream.read((char*)buffer, bufferSize);
		outStream.write((char* )buffer, bufferSize);
		iter->header.compressedSize = bufferSize;

		free(buffer);
		inputStream.close();
	}

	//write file content header
	outStream.seekp(0, std::ios::beg);

	outStream.write((char*)&fileHeader, sizeof(SpkFileHeader));

	for (auto iter = d_->compressData.fileBriefs.begin();
		iter != d_->compressData.fileBriefs.end();
		iter++)
	{
		SByteArray byteArr = iter->packPath.toUtf8();
		outStream.write((char*)&(iter->header), sizeof(iter->header));
		outStream.write((char*)(byteArr.data()), byteArr.size());
	}

	outStream.close();
	return ret;

}


bool SpkFileHelper::loadPackage(const SString& packagePath)
{
	bool ret = true;
	
	std::ifstream inStream;
	SpkFileHeader fileHeader = { 0 };

	inStream.open(packagePath.wc_str(), std::ifstream::binary);
	inStream.read((char*)&fileHeader, sizeof(fileHeader));

	for (uint32_t i = 0; i < fileHeader.fileCnt; i++)
	{
		SpkFileBrief brief;
		char* buff = nullptr;
		size_t buffSize = 0;
		inStream.read((char*)&(brief.header), sizeof(brief.header));
		buffSize = brief.header.blockSize - sizeof(SpkFileBriefHeader);
		buff = (char*)calloc(1, buffSize+1);

		inStream.read(buff, buffSize);
		brief.packPath = SString(buff,buffSize);
		brief.belongPackPath = packagePath;

		d_->addLoadFileBrief(brief);
		free(buff);
	}

	inStream.close();
	return ret;
}

SByteArray SpkFileHelper::getRes(const SString& path)
{
	std::ifstream inStream;
	SpkFileBrief brief = d_->findFileBrief(path);
	SByteArray ret(brief.header.compressedSize);

	inStream.open(brief.belongPackPath.wc_str(), std::ifstream::binary);
	inStream.seekg(brief.header.startPos, std::ios_base::beg);
	inStream.read((char*)ret.data(), brief.header.compressedSize);
	return ret;
}

SString SpkFileHelper::toPathString(const SString& path)
{
	std::wstring ret = path.wc_str();
	std::replace(ret.begin(), ret.end(), SWS('/'), SWS('\\'));
	return ret.c_str();
}
