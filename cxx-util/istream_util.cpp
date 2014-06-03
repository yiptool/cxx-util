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
#include "istream_util.h"
#include "macros.h"
#include <stdexcept>

void istream_check_error(std::istream & stream, const char * message)
{
	if (UNLIKELY(stream.bad() || stream.fail()))
		throw std::runtime_error(message);
}

void istream_check_error(std::istream & stream, const std::string & message)
{
	if (UNLIKELY(stream.bad() || stream.fail()))
		throw std::runtime_error(message);
}

size_t istream_read(std::istream & stream, void * buf, size_t size)
{
	size_t bytesRead = istream_read(stream, buf, size, std::nothrow);
	istream_check_error(stream, "read failed.");
	return bytesRead;
}

size_t istream_read(std::istream & stream, void * buf, size_t size, const std::nothrow_t &)
{
	char * p = reinterpret_cast<char *>(buf);
	size_t totalBytesRead = 0;

	do
	{
		if (stream.eof() || stream.bad() || stream.fail())
			break;

		std::ios_base::iostate state = stream.rdstate();

		stream.read(p, static_cast<std::streamsize>(size));
		size_t bytesRead = static_cast<size_t>(stream.gcount());

		if (stream.eof())
			stream.clear(state | std::ios_base::eofbit);

		totalBytesRead += bytesRead;
		p += bytesRead;
		size -= bytesRead;
	}
	while (size > 0);

	return totalBytesRead;
}

void istream_seek(std::istream & stream, std::streamoff off, std::ios_base::seekdir dir)
{
	istream_seek(stream, off, dir, std::nothrow);
	istream_check_error(stream, "seek failed.");
}

void istream_seek(std::istream & stream, std::streamoff off, std::ios_base::seekdir dir, const std::nothrow_t &)
{
	std::ios_base::iostate state = stream.rdstate();
	stream.clear(state & ~std::ios_base::eofbit);

	stream.seekg(off, dir);

	if (stream.eof())
		stream.clear(state | std::ios_base::eofbit);
}
