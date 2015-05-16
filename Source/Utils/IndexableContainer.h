#pragma once

template<class T>
class LinearAllocator
{
public:
	LinearAllocator()
	{
		m_elements = nullptr;
		count = 0;
		capacity = 0;
	}

	LinearAllocator(int size)
	{
		m_elements = new T[size];
		count = size;
		capacity = size;
	}

	void reserve(int size)
	{
		if (size > capacity)
		{
			if (capacity < 1)
				capacity = 1;
			while (capacity < size)
				capacity *= 2;

			T* tmp = Memory::allocate<T>(capacity);
			Memory::copy(&m_elements[0], &tmp[0], count);
			Memory::deallocate(m_elements);
			m_elements = tmp;
		}
	}

	void reserveExact(int size)
	{
		if (size > capacity)
		{
			capacity = size;

			T* tmp = Memory::allocate(capacity);
			Memory::copy(m_elements[0], tmp[0], count);
			Memory::deallocate(m_elements);
			m_elements = tmp;
		}
	}

private:
	T* m_elements;
	int count;
	int capacity;
};

template<class T>
class IndexableContainer
{
public:
	IndexableContainer()
	{
		elements = nullptr;
		count = 0;
		capacity = 0;
	}

	IndexableContainer(int size)
	{
		elements = new T[size];
		count = size;
		capacity = size;
	}

	//! Exposes the raw pointer storing the elements of the container.
	//! The pointer can be used to modify elements and remains valid
	//! as long as the container is not reallocated.
	T* raw();
	const T* raw() const;

public:
	T* elements;
	int count;
	int capacity;
};
