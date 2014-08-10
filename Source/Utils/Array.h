#pragma once

#include "XAssert.h"
#include "Memory.h"

/// Template class that provides a dynamic array.

template<class T>
class Array
{
public:
	Array();
	Array(const Array<T>& other);
	Array(int capacity);
	~Array();

	void init();
	/// Removes all elements from Array.
	void clear();
	/// Removes all elements from Array and releases memory.
	void clearMemory();

	/// Adds an element to container.
	void add(const T& value);
	void add(const T* values, int count)
	{
		reserve(m_count + count);
		Memory::copy(values, m_values + m_count, count);
		m_count += count;
	}
	// Adds uninitialized elements to container. See also resize().
	void addEmpty(int size = 1);
	/// Same as add(), overloading stream operator allows adding multiple elements.
	Array<T>& operator<<(const T& value);
	/// Inserts an element at specified index. Subsequent elements are transposed to cover the resulting gap, which may be a slow operation.
	void addAt(int index, const T& value);
	void removeLast();
	/// Removes element at index. Subsequent elements are transposed to cover the resulting gap which may be slow a slow operation.
	void removeAt(int index);
	/// Fast removal of element by swapping the last element with the element deleted.
	void swapRemove(int index);

	Array<T>& operator=(const Array<T>& other);
	T& operator[](int index);
	const T& operator[](int index) const;
	T& first();
	const T& first() const;
	T& last();
	const T& last() const;
	int count() const;
	bool isEmpty() const;
	/// Make sure container can hold "size" elements without needing to resize.
	void reserve(int size);
	/// Resized the container so that it contains "size" elements. New elements are uninitialized.
	void resize(int size);

private:
	void grow(int size);
	bool withinBounds(int index) const;

	T* m_values;
	int m_count;
	int m_capacity;

	#pragma region Iterator
public:
	class Iterator
	{
	public:
		Iterator(Array* host, int index)
		{
			m_host = host;
			m_index = index;
		}
		void reset()
		{
			m_index = 0;
		}
		bool operator!=(const Iterator& other) const
		{
			return m_index != other.m_index;
		}
		const Iterator& operator++()
		{
			m_index++;
			return *this;
		}
		T& operator*() const
		{
			return (*m_host)[m_index];
		}
		T* operator->() const
		{
			return &(*m_host)[m_index];
		}

	private:
		Array* m_host;
		int m_index;

	};
	Iterator begin()
	{
		return Iterator(this, 0);
	}
	Iterator end()
	{
		return Iterator(this, m_count);
	}
	#pragma endregion
};

template<class T>
Array<T>::Array()
{
	init();
}

template<class T>
Array<T>::Array(const Array<T>& other) : Array()
{
	(*this) = other;
}

template<class T>
Array<T>::Array(int capacity)
{
	init();
	m_capacity = capacity;
	m_values = new T[capacity];
}

template<class T>
Array<T>::~Array()
{
	clearMemory();
}

template<class T>
void Array<T>::init()
{
	m_values = nullptr;
	m_count = 0;
	m_capacity = 0;
}
template<class T>
void Array<T>::addEmpty(int count)
{
	resize(m_count + count);
}

template<class T>
void Array<T>::add(const T& value)
{
	addEmpty();
	last() = value;
}

template<class T>
Array<T>& Array<T>::operator<<(const T& value)
{
	add(value);
	return *this;
}

template<class T>
void Array<T>::addAt(int index, const T& value)
{
	// Extend capacity if necessary
	if (m_count >= m_capacity)
		grow(m_count);

	// Make room for new element
	for (int i = index + 1; i <= m_count; i++)
		m_values[i] = m_values[i - 1];

	m_values[index] = value;
	m_count++;
}

template<class T>
void Array<T>::removeLast()
{
	if (m_count > 0)
		m_count--;
}

template<class T>
void Array<T>::removeAt(int index)
{
	// Shift elements left to cover gap
	for (int i = index; i < m_count - 1; i++)
		m_values[i] = m_values[i + 1];
	m_count--;
}

template<class T>
void Array<T>::swapRemove(int index)
{
	m_values[index] = last();
	if (m_count > 0)
		m_count--;
}

template<class T>
Array<T>& Array<T>::operator=(const Array<T>& other)
{
	clear();
	resize(other.count());
	if (!other.isEmpty())
		Memory::copy(&other[0], &(*this)[0], other.count() * sizeof(T));

	return *this;
}

template<class T>
void Array<T>::clear()
{
	m_count = 0;
}

template<class T>
void Array<T>::clearMemory()
{
	delete [] m_values;
	init();
}

template<class T>
T& Array<T>::operator[](int index)
{
	xassert_msg(withinBounds(index), "index out of bounds");
	return m_values[index];
}

template<class T>
const T& Array<T>::operator[](int index) const
{
	xassert_msg(withinBounds(index), "index out of bounds");
	return m_values[index];
}

template<class T>
T& Array<T>::first()
{
	return m_values[0];
}

template<class T>
const T& Array<T>::first() const
{
	return m_values[0];
}

template<class T>
T& Array<T>::last()
{
	return m_values[m_count - 1];
}

template<class T>
const T& Array<T>::last() const
{
	return m_values[m_count - 1];
}

template<class T>
int Array<T>::count() const
{
	return m_count;
}

template<class T>
bool Array<T>::isEmpty() const
{
	return m_count == 0;
}

template<class T>
void Array<T>::reserve(int size)
{
	if (size > m_capacity)
		grow(size);
}

template<class T>
void Array<T>::resize(int size)
{
	reserve(size);
	m_count = size;
}

template<class T>
bool Array<T>::withinBounds(int index) const
{
	return index >= 0 && index < count();
}

template<class T>
void Array<T>::grow(int count)
{
	// Determine new capacity
	if (m_capacity < 1)
		m_capacity = 1;
	while (m_capacity < count)
		m_capacity *= 2;

	// Transfer old data to new array
	T* tmp = new T[m_capacity];
	Memory::copy(&m_values[0], tmp, m_count * sizeof(T));

	delete [] m_values;
	m_values = tmp;
}

