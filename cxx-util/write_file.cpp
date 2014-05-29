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
#include "write_file.h"
#include "fmt.h"
#include "macros.h"
#include <stdexcept>
#include <cerrno>
#include <cstring>
#include <cstdio>

void writeFile(const std::string & file, const std::string & data)
{
	FILE * f = fopen(file.c_str(), "wb");
	if (UNLIKELY(!f))
	{
		int err = errno;
		throw std::runtime_error(fmt() << "unable to create file '" << file << "': " << strerror(err));
	}

	try
	{
		fwrite(data.data(), 1, data.size(), f);
		if (UNLIKELY(ferror(f)))
		{
			int err = errno;
			throw std::runtime_error(fmt() << "unable to write file '" << file << "': " << strerror(err));
		}

		fflush(f);
		if (UNLIKELY(ferror(f)))
		{
			int err = errno;
			throw std::runtime_error(fmt() << "unable to write file '" << file << "': " << strerror(err));
		}
	}
	catch (...)
	{
		fclose(f);
		remove(file.c_str());
		throw;
	}

	fclose(f);
}
