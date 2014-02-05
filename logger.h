/* vim: set ai noet ts=4 sw=4 tw=115: */
//
// Copyright (c) 2014 Nikolay Zapolnov (zapolnov@gmail.com).
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
#ifndef __75551012cd3ce61caac8b3f448433fd2__
#define __75551012cd3ce61caac8b3f448433fd2__

#include "macros.h"
#include <string>
#include <sstream>

enum LogLevel
{
	LOG_DEBUG = 0,
	LOG_CONSOLE = 1,
	LOG_SCRIPT_PRINT = 2,
	LOG_SCRIPT_ERROR = 3,
	LOG_INFO = 4,
	LOG_WARN = 5,
	LOG_ERROR = 6 
};

enum
{
	NUM_LOG_LEVELS = 7
};

class LogStream : public std::stringstream
{
public:
	static LogStream DUMMY;

	inline explicit LogStream(LogLevel level) : std::stringstream(), m_RefCount(1), m_Level(level) {}
	~LogStream();

	NOTHROW inline void retain() { ++m_RefCount; }
	NOINLINE void release();

private:
	signed char m_RefCount;
	signed char m_Level;

	LogStream(const LogStream &);
	LogStream & operator=(const LogStream &);
};

class LogWriter
{
public:
	NOTHROW inline explicit LogWriter(LogStream * stream)
		: m_Stream(stream)
	{
	}

	NOTHROW inline LogWriter(const LogWriter & src)
		: m_Stream(src.m_Stream)
	{
		m_Stream->retain();
	}

	inline ~LogWriter()
	{
		m_Stream->release();
	}

	inline LogWriter & operator=(const LogWriter & src)
	{
		src.m_Stream->retain();
		m_Stream->release();
		m_Stream = src.m_Stream;
		return *this;
	}

	template <class TYPE> inline LogWriter & operator<<(TYPE value)
	{
		if (UNLIKELY(m_Stream != &LogStream::DUMMY))
			serialize(value);
		return *this;
	}

protected:
	template <class TYPE> NOINLINE void serialize(const TYPE & value)
	{
		*m_Stream << value;
	}

private:
	LogStream * m_Stream;
};

class LogListener
{
public:
	virtual inline ~LogListener() {}
	virtual void logMessage(LogLevel level, const std::string & message) = 0;
};

class DefaultLogListener : public LogListener
{
public:
	static DefaultLogListener instance;
	void logMessage(LogLevel level, const std::string & message);
};

namespace Log
{
	void setListener(LogLevel level, LogListener * listener);

	void write(LogLevel level, const std::string & message);
	LogWriter write(LogLevel level);

	inline LogWriter debug() { return write(LOG_DEBUG); }
	inline LogWriter info() { return write(LOG_INFO); }
	inline LogWriter warn() { return write(LOG_WARN); }
	inline LogWriter error() { return write(LOG_ERROR); }
}

#endif
