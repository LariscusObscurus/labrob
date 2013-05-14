#include "LabyrinthParser.hpp"
#include <iostream>
#include <fstream>
#include <vector>

LabyrinthParser::LabyrinthParser(const char* fileName)
	: mBuffer(0), mWidth(0), mHeight(0)
{
	std::ifstream fileStream(fileName);
	if(!fileStream) {
		/* throw exception? */
	}

	while(fileStream.good()) {
		char temp = fileStream.get();
		if(temp != '\n') {
			mBuffer.push_back(temp);
		}
	}

	int size = fileStream.gcount();

	for (int i = 0; i < mBuffer.size(); ++i)
	{
		if(mBuffer[i] == '\n') {
			mWidth = i+1;
			break;
		}
	}

	mHeight = size / mWidth;
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
