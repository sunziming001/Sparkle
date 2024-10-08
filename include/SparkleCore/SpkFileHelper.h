#ifndef SPK_FILE_HELPER_H
#define SPK_FILE_HELPER_H

#include "SConfig.h"
#include "SString.h"
#include "SByteArray.h"



class SPARKLE_API SpkFileHelper
{
private:
	static SpkFileHelper* instance;
	SpkFileHelper();
public:
	~SpkFileHelper();
	static SpkFileHelper* getInstance();

	bool compressDir(const SString& dir, 
		const SString& name,
		uint32_t version=0);

	bool loadPackage(const SString& packagePath);
	SByteArray getRes(const SString& path);
private:
	
	SString toPathString(const SString& path);

	DECLARE_INNER_DATA(d_);
};


#endif