#ifndef _SSTRING_H
#define _SSTRING_H

#include "SConfig.h"
#include "SByteArray.h"

enum class SPARKLE_API SStringCode
{
	Unknow,
	Utf8,
	Unicode,
};

class SPARKLE_API SString
{
public:
	SString(const char * utf8Str);
	SString(const char* utf8Str, size_t len);
	SString(const wchar_t * unicodeStr);
	SString(const wchar_t* unicodeStr, size_t len);

	SString& operator=(const char* utf8Str);
	SString& operator=(const wchar_t* unicodeStr);
	

	char* c_str()const;
	wchar_t* wc_str()const;
	size_t length()const;
	~SString();
private:
	SByteArray data_;
	SStringCode code_;

};


#endif