#include "SString.h"
#include <string>

SString::SString(const char * utf8Str)
	:code_(SStringCode::Utf8)
{
	size_t len = strlen(utf8Str);
	data_ = SByteArray((SByte*)utf8Str, len);
}

SString::SString(const char* utf8Str, size_t len)
	:code_(SStringCode::Utf8)
{
	data_ = SByteArray((SByte*)utf8Str, len);
}

SString::SString(const wchar_t * unicodeStr)
	:code_(SStringCode::Unicode)
{
	size_t len = wcslen(unicodeStr);
	data_ = SByteArray((SByte*)unicodeStr, len*sizeof(wchar_t));
}

SString::SString(const wchar_t* unicodeStr, size_t len)
	:code_(SStringCode::Unicode)
{
	data_ = SByteArray((SByte*)unicodeStr, len * sizeof(wchar_t));
}

char* SString::c_str() const
{
	if (code_ == SStringCode::Utf8)
	{
		return (char*)data_.data();
	}
	else {
		return nullptr;
	}
}

wchar_t* SString::wc_str() const
{
	if (code_ == SStringCode::Unicode)
	{
		return (wchar_t*)data_.data();
	}
	else {
		return nullptr;
	}
}

size_t SString::length() const
{
	size_t charSize = 1;
	if (code_ == SStringCode::Unicode)
	{
		charSize = sizeof(wchar_t);
	}

	return data_.size() / charSize;
}

SString::~SString()
{

}

SString& SString::operator=(const wchar_t* unicodeStr)
{
	size_t len = wcslen(unicodeStr);
	code_ = SStringCode::Unicode;
	data_ = SByteArray((SByte*)unicodeStr, len * sizeof(wchar_t));

	return *this;
}

SString& SString::operator=(const char* utf8Str)
{
	size_t len = strlen(utf8Str);
	code_ = SStringCode::Utf8;
	data_ = SByteArray((SByte*)utf8Str, len);

	return *this;
}
