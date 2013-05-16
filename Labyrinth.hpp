#ifndef LABYRINTHPARSER_H
#define LABYRINTHPARSER_H

#include <vector>

class Labyrinth
{
	std::vector<char> mBuffer;
	int mWidth;
	int mHeight;
public:
	Labyrinth();
	~Labyrinth();

	int readFile(const char* fileName);
	bool isfree(int x, int y);
	void display();
	int newRobot();
	std::vector<char> getBuffer();
	int getWidth();
	int getHeight();
};

#endif
