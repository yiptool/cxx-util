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
#ifndef __73df9c7ed6eaca1e8a31f4332c338263__
#define __73df9c7ed6eaca1e8a31f4332c338263__

#include "macros.h"
#include <cstdlib>

template <class TYPE, size_t ITEMSPERARENA = 64> class PoolAllocator
{
public:
	PoolAllocator()
		: m_FreeList(nullptr)
	{
		m_Arena = new Arena;
	}

	~PoolAllocator() noexcept
	{
		while (m_Arena)
		{
			Arena * arena = m_Arena;
			m_Arena = arena->prevArena;
			delete arena;
		}
	}

	TYPE * alloc()
	{
		if (m_FreeList)
		{
			Slot * slot = m_FreeList;
			m_FreeList = slot->nextFree;
			return reinterpret_cast<TYPE *>(slot->payload);
		}

		if (m_Arena->firstFree < ITEMSPERARENA)
			return reinterpret_cast<TYPE *>(m_Arena->data[m_Arena->firstFree++].payload);

		m_Arena = new Arena(m_Arena);
		return reinterpret_cast<TYPE *>(m_Arena->data[0].payload);
	}

	void free(TYPE * ptr) noexcept
	{
		Slot * slot = reinterpret_cast<Slot *>(reinterpret_cast<char *>(ptr) - offsetof(Slot, payload));
		slot->nextFree = m_FreeList;
		m_FreeList = slot;
	}

private:
	union Slot
	{
		alignas(TYPE) char payload[sizeof(TYPE)];
		Slot * nextFree;
	};

	struct Arena
	{
		Slot data[ITEMSPERARENA];
		size_t firstFree;
		Arena * const prevArena;

		inline Arena() noexcept : firstFree(0), prevArena(nullptr) {}
		inline Arena(Arena * prev) noexcept : firstFree(1), prevArena(prev) {}
		inline ~Arena() noexcept {}
	};

	Arena * m_Arena;
	Slot * m_FreeList;

	PoolAllocator(const PoolAllocator &) = delete;
	PoolAllocator & operator=(const PoolAllocator &) = delete;
};

#endif
