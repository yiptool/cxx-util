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
#include "logger.h"
#include "assert.h"
#include <iostream>

LogStream LogStream::DUMMY(LOG_DEBUG);
DefaultLogListener DefaultLogListener::instance;

static LogListener * g_LogListeners[] =
{
	RELEASE_ONLY_CODE(NULL) DEBUG_ONLY_CODE(&DefaultLogListener::instance),	/* LOG_DEBUG */
	RELEASE_ONLY_CODE(NULL) DEBUG_ONLY_CODE(&DefaultLogListener::instance),	/* LOG_CONSOLE */
	&DefaultLogListener::instance,											/* LOG_SCRIPT_PRINT */
	&DefaultLogListener::instance,											/* LOG_SCRIPT_ERROR */
	&DefaultLogListener::instance,											/* LOG_INFO */
	&DefaultLogListener::instance,											/* LOG_WARN */
	&DefaultLogListener::instance,											/* LOG_ERROR */
};

static const size_t g_NumLogLevels = sizeof(g_LogListeners) / sizeof(g_LogListeners[0]);

LogStream::~LogStream()
{
	if (LIKELY(this == &DUMMY))
		return;

	if (LIKELY(m_Level >= 0 && static_cast<size_t>(m_Level) < g_NumLogLevels))
	{
		if (UNLIKELY(g_LogListeners[m_Level] != NULL))
			g_LogListeners[m_Level]->logMessage((LogLevel)m_Level, this->str());
	}
}

NOINLINE void LogStream::release()
{
	if (--m_RefCount == 0 && this != &DUMMY)
		delete this;
}

void DefaultLogListener::logMessage(LogLevel level, const std::string & message)
{
	switch (level)
	{
	case LOG_DEBUG:
	case LOG_CONSOLE:
	case LOG_SCRIPT_PRINT:
	case LOG_INFO:
		std::cout << message << std::endl;
		break;

	case LOG_WARN:
	case LOG_ERROR:
	case LOG_SCRIPT_ERROR:
		std::cerr << message << std::endl;
		break;
	}
}

void Log::setListener(LogLevel level, LogListener * listener)
{
	if (LIKELY(level >= 0 && level < g_NumLogLevels))
		g_LogListeners[level] = listener;
}

void Log::write(LogLevel level, const std::string & message)
{
	if (UNLIKELY(level < 0))
		level = LOG_DEBUG;
	else if (UNLIKELY(level >= g_NumLogLevels))
		level = LOG_ERROR;

	if (UNLIKELY(g_LogListeners[level]))
		g_LogListeners[level]->logMessage(level, message);
}

LogWriter Log::write(LogLevel level)
{
	if (UNLIKELY(level < 0))
		level = LOG_DEBUG;
	else if (UNLIKELY(level >= g_NumLogLevels))
		level = LOG_ERROR;

	if (LIKELY(!g_LogListeners[level]))
		return LogWriter(&LogStream::DUMMY);

	return LogWriter(new LogStream(level));
}
