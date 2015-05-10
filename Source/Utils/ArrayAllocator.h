#pragma once

#include "Memory.h"

namespace ae
{
template<class T>
class ArrayAllocator
{
public:
	ArrayAllocator()
	{
		m_elements = nullptr;
		m_count = 0;
		m_capacity = 0;
	}

	ArrayAllocator(int size)
	{
		m_elements = new T[size];
		m_count = size;
		m_capacity = size;
	}

	void add()
	{
	}

	void addRaw(int count = 1)
	{
		resize(m_count + count);
	}

	void removRaw(int index)
	{

	}

	/// Constructs element at index.
	void construct(const T& element, int index)
	{
		Memory::construct(element, m_elements[m_count]);
	}

	/// Destructs element at index.
	void destruct(int index)
	{
		Memory::destroy(m_elements[index]);
	}

	void reserve(int size)
	{
		if (size > m_capacity)
		{
			if (m_capacity < 1)
				m_capacity = 1;
			while (m_capacity < size)
				m_capacity *= 2;

			T* tmp = Memory::allocate<T>(m_capacity);
			Memory::copy(&m_elements[0], &tmp[0], m_count);
			Memory::deallocate(m_elements);
			m_elements = tmp;
		}
	}

	void reserveExact(int size)
	{
		if (size > m_capacity)
		{
			m_capacity = size;

			T* tmp = Memory::allocate(m_capacity);
			Memory::copy(m_elements[0], tmp[0], m_count);
			Memory::deallocate(m_elements);
			m_elements = tmp;
		}
	}

private:
	T* m_elements;
	int m_count;
	int m_capacity;
};
}