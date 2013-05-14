#ifndef STREAM_H
#define STREAM_H

#include <cstddef>

class IReadStream
{
public:
	virtual size_t read(void* buffer, size_t size) = 0;
	virtual bool isReadable() = 0;
};

class IWriteStream
{
public:
	virtual size_t write(const void* buffer, size_t size) = 0;
	virtual bool isWritable() = 0;
};

enum class Origin {
	Begin,
	Current,
	End
};

class IStream : public virtual IReadStream, public virtual IWriteStream
{
public:
	virtual long seek(long offset, Origin origin) = 0;
	virtual long getPosition() = 0;
	virtual bool isSeekable() = 0;
};

class IFileStream : public virtual IStream
{
public:
	virtual const char* getFileName() = 0;
	virtual const char* getFilePath() = 0;
	virtual int printf(const char* str, ...) = 0;
	virtual int readString(char* buffer, int size) = 0;
	virtual char* readContent() = 0;
};

class IMemoryStream : public virtual IStream
{
public:
	virtual void* getBuffer() = 0;
	virtual void flushBuffer() = 0;
};

#endif
