#ifndef _SCONFIG_H
#define _SCONFIG_H

#ifdef EXPORT_AS_DLL

#define SPARKLE_API   __declspec( dllexport )

#else

#define SPARKLE_API __declspec( dllimport )

#endif

#define DECLARE_INNER_DATA(name) \
private: \
	struct Data; \
	struct Data* name = nullptr;\


#endif