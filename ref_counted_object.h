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
#ifndef __1f4d0a314303d4c3d661b5ba97369387__
#define __1f4d0a314303d4c3d661b5ba97369387__

#include "assert.h"
#include <cstddef>

class RefCountedObject
{
public:
	class WeakPtr;

	struct WeakPtrBase
	{
	protected:
		void * m_Pointer;

		void set(RefCountedObject * object, void * pointer);

	private:
		WeakPtrBase * m_Next;
		WeakPtrBase * m_Prev;

		void attach(RefCountedObject * object);
		void detach();

		friend class WeakPtr;
		friend class RefCountedObject;
	};

	class WeakPtr : public WeakPtrBase
	{
	protected:
		WeakPtr();
		WeakPtr(RefCountedObject * object, void * pointer);
		~WeakPtr();

	private:
		WeakPtr(const WeakPtr & src);
		WeakPtr & operator=(const WeakPtr & src);

		friend class RefCountedObject;
	};

	RefCountedObject();
	RefCountedObject(const RefCountedObject &);
	virtual ~RefCountedObject();

	inline RefCountedObject & operator=(const RefCountedObject &) { return *this; }

	inline int refCount() const { return m_RefCount; }
	inline void retain() { ++m_RefCount; }
	void release();

protected:
	virtual void deleteThis();

private:
	int m_RefCount;
	WeakPtr m_WeakPtrs;

	friend class WeakPtr;
	friend struct WeakPtrBase;
};

#endif
