#include "Labyrinth.hpp"
#include "Robot.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>

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
	std::lock_guard<std::mutex> lock1(mMutexBuffer);
	std::lock_guard<std::mutex> lock2(mMutexWidth);
	return (mBuffer[y * mWidth + x] != '#');
}

/* Ausgabe des Labyrinths */
void Labyrinth::display()
{
	std::lock_guard<std::mutex> lock1(mMutexBuffer);
	std::lock_guard<std::mutex> lock2(mMutexWidth);
	int size = (int) mBuffer.size();
	for (int i = 0; i <= size; i++) {
		if(i == size) {
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
	std::lock_guard<std::mutex> lock(mMutexBuffer);
	return mBuffer;
}

int Labyrinth::getWidth()
{
	std::lock_guard<std::mutex> lock(mMutexWidth);
	return mWidth;
}

int Labyrinth::getHeight()
{
	std::lock_guard<std::mutex> lock(mMutexHeight);
	return mHeight;
}

Labyrinth::Position Labyrinth::getEntry()
{
	std::lock_guard<std::mutex> lock1(mMutexHeight);
	std::lock_guard<std::mutex> lock2(mMutexWidth);
	std::lock_guard<std::mutex> lock3(mMutexEntry);
	Position result;
	result.x = mEntry % mWidth;
	result.y = mEntry / mWidth;
	return result;
}

Labyrinth::Position Labyrinth::getExit()
{
	std::lock_guard<std::mutex> lock1(mMutexHeight);
	std::lock_guard<std::mutex> lock2(mMutexWidth);
	std::lock_guard<std::mutex> lock3(mMutexExit);
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
	for (int i = (int) mBuffer.size() ; i >= mWidth * (mHeight -1); i--) {
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
