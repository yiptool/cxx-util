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
#ifndef __34b00717395c1317c4d174d53fdc0082__
#define __34b00717395c1317c4d174d53fdc0082__

#include <memory>

/// @cond
namespace do_not_use_me
{
	template <class TYPE, class... ARGS> struct make_ptr_proxy : public TYPE
	{
		inline make_ptr_proxy(ARGS&&... args) : TYPE(std::forward<ARGS>(args)...) {}
	};
}
/// @endcond

template <class TYPE, class... ARGS> std::shared_ptr<TYPE> make_ptr(ARGS&&... args)
{
	return std::static_pointer_cast<TYPE>(
		std::make_shared<do_not_use_me::make_ptr_proxy<TYPE, ARGS...>>(std::forward<ARGS>(args)...)
	);
}

#define FRIEND_MAKE_PTR() \
	template <class TYPE, class... ARGS> friend struct do_not_use_me::make_ptr_proxy;

#endif
