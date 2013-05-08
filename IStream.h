#ifndef ISTREAM_H
#define ISTREAM_H

#include <cstddef>

enum class Origin {
	Begin,
	Current,
	End
};

class IReadStream
{
public:
	virtual bool isReadable() = 0;
	virtual size_t read(void* buffer, size_t size) = 0;
};

class IWriteStream
{
public:
	virtual bool isWritable() = 0;
	virtual size_t write(const void* buffer, size_t size) = 0;
};

class IStream : public virtual IReadStream, public virtual IWriteStream
{
public:
	virtual size_t getSize() = 0;
	virtual size_t getPosition() = 0;
	virtual long seek(long offset, Origin origin) = 0;
	virtual bool isSeekabel() = 0;
};

class ITextStream : public virtual IStream
{
public:
	virtual size_t printf(const char* str, size_t size) = 0;
	virtual size_t sprintf(const char* str, size_t size, char* output) = 0;
};

#endif