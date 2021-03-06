#include "Labyrinth.hpp"
#include "Robot.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>

Labyrinth::Labyrinth()
	: mWidth(0), mHeight(0), mEntry(-1), mExit(-1)
{
}

Labyrinth::Labyrinth(std::ifstream& fileStream)
	: mWidth(0), mHeight(0), mEntry(-1), mExit(-1)
{
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
}

Labyrinth::~Labyrinth()
{
}


/* Ist die angegebene Position frei? 
 * Return Werte:
 * 	false -> Feld ist nicht frei
 * 	true -> Feld ist frei
 */

bool Labyrinth::isfree(int x, int y)
{
	if((y >= mHeight) || (x >= mWidth) || (y < 0) || (x < 0)){
		return 0;
	}
	return (mBuffer[y * mWidth + x] != '#');
}

/* Ausgabe des Labyrinths */
void Labyrinth::display(std::vector<char> labyrinth)
{
	int size = (int) labyrinth.size();
	for (int i = 0; i <= size; i++) {
		if(i == size) {
			std::cout << std::endl;
		} else if(((i % mWidth) == 0) ) {
			std::cout << std::endl << labyrinth[i];
		} else {
			std::cout << labyrinth[i];
		}
	}
	std::cout << std::endl;
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

Labyrinth::Position Labyrinth::getEntry()
{
	Position result;
	result.x = mEntry % mWidth;
	result.y = mEntry / mWidth;
	return result;
}

Labyrinth::Position Labyrinth::getExit()
{
	Position result;
	result.x = mExit % mWidth;
	result.y = mExit / mWidth;
	return result;
}

int Labyrinth::locateStartEnd()
{
	for (int i = 0; i <= mWidth - 1; i++) {
		if((mBuffer[i] != '#') && (bothFound(i) == 0)) {
			return 0;
		}
	}
	for (int i = 2; i <= mHeight; i++) {
		if((mBuffer[i * mWidth - 1] != '#') && (bothFound(i * mWidth - 1) == 0)) {
				return 0;
		}
	}
	for (int i = (int) mBuffer.size() - 1 ; i >=((int)mBuffer.size() -1 - mWidth); --i) {
		if((mBuffer[i] != '#') && (bothFound(i) == 0)) {
			return 0;
		}
	}
	for (int i = (mHeight -1); i >= 1 ; i--) {
		if((mBuffer[i * mWidth] != '#') && (bothFound(i * mWidth ) == 0)) {
			return 0;
		}
	}
	return 0;
}

int Labyrinth::bothFound(int pos)
{
	if(mEntry == -1) {
		mEntry = pos;
	} else if(mExit == -1){
		mExit = pos;
		return 0;
	}
	return -1;
}

void Labyrinth::plotPath(const std::list<Position>& robPath)
{
	std::vector<char> temp = mBuffer;
	for(auto& it: robPath){
		temp[it.y * mHeight + it.x] = '*';
	}
	display(temp);
}

void Labyrinth::showLabyrinth()
{
	display(mBuffer);
}
