#ifndef SLOGGER_H
#define SLOGGER_H

#include "SConfig.h"
#include "SString.h"

enum class SLoggerLevel
{
	Fatal,
	Error,
	Info,
	Debug,
	Trace,
};

struct SLoggerConf
{
	SString path=SWS("./log/game/");
	SString name=SWS("sparkle");
	int maxFileCnt = 5;
	SString logPath;
	SLoggerLevel maxLoggerLevel = SLoggerLevel::Info;
};

class SPARKLE_API SLoggerManager
{
private:
	static SLoggerManager* instance;
	SLoggerManager();
	
public:
	~SLoggerManager();
	static SLoggerManager* getInstance();
	void init(const SLoggerConf& conf = SLoggerConf());
	void writeLog(SLoggerLevel lv, SStringPtr linePtr);
	void writeLog(SLoggerLevel lv, const SString& line);
private:
	SString getFormatedTime(const wchar_t* format);
	SString levelToString(SLoggerLevel lv)const;
private:
	DECLARE_INNER_DATA(d_);
};

class SPARKLE_API SLogger
{
public:
	SLogger(SLoggerLevel lv, const SString& tag);
	~SLogger();
	SLogger& operator<<(SStringPtr line);
	SLogger& operator<<(const SString& line);
private:
	SLoggerLevel lv_;
	SString tag_;
};

#define SFatal(tag) SLogger(SLoggerLevel::Fatal, tag)
#define SError(tag) SLogger(SLoggerLevel::Error, tag)
#define SInfo(tag) SLogger(SLoggerLevel::Info, tag)
#define SDebug(tag) SLogger(SLoggerLevel::Debug, tag)
#define STrace(tag) SLogger(SLoggerLevel::Trace, tag)

#endif