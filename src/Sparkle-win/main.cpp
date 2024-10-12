#include <iostream>
#include "SSharedPtr.h"
#include "SString.h"
#include <string>
#include "SWindow_MS_OpenGL.h"
#include "SCoreApplication.h"
#include "SLogger.h"
#include <set>
#include "SpkFileHelper.h"
#include "SImage.h"
#include "SVector3D.h"

int main(int argc, char** argv)
{

	SVector3D a(0, 1, 0);
	SVector3D b(-1, 0, 0);
	float angle = SVector3D::angle(a, b);

	SpkFileHelper::getInstance()->loadPackage(SWS("res.spk"));

	SWindowConf conf = {
		{800,600},
		"TestWindow",
		false,
		32
	};

	SCoreApplication app(argc, argv);
	SWindow_MS_OpenGL window(conf);

	SInfo("Test") << SVector3D::crossProduct(a, b);
	app.exec();

	
	

	return 0;
}