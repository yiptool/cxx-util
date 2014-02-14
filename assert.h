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
#ifndef __5c9e7207c3699f140b789c52819bb6d4__
#define __5c9e7207c3699f140b789c52819bb6d4__

#include "macros.h"
#include <exception>

#ifdef DISABLE_ASSERTIONS
 #define ASSERT(x) ((void)0)
 #define ASSERT_NONFATAL(x) (LIKELY(x))
 #define DEBUG_ONLY_CODE(x)
 #define RELEASE_ONLY_CODE(x) x
#else
 #define ASSERT(x) ((LIKELY(x) ? (void)0 : assertionFailed(__FILE__, __LINE__, #x)), (void)0)
 #define ASSERT_NONFATAL(x) (LIKELY(x) ? true : (assertionFailedNonFatal(__FILE__, __LINE__, #x), false))
 #define DEBUG_ONLY_CODE(x) x
 #define RELEASE_ONLY_CODE(x)
#endif

EXTERN_C_BEGIN

NOINLINE NORETURN void assertionFailed(const char * file, int line, const char * expr) throw(std::exception);
NOINLINE void assertionFailedNonFatal(const char * file, int line, const char * expr);

EXTERN_C_END

#endif
