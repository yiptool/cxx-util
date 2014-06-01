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
#ifndef __1c3c04cabe377d3f2a151946679a4079__
#define __1c3c04cabe377d3f2a151946679a4079__

#include "macros.h"

/**
 * Converts given hexadecimal digit into it's numeric value.
 * @param ch Hexadecimal digit.
 * @returns numeric value of the digit (0 to 15) or -1 if given character is not a hexadecimal digit.
 */
FCONST int unhex(char ch) noexcept;

/**
 * Converts hexadecimal number containing two digits into it's numeric value.
 * @param ch1 First (highest) hexadecimal digit.
 * @param ch2 Second (lowest) hexadecimal digit.
 * @returns numeric value (0 to 255) or -1 if at least one of the characters is not a hexadecimal digit.
 */
FCONST int unhex2(char ch1, char ch2) noexcept;

#endif
