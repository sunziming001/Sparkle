#include <iostream>
#include "SSharedPtr.h"
#include "SString.h"
#include <string>
#include "SWindow_MS_OpenGL.h"

int main(int argc, char** argv)
{
	SWindowConf conf = {
		{800,600},
		"TestWindow",
		false,
		32
	};


	SWindow_MS_OpenGL window(conf);
	while (true)
	{
		window.runOnce();
	}

	return 0;
}