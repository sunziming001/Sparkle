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
#include "SMatrix4x4.h"
#include "STransform.h"

int main(int argc, char** argv)
{
	STransform trans;
	SVector3D v(0, 1, 0);
	SVector3D ret;
	//trans.move(SVector3D(0, 1, 0));
	trans.angleRotateZ(90);

	
	ret = trans.calc(v).normalized();
	SpkFileHelper::getInstance()->loadPackage(SWS("res.spk"));

	SWindowConf conf = {
		{800,600},
		"TestWindow",
		false,
		32
	};

	SCoreApplication app(argc, argv);
	SWindow_MS_OpenGL window(conf);

	app.exec();

	
	

	return 0;
}