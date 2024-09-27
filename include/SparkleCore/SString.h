#ifndef _SSTRING_H
#define _SSTRING_H

#include "SConfig.h"
#include "SByteArray.h"
#include "SFlags.h"
#include "SSharedPtr.h"

#define SWS_NX(S) L ##S
#define SWS(S) SWS_NX(S)




class SPARKLE_API SString
{
public:
	enum class FmtFlag
	{
		DEC=0,
		HEX=1,
	};

public:
	SString();
	SString(const char * utf8Str);
	SString(const char* utf8Str, size_t len);
	SString(const wchar_t * unicodeStr);
	SString(const wchar_t* unicodeStr, size_t len);
	SString(const SString& str);
	~SString();

	SString& operator=(const SString& str);
	SString& operator=(const char* utf8Str);
	SString& operator=(const wchar_t* unicodeStr);

	SString operator+(const char* utf8Str);
	SString operator+(const wchar_t* unicodeStr);

	SString& operator<<(const SString& str);
	SString& operator<<(SSharedPtr<SString> strPTr);
	SString& operator<<(FmtFlag flag);
	SString& operator<<(int32_t value);
	SString& operator<<(uint32_t value);
	SString& operator<<(int64_t value);
	SString& operator<<(uint64_t value);
	SString& operator<<(float value);
	SString& operator<<(double value);

	const SByteArray& toByteArray()const;
	SByteArray toUtf8()const;
	size_t length()const;
	bool hasFmtFlag(FmtFlag flag)const;
	
	static SByteArray FromUtf8ToUnicode(const SByteArray& utf8Data);
	static SByteArray FromUnicodeToUtf8(const SByteArray& utf8Data);
	
	static SString FromNumber(int32_t value );
	static SString FromNumber(uint32_t value);
	static SString FromNumber(int64_t value);
	static SString FromNumber(uint64_t value);
	static SString FromNumber(float value);
	static SString FromNumber(double value);

	static SString FromHexNumber(int32_t value);
	static SString FromHexNumber(uint32_t value);
	static SString FromHexNumber(int64_t value);
	static SString FromHexNumber(uint64_t value);
	static SString FromHexNumber(float value);
	static SString FromHexNumber(double value);

private:
	template<typename T>
	SString convertNumber(T value)
	{

		if (hasFmtFlag(FmtFlag::HEX))
		{
			return FromHexNumber(value);
		}
		else {
			return FromNumber(value);
		}
	}


private:
	DECLARE_INNER_DATA(d_);
};

typedef SSharedPtr<SString> SStringPtr;


#endif