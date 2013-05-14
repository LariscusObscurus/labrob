#ifndef LABYRINTHPARSER_H
#define LABYRINTHPARSER_H

class IFileStream;

class LabyrinthParser
{
	char* mBuffer;
	int mWidth;
	int mHeight;
public:
	LabyrinthParser(const char* fileName);
	LabyrinthParser(IFileStream* fileStream);
	~LabyrinthParser();

	const char* getBuffer();
	int getWidth();
	int getHeight();
};

#endif
