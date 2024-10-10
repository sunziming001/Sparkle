#include <iostream>
#include "SpkFileHelper.h"

void printHelp()
{
	std::cout << "SparkelPack command: " << std::endl;
	std::cout << "-d [DirPath]		assign dir to compress" << std::endl;
	std::cout << "-o [OutputName]   assign output name" << std::endl;
	std::cout << "-h print help" << std::endl;
}

enum class ReadValueType
{
	None,
	ReadDir,
	ReadOutput,
};

int main(int argc, char** argv)
{
	SString outputName = SWS("output.pack");
	SString dirPath = ".";
	bool isValidLaunch = false;
	ReadValueType type = ReadValueType::None;
	for (int i = 1; i < argc; i++)
	{
		std::string v = argv[i];
		
		switch (type)
		{
		case ReadValueType::ReadDir:
			dirPath = v.c_str();
			break;
		case ReadValueType::ReadOutput:
			outputName = v.c_str();
			break;
		default:
			break;
		}

		if (v == "-d")
		{
			isValidLaunch = true;
			type = ReadValueType::ReadDir;
		}
		else if (v == "-o")
		{
			isValidLaunch = true;
			type = ReadValueType::ReadOutput;
		}
		else if(v == "-h") {
			isValidLaunch = true;
			type = ReadValueType::None;
			printHelp();
		}
		else {
			type = ReadValueType::None;
		}
	}

	if (!isValidLaunch)
	{
		printHelp();
	}
	else {
		SpkFileHelper::getInstance()->compressDir(dirPath, outputName);
	}

	


	return 0;
}