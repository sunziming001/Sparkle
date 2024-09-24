#include <iostream>
#include "SSharedPtr.h"
#include "SString.h"
#include <string>
#include "SWindow_MS_OpenGL.h"
#include "SCoreApplication.h"

int main(int argc, char** argv)
{
	SWindowConf conf = {
		{800,600},
		"TestWindow",
		false,
		32
	};

	SCoreApplication app(argc, argv);
	SWindow_MS_OpenGL window(conf);
	app.exec();

	while (true)
	{
		window.runOnce();
	}

	return 0;
}