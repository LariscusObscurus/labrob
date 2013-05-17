#include "Labyrinth.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>

Labyrinth::Labyrinth()
	: mBuffer(0), mWidth(0), mHeight(0)
{
}

Labyrinth::~Labyrinth()
{
}

/* Datei einlesen und Vector befüllen 
 * Return Werte: 
 * 	0 -> OK
 * 	-1 -> Datei konnte nicht geöffnet werden
 */

int Labyrinth::readFile(const char *fileName)
{
	std::ifstream fileStream(fileName);
	fileStream.unsetf(std::ios_base::skipws);

	if(!fileStream) {
		std::cerr << "Could not open file!" << std::endl;
		return -1;
	}

	mBuffer = std::vector<char>(0);
	mBuffer.insert(mBuffer.begin(),
			std::istreambuf_iterator<char>(fileStream), 
			std::istreambuf_iterator<char>());

	for(int i = 0; i <= (int) mBuffer.size(); i++) {
		if (mBuffer[i] == '\r') {
			mWidth = i;
			break;
		}
	}

	mBuffer.erase(std::remove(mBuffer.begin(), mBuffer.end(), '\n'), mBuffer.end());
	mBuffer.erase(std::remove(mBuffer.begin(), mBuffer.end(), '\r'), mBuffer.end());

	mHeight = (int) mBuffer.size() / mWidth;
	fileStream.close();
	locateStartEnd();
	return 0;
}

/* Ist die angegebene Position frei? 
 * Return Werte:
 * 	false -> Feld ist nicht frei
 * 	true -> Feld ist frei
 */

bool Labyrinth::isfree(int x, int y)
{
	return (mBuffer[y * mWidth + x] != '#');
}

/* Ausgabe des Labyrinths */
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

int Labyrinth::locateStartEnd()
{
	for (int i = 0; i <= (int) mBuffer.size(); i++) {
		if(mBuffer[i] != '#') {
			if((i < mWidth) && (mBuffer[i] != '#')) {
				mEntry = i;
			} else if((i % mWidth) == 0) {
				mEntry = i;
			} else if (i > ((mWidth - 1) * mHeight)) {
				mExit = i;
			} else if ((i % mWidth) == 1) {
				mExit = i;
			}
		}
	}
	return 0;
}
