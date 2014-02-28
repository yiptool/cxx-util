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
#ifndef __8298e5c932266831c33b13f678b6e00f__
#define __8298e5c932266831c33b13f678b6e00f__

#include "ref_counted_object.h"
#include "assert.h"

template <class TYPE> class WeakPtr;

template <class TYPE> class StrongPtr
{
public:
	inline StrongPtr() : m_Ptr(NULL) {}
	inline StrongPtr(TYPE * p) : m_Ptr(p) { retain(); }
	inline StrongPtr(const StrongPtr & s) : m_Ptr(s.m_Ptr) { retain(); }
	template <class T> inline StrongPtr(T * p) : m_Ptr(p) { retain(); }
	template <class T> inline StrongPtr(const StrongPtr<T> & s) : m_Ptr(s.m_Ptr) { retain(); }
	template <class T> inline StrongPtr(const WeakPtr<T> & s) : m_Ptr(s.get_()) { retain(); }
	inline ~StrongPtr() { release(); }

	inline StrongPtr & operator=(TYPE * p) { set(p); return *this; }
	inline StrongPtr & operator=(const StrongPtr & s) { set(s.m_Ptr); return *this; }
	template <class T> inline StrongPtr & operator=(T * p) { set(p); return *this; }
	template <class T> inline StrongPtr & operator=(const StrongPtr<T> & s) { set(s.m_Ptr); return *this; }
	template <class T> inline StrongPtr & operator=(const WeakPtr<T> & s) { set(s.get_()); return *this; }

	void release() { if (m_Ptr) { m_Ptr->release(); m_Ptr = NULL; } }

	inline bool isNull() const { return !m_Ptr; }
	inline bool operator!() const { return !m_Ptr; }

	inline TYPE * get() const { return m_Ptr; }
	inline TYPE * operator->() const { ASSERT(m_Ptr != NULL); return m_Ptr; }
	inline TYPE & operator*() const { ASSERT(m_Ptr != NULL); return *m_Ptr; }

	inline bool operator==(const TYPE * p) const { return m_Ptr == p; }
	inline bool operator==(const StrongPtr<TYPE> & s) const { return m_Ptr == s.m_Ptr; }
	inline bool operator==(const WeakPtr<TYPE> & s) const { return m_Ptr == s.get_(); }
	template <class T> inline bool operator==(const T * p) const { return m_Ptr == p; }
	template <class T> inline bool operator==(const StrongPtr<T> & s) const { return m_Ptr == s.m_Ptr; }
	template <class T> inline bool operator==(const WeakPtr<T> & s) const { return m_Ptr == s.get_(); }

	inline bool operator!=(const TYPE * p) const { return m_Ptr != p; }
	inline bool operator!=(const StrongPtr<TYPE> & s) const { return m_Ptr != s.m_Ptr; }
	inline bool operator!=(const WeakPtr<TYPE> & s) const { return m_Ptr != s.get_(); }
	template <class T> inline bool operator!=(const T * p) const { return m_Ptr != p; }
	template <class T> inline bool operator!=(const StrongPtr<T> & s) const { return m_Ptr != s.m_Ptr; }
	template <class T> inline bool operator!=(const WeakPtr<T> & s) const { return m_Ptr != s.get_(); }

private:
	TYPE * m_Ptr;

	void retain() { if (m_Ptr) m_Ptr->retain(); }
	void set(TYPE * p) { if (p) p->retain(); if (m_Ptr) m_Ptr->release(); m_Ptr = p; }
};

#endif
