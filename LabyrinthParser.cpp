#include "LabyrinthParser.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>

LabyrinthParser::LabyrinthParser(const char* fileName)
	: mBuffer(0), mWidth(0), mHeight(0)
{
	std::ifstream fileStream(fileName, std::ifstream::binary);
	if(!fileStream) {
		/* throw exception? */
	}
	mBuffer.insert( 
		mBuffer.begin(), 
		std::istream_iterator<char>(fileStream), 
		std::istream_iterator<char>());

	for(int i = 0; i <= mBuffer.size(); i++) {
		if(mBuffer[i] != '\n') {
			mWidth = i;
		}
	}

	mHeight = mBuffer.size() / mWidth;
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
