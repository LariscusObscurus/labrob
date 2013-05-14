#include "LabyrinthParser.h"
#include "IStream.h"

LabyrinthParser::LabyrinthParser(const char* fileName)
	: mBuffer(0), mWidth(0), mHeight(0)
{
}

LabyrinthParser::LabyrinthParser(IFileStream* fileStream)
	: mBuffer(0), mWidth(0), mHeight(0)
{
}

LabyrinthParser::~LabyrinthParser()
{
	if (mBuffer) {
		delete mBuffer;
	}
}

const char* LabyrinthParser::getBuffer()
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
