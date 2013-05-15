#include "LabyrinthParser.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>
#include <sstream>

LabyrinthParser::LabyrinthParser(const char* fileName)
	: mWidth(0), mHeight(0)
{
	std::ifstream fileStream(fileName);
	fileStream.unsetf(std::ios_base::skipws);

	if(!fileStream) {
		std::cerr << "Could not open file!" << std::endl;
	}
  	std::string lab((std::istreambuf_iterator<char>(fileStream)), 
			std::istreambuf_iterator<char>());

	for(int i = 0; i <= lab.size(); i++) {
		if (lab[i] == '\r')
		{
			mWidth = i;
			break;
		}
	}

	lab.erase(std::remove(lab.begin(), lab.end(), '\n'), lab.end());
	lab.erase(std::remove(lab.begin(), lab.end(), '\r'), lab.end());
	std::cout << lab << std::endl;

	mBuffer = std::vector<char>(lab.begin(), lab.end());
	fileStream.close();
}

LabyrinthParser::~LabyrinthParser()
{
}

std::vector<char> LabyrinthParser::getBuffer()
{
	return mBuffer;
}

int LabyrinthParser::getWidth()
{
	return mWidth;
}

int LabyrinthParser::getHeight()
{
	return mHeight;
}
