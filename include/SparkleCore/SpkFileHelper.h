#ifndef SPK_FILE_HELPER_H
#define SPK_FILE_HELPER_H

#include "SConfig.h"
#include "SString.h"



class SPARKLE_API SpkFileHelper
{
private:
	static SpkFileHelper* instance;
	SpkFileHelper();
public:
	~SpkFileHelper();
	static SpkFileHelper* getInstance();

	bool compressDir(const SString& dir, const SString& name);
private:
	
	SString toPathString(const SString& path);

	DECLARE_INNER_DATA(d_);
};


#endif