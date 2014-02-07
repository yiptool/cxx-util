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
#ifndef __3995c06ae7ce2a87b0ff3c67f60ce324__
#define __3995c06ae7ce2a87b0ff3c67f60ce324__

#ifdef _MSC_VER
 typedef signed __int8 int8;
 typedef unsigned __int8 uint8;
 typedef signed __int16 int16;
 typedef unsigned __int16 uint16;
 typedef signed __int32 int32;
 typedef unsigned __int32 uint32;
 typedef signed __int64 int64;
 typedef unsigned __int64 uint64;
#else
 #include <stdint.h>
 typedef int8_t int8;
 typedef uint8_t uint8;
 typedef int16_t int16;
 typedef uint16_t uint16;
 typedef int32_t int32;
 typedef uint32_t uint32;
 typedef int64_t int64;
 typedef uint64_t uint64;
#endif

#endif
