#include "SLogger.h"
#include <filesystem>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>


SLoggerConf::SLoggerConf(const SLoggerConf& conf)
{
	path = conf.path;
	name = conf.name;
	maxFileCnt = conf.maxFileCnt;
	logPath = conf.logPath;
	maxLoggerLevel = conf.maxLoggerLevel;
}

SLoggerConf::SLoggerConf()
{
	path = SWS("./log/game/");
	name = SWS("sparkle");
	maxFileCnt = 5;
	maxLoggerLevel = SLoggerLevel::Info;
}

SLoggerConf& SLoggerConf::operator=(const SLoggerConf& conf)
{
	path = conf.path;
	name = conf.name;
	maxFileCnt = conf.maxFileCnt;
	logPath = conf.logPath;
	maxLoggerLevel = conf.maxLoggerLevel;
	return *this;
}

struct SLoggerManager::Data
{
	SLoggerConf conf;
	std::wofstream outFileStream;
};

SLoggerManager* SLoggerManager::instance=nullptr;

SLoggerManager::SLoggerManager()
	:d_(new Data())
{

}



SLoggerManager::~SLoggerManager()
{
	delete d_;
}

SLoggerManager* SLoggerManager::getInstance()
{
	if (nullptr == instance)
	{
		instance = new SLoggerManager;
	}
	return instance;
}

void SLoggerManager::init(const SLoggerConf& conf)
{
	d_->conf = conf;
	std::filesystem::path p =(wchar_t*) (d_->conf.path.toByteArray().data());
	bool created = std::filesystem::create_directories(p);
	std::vector<std::wstring> existFiles;

	int curCnt = 0;
	for (const auto& entry : std::filesystem::directory_iterator(p))
	{
		existFiles.push_back(entry.path().wstring());
	}
	std::sort(existFiles.begin(), existFiles.end(), [](const std::wstring& s1, const std::wstring& s2)->bool {
		return s1 > s2;
		});
	for (auto iter = existFiles.begin();
		iter != existFiles.end();
		iter++)
	{
		if (iter->find((const wchar_t*)d_->conf.name.toByteArray().data()) != std::wstring::npos)
		{
			curCnt++;
		}

		if (curCnt >= d_->conf.maxFileCnt)
		{
			std::filesystem::remove(*iter);
		}
		
	}
	d_->conf.logPath = d_->conf.path;
	d_->conf.logPath << SWS("/");
	d_->conf.logPath << d_->conf.name;
	d_->conf.logPath << getFormatedTime(SWS("_%Y_%m_%d_%H_%M_%S"));
	d_->conf.logPath << SWS(".txt");

	d_->outFileStream.open((wchar_t*)d_->conf.logPath.toByteArray().data());
	d_->outFileStream.close();

}

void SLoggerManager::writeLog(SLoggerLevel lv, SStringPtr linePtr)
{
	writeLog(lv, *linePtr);
}

void SLoggerManager::writeLog(SLoggerLevel lv, const SString& line)
{
	SString out = getFormatedTime(SWS("%H:%M:%S "));
	out << levelToString(lv);
	out << SWS(" ");
	out << line;

	if (lv <= d_->conf.maxLoggerLevel)
	{
		d_->outFileStream.open((wchar_t*)d_->conf.logPath.toByteArray().data(),
			std::wofstream::app);
		d_->outFileStream << (wchar_t*)out.toByteArray().data();;
		d_->outFileStream << std::endl;
		d_->outFileStream.close();
	}
	

	std::cout<<(char*) out.toUtf8().data() << std::endl;
}

SString SLoggerManager::getFormatedTime(const wchar_t* format)
{
	wchar_t s[200];
	time_t curTime = time(nullptr);
	struct tm ctm = { 0 };
	localtime_s(&ctm, &curTime);

	
	wcsftime(s, 200, format, &ctm);

	return s;
}

SString SLoggerManager::levelToString(SLoggerLevel lv) const
{
	SString ret;
	switch (lv)
	{
	case SLoggerLevel::Fatal:
		ret << SWS("[Fatal]");
		break;
	case SLoggerLevel::Error:
		ret << SWS("[Error]");
		break;
	case SLoggerLevel::Info:
		ret << SWS("[Info]");
		break;
	case SLoggerLevel::Debug:
		ret << SWS("[Debug]");
		break;
	case SLoggerLevel::Trace:
		ret << SWS("[Trace]");
		break;
	default:
		ret << SWS("[Unknown]");
		break;
	}

	return ret;
}

SLogger::SLogger(SLoggerLevel lv, const SString& tag)
	:lv_(lv)
	,tag_(tag)
{

}

SLogger::~SLogger()
{

}

SLogger& SLogger::operator<<(SStringPtr line)
{
	(*this) << (*line);
	return *this;
}

SLogger& SLogger::operator<<(const SString& line)
{
	SLoggerManager* mgr = SLoggerManager::getInstance();
	SString tagLine = SWS("[");
	tagLine << tag_;
	tagLine << SWS("] ");
	tagLine << line;
	mgr->writeLog(lv_, tagLine);
	return *this;
}

