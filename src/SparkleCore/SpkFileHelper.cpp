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

namespace fs = std::filesystem;

enum class SpkCompressType
{
	None,
	Zip,
};

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
	SString packPath=SWS("");
	SString localPath = SWS("");

}SpkFileBrief;


typedef struct SpkCompressData
{
	std::vector<SpkFileBrief> fileBriefs;
}SpkCompressData;

struct SpkFileHelper::Data {
	SpkCompressData compressData;

	void iterateFile(const SString& curDir, const SString& rootDir, std::function<void(const SString& file, const SString& rootPath)> iterFunc);
	void clearCompressData();
	void addFileBrief(const SpkFileBrief brief);
	
};

void SpkFileHelper::Data::clearCompressData()
{
	compressData.fileBriefs.clear();
}

void SpkFileHelper::Data::addFileBrief(const SpkFileBrief brief)
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



bool SpkFileHelper::compressDir(const SString& dir, const SString& name)
{
	bool ret=true;
	fs::path rootPath = toPathString(dir).wc_str();
	std::ofstream outStream;
	outStream.open(name.wc_str(), std::ofstream::trunc| std::ofstream::binary);

	uint64_t headerSize = 0;

	d_->clearCompressData();

	d_->iterateFile(rootPath.wstring().c_str(), rootPath.wstring().c_str(), [this, &headerSize](const SString& filePath, const SString& rootDir) {
		fs::path truePath = filePath.wc_str();
		SString fp = fs::relative(truePath, rootDir.wc_str()).wstring().c_str();
		

		SpkFileBrief brief;
		brief.header.blockSize = sizeof(SpkFileBriefHeader) + fp.toUtf8().size();
		brief.header.compressType = SpkCompressType::None;
		brief.header.compressedSize = 0;
		brief.header.startPos = 0;
		
		brief.packPath = fp;
		brief.localPath = filePath;

		d_->addFileBrief(brief);

		headerSize += brief.header.blockSize;
	});

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
		buffer = (unsigned char*)calloc(1, bufferSize);
		inputStream.seekg(0, std::ios::beg);
		inputStream.read((char*)buffer, bufferSize);
		outStream.write((char* )buffer, bufferSize);
		iter->header.compressedSize = bufferSize;

		free(buffer);
		inputStream.close();
	}

	outStream.seekp(0, std::ios::beg);
	for (auto iter = d_->compressData.fileBriefs.begin();
		iter != d_->compressData.fileBriefs.end();
		iter++)
	{
		const SByteArray& byteArr = iter->packPath.toUtf8();
		outStream.write((char*)&(iter->header), sizeof(iter->header));
		outStream.write((char*)(byteArr.data()), byteArr.size());
	}

	outStream.close();
	return ret;

}


SString SpkFileHelper::toPathString(const SString& path)
{
	std::wstring ret = path.wc_str();
	std::replace(ret.begin(), ret.end(), SWS('/'), SWS('\\'));
	return ret.c_str();
}
