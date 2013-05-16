#include "Labyrinth.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>
#include <sstream>

Labyrinth::Labyrinth()
	: mBuffer(0), mWidth(0), mHeight(0)
{
}

Labyrinth::~Labyrinth()
{
}

int Labyrinth::readFile(const char *fileName)
{
	std::ifstream fileStream(fileName);
	fileStream.unsetf(std::ios_base::skipws);

	if(!fileStream) {
		std::cerr << "Could not open file!" << std::endl;
		return -1;
	}
  	std::string lab((std::istreambuf_iterator<char>(fileStream)), 
			std::istreambuf_iterator<char>());

	for(int i = 0; i <= (int) lab.size(); i++) {
		if (lab[i] == '\r')
		{
			mWidth = i;
			break;
		}
	}

	lab.erase(std::remove(lab.begin(), lab.end(), '\n'), lab.end());
	lab.erase(std::remove(lab.begin(), lab.end(), '\r'), lab.end());

	mBuffer = std::vector<char>(lab.begin(), lab.end());

	fileStream.close();
	return 0;
}

bool Labyrinth::isfree(int x, int y)
{
	if(mBuffer[y * mWidth + x] == '#') {
		return false;
	} else {
		return true;
	}
}

void Labyrinth::display()
{
	for (int i = 0; i <= (int) mBuffer.size(); i++) {
		if(i == (int) mBuffer.size()) {
			std::cout << std::endl;

		} else if(((i % mWidth) == 0) ) {
			std::cout << std::endl << mBuffer[i];
		} else {
			std::cout << mBuffer[i];
		}
	}
}

std::vector<char> Labyrinth::getBuffer()
{
	return mBuffer;
}

int Labyrinth::getWidth()
{
	return mWidth;
}

int Labyrinth::getHeight()
{
	return mHeight;
}
