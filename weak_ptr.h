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
#ifndef __c438f00117ee5d6bddc2860b7c5c698a__
#define __c438f00117ee5d6bddc2860b7c5c698a__

#include "strong_ptr.h"
#include "ref_counted_object.h"
#include "assert.h"

template <class TYPE> class WeakPtr : public RefCountedObject::WeakPtr
{
public:
	inline WeakPtr() {}
	inline WeakPtr(TYPE * p) : RefCountedObject::WeakPtr(p, p) {}
	inline WeakPtr(const WeakPtr & s) : RefCountedObject::WeakPtr(s.get_(), s.m_Pointer) {}
	template <class T> inline WeakPtr(T * p) : RefCountedObject::WeakPtr(p, p) {}
	template <class T> inline WeakPtr(const StrongPtr<T> & s) : RefCountedObject::WeakPtr(s.get(), s.get()) {}
	template <class T> inline WeakPtr(const WeakPtr<T> & s) : RefCountedObject::WeakPtr(s.get_(), s.m_Pointer) {}
	inline ~WeakPtr() {}

	inline WeakPtr & operator=(TYPE * p) { set(p, p); return *this; }
	inline WeakPtr & operator=(const WeakPtr & s) { set(s.get_(), s.m_Pointer); return *this; }
	template <class T> inline WeakPtr & operator=(T * p) { set(p, p); return *this; }
	template <class T> inline WeakPtr & operator=(const StrongPtr<T> & s) { set(s.get(), s.get()); return *this; }
	template <class T> inline WeakPtr & operator=(const WeakPtr<T> & s) { set(s.get_(), s.m_Pointer); return *this; }

	inline bool isNull() const { return !m_Pointer; }
	inline bool operator!() const { return !m_Pointer; }

	inline StrongPtr<TYPE> get() const { return StrongPtr<TYPE>(reinterpret_cast<TYPE *>(m_Pointer)); }

private:
	inline TYPE * get_() const { return reinterpret_cast<TYPE *>(m_Pointer); }

	template <class T> friend class WeakPtr;
	template <class T> friend class StrongPtr;
};

#endif
