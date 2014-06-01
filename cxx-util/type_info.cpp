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
#include "type_info.h"

#ifdef __GNUG__

#include <cxxabi.h>
#include <cstdlib>

namespace
{
	struct nameptr
	{
		char * p;
		inline nameptr(char * ptr) : p(ptr) {}
		inline ~nameptr() { free(p); }
	};
}

static std::string unmangleName(const char * name)
{
	int status = -1;
	nameptr ptr(abi::__cxa_demangle(name, nullptr, nullptr, &status));
	return (status == 0 ? ptr.p : name);
}

#else // __GNUG__

static std::string unmangleName(const char * name)
{
	return name;
}

#endif // __GNUG__

TypeDescriptor::TypeDescriptor(const std::type_info & info, size_t sz)
	: name(unmangleName(info.name())),
	  size(sz)
{
}
