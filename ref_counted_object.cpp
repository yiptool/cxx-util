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
#include "ref_counted_object.h"

/* RefCountedObject::WeakPtr */

RefCountedObject::WeakPtr::WeakPtr()
	: m_Pointer(NULL)
{
	m_Next = this;
	m_Prev = this;
}

RefCountedObject::WeakPtr::WeakPtr(RefCountedObject * object, void * pointer)
	: m_Pointer(pointer)
{
	attach(object);
}

RefCountedObject::WeakPtr::~WeakPtr()
{
	detach();
}

void RefCountedObject::WeakPtr::set(RefCountedObject * object, void * pointer)
{
	detach();
	m_Pointer = pointer;
	attach(object);
}

void RefCountedObject::WeakPtr::attach(RefCountedObject * object)
{
	if (!object)
	{
		m_Next = this;
		m_Prev = this;
	}
	else
	{
		m_Next = object->m_WeakPtrs.m_Next;
		m_Prev = &object->m_WeakPtrs;
		m_Next->m_Prev = this;
		m_Prev->m_Next = this;
	}
}

void RefCountedObject::WeakPtr::detach()
{
	m_Next->m_Prev = m_Prev;
	m_Prev->m_Next = m_Next;
	m_Next = this;
	m_Prev = this;
}


/* RefCountedObject */

RefCountedObject::RefCountedObject()
	: m_RefCount(0)
{
}

RefCountedObject::RefCountedObject(const RefCountedObject &)
	: m_RefCount(0)
{
}

RefCountedObject::~RefCountedObject()
{
	ASSERT(m_RefCount == 0);
	for (WeakPtr * n, * p = m_WeakPtrs.m_Next; p != &m_WeakPtrs; p = n)
	{
		n = p->m_Next;
		p->m_Pointer = NULL;
		p->m_Next = p;
		p->m_Prev = p;
	}
}

void RefCountedObject::release()
{
	ASSERT(m_RefCount > 0);
	if (--m_RefCount == 0)
		deleteThis();
}

void RefCountedObject::deleteThis()
{
	delete this;
}
