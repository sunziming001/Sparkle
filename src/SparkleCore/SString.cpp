#include "SString.h"
#include <string>
#include <codecvt> // for std::codecvt_utf8
#include <locale>  // for std::wstring_convert
#include <sstream>

struct SString::Data
{
	SByteArray byteArr;
	SFlags<FmtFlag> fmtFlags=FmtFlag::DEC;
};

SString::SString()
	:d_(new Data())
{

}

SString::SString(const char * utf8Str)
	: SString()
{
	size_t len = strlen(utf8Str);
	d_->byteArr = FromUtf8ToUnicode(SByteArray((SByte*)utf8Str, len));
	if (utf8Str[len - 1] != 0)
	{
		d_->byteArr += SByteArray((SByte*)SWS("\0"), sizeof(wchar_t));
	}
	
}

SString::SString(const char* utf8Str, size_t len)
	: SString()
{
	d_->byteArr = FromUtf8ToUnicode(SByteArray((SByte*)utf8Str, len));
	if (utf8Str[len - 1] != 0)
	{
		d_->byteArr += SByteArray((SByte*)SWS("\0"), sizeof(wchar_t));
	}
}

SString::SString(const wchar_t * unicodeStr)
	: SString()
{
	size_t len = wcslen(unicodeStr);
	d_->byteArr = SByteArray((SByte*)unicodeStr, len*sizeof(wchar_t));
	if (unicodeStr[len - 1] != 0)
	{
		d_->byteArr += SByteArray((SByte*)SWS("\0"), sizeof(wchar_t));
	}
}

SString::SString(const wchar_t* unicodeStr, size_t len)
	: SString()
{
	d_->byteArr = SByteArray((SByte*)unicodeStr, len * sizeof(wchar_t));
	if (unicodeStr[len - 1] != 0)
	{
		d_->byteArr += SByteArray((SByte*)SWS("\0"), sizeof(wchar_t));
	}
}


SString::SString(const SString& str)
	: SString()
{
	d_->byteArr = str.d_->byteArr;
}


SString::~SString()
{
	delete d_;
}

SString& SString::operator=(const wchar_t* unicodeStr)
{
	size_t len = wcslen(unicodeStr);
	d_->byteArr = SByteArray((SByte*)unicodeStr, len * sizeof(wchar_t));
	if (unicodeStr[len - 1] != 0)
	{
		d_->byteArr += SByteArray((SByte*)SWS("\0"), sizeof(wchar_t));
	}
	return *this;
}

SString& SString::operator=(const char* utf8Str)
{
	size_t len = strlen(utf8Str);

	d_->byteArr = FromUtf8ToUnicode(SByteArray((SByte*)utf8Str, len));
	if (utf8Str[len - 1] != 0)
	{
		d_->byteArr += SByteArray((SByte*)SWS("\0"), sizeof(wchar_t));
	}
	return *this;
}




SString& SString::operator=(const SString& str)
{
	d_->byteArr = str.d_->byteArr;
	return *this;
}

SString SString::operator+(const char* utf8Str)
{
	SString ret = *this;
	size_t len = strlen(utf8Str);
	while (utf8Str[len - 1] == 0 && len>0)
	{
		len--;
	}
	if (len > 0)
	{
		SByteArray appendData = FromUtf8ToUnicode(SByteArray((SByte*)utf8Str, len));

		ret.d_->byteArr -= sizeof(wchar_t);
		ret.d_->byteArr += appendData;
		ret.d_->byteArr += SByteArray((SByte*)SWS("\0"), sizeof(wchar_t));

	}
	
	return ret;
}

SString SString::operator+(const wchar_t* unicodeStr)
{
	SString ret = *this;

	size_t len = wcslen(unicodeStr);
	while (unicodeStr[len - 1] == 0 && len > 0)
	{
		len--;
	}

	if (len > 0)
	{
		SByteArray appendData = SByteArray((SByte*)unicodeStr, len * sizeof(wchar_t));

		ret.d_->byteArr -= sizeof(wchar_t);
		ret.d_->byteArr += appendData;
		ret.d_->byteArr += SByteArray((SByte*)SWS("\0"), sizeof(wchar_t));

	}
	
	return ret;
}



SString& SString::operator<<(const SString& str)
{
	this->d_->byteArr -= sizeof(wchar_t);
	this->d_->byteArr += str.d_->byteArr;
	return *this;
}


SString& SString::operator<<(SSharedPtr<SString> strPTr)
{
	this->d_->byteArr -= sizeof(wchar_t);
	this->d_->byteArr += strPTr->d_->byteArr;
	return *this;
}

SString& SString::operator<<(FmtFlag flag)
{
	d_->fmtFlags |= flag;
	return *this;
}

SString& SString::operator<<(int32_t value)
{
	(*this)<<convertNumber(value);
	return *this;
}

SString& SString::operator<<(uint32_t value)
{
	(*this) << convertNumber(value);
	return *this;
}

SString& SString::operator<<(int64_t value)
{
	(*this) << convertNumber(value);
	return *this;
}

SString& SString::operator<<(uint64_t value)
{
	(*this) << convertNumber(value);
	return *this;
}


SString& SString::operator<<(float value)
{
	(*this) << convertNumber(value);
	return *this;
}

SString& SString::operator<<(double value)
{
	(*this) << convertNumber(value);
	return *this;
}



const SByteArray& SString::toByteArray() const
{
	return d_->byteArr;
}

SByteArray SString::toUtf8() const
{
	return FromUnicodeToUtf8(d_->byteArr);
}

const wchar_t* SString::wc_str() const
{
	return (const wchar_t*)toByteArray().data();
}

size_t SString::length() const
{
	size_t charSize = sizeof(wchar_t);
	return d_->byteArr.size() / charSize;
}

bool SString::hasFmtFlag(FmtFlag flag) const
{
	return (d_->fmtFlags&flag) ? true : false;
}

SByteArray SString::FromUtf8ToUnicode(const SByteArray& utf8Data)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
	std::wstring ws = converter.from_bytes((char*)utf8Data.data(), (char*)utf8Data.data() + utf8Data.size());
	return SByteArray((SByte*)ws.c_str(), wcslen(ws.c_str()) * sizeof(wchar_t));
}

SByteArray SString::FromUnicodeToUtf8(const SByteArray& unicodeData)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
	std::wstring wstr = (wchar_t*)unicodeData.data();
	std::string s = converter.to_bytes((wchar_t*)unicodeData.data(), (wchar_t*)unicodeData.data() + unicodeData.size());
	return SByteArray((SByte*)s.c_str(), strlen(s.c_str()));
}

SString SString::FromNumber(int32_t value)
{
	return std::to_wstring(value).c_str();
}

SString SString::FromNumber(uint32_t value)
{
	return std::to_wstring(value).c_str();
}

SString SString::FromNumber(int64_t value)
{
	return std::to_wstring(value).c_str();
}

SString SString::FromNumber(uint64_t value)
{
	return std::to_wstring(value).c_str();
}

SString SString::FromNumber(float value)
{
	return std::to_wstring(value).c_str();
}

SString SString::FromNumber(double value)
{
	return std::to_wstring(value).c_str();
}

SString SString::FromHexNumber(int32_t value)
{
	std::wstringstream stream;
	stream << SWS("0x") << std::hex << value;
	return stream.str().c_str();
}

SString SString::FromHexNumber(uint32_t value)
{
	std::wstringstream stream;
	stream << SWS("0x") << std::hex << value;
	return stream.str().c_str();
}

SString SString::FromHexNumber(int64_t value)
{
	std::wstringstream stream;
	stream << SWS("0x") << std::hex << value;
	return stream.str().c_str();
}

SString SString::FromHexNumber(uint64_t value)
{
	std::wstringstream stream;
	stream << SWS("0x") << std::hex << value;
	return stream.str().c_str();
}

SString SString::FromHexNumber(float value)
{
	return FromNumber(value);
}

SString SString::FromHexNumber(double value)
{
	return FromNumber(value);
}

