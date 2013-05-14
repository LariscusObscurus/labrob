#ifndef LABYRINTHPARSER_H
#define LABYRINTHPARSER_H

#include <vector>

class LabyrinthParser
{
	std::vector<char> mBuffer;
	int mWidth;
	int mHeight;
public:
	LabyrinthParser(const char* fileName);
	~LabyrinthParser();

	std::vector<char> getBuffer();
	int getWidth();
	int getHeight();
};

#endif
