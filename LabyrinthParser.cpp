#include "LabyrinthParser.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>

LabyrinthParser::LabyrinthParser(const char* fileName)
	: mBuffer(std::vector<char>(0)), mWidth(0), mHeight(0)
{
	std::ifstream fileStream(fileName, std::ios::binary);
	fileStream.unsetf(std::ios_base::skipws);

	if(!fileStream) {
		/* throw exception? */
	}
	mBuffer.insert( 
		mBuffer.begin(), 
		std::istream_iterator<char>(fileStream), 
		std::istream_iterator<char>());

	/*for(int i = 0; i <= (int) mBuffer.size(); i++) {
		int lock = 1;
		if(mBuffer[i] == '\n') {
			if(lock) {
				mWidth = i;
				lock = 0;
			}
			mBuffer.erase(mBuffer.begin()+i);
		}
	}*/

	//mHeight = mBuffer.size() / mWidth;
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
