#pragma once

#include "Cast.h"
#include "Memory.h"
#include "XAssert.h"

namespace ae
{
//! A resizable container, which stores elements in adjacent memory
//! locations and provides a fast index-based lookup.
//!
//!	It is many ways similar to std::vector, but has a more readable implementation and additional
//! convenience methods.
//!
//! - Elements are reallocated when growing, causing any pointers
//!   pointing to elements inside the container to become invalidated.
//!	- Does not allocate on heap until a first element is added to it.
//!	- Supports C++11 iterators to make iterating more convenient.
//!	- Allows adding multiple elements on a single line using the output
//!	  stream operator (<<).
//! - Provides out of bound checking in debug.
template<class T>
class Array
{
public:
	//! Constructs an empty container.
	Array()
	{
		m_elements = nullptr;
		m_count = 0;
		m_capacity = 0;
	}

	//! Constructs a Array with an initial size of "size" elements
	//! constructed using default constructor.
	Array(int size)
	{
		m_elements = new T[size];
		m_count = size;
		m_capacity = size;
	}
	//! Constructs a copy of "other".
	Array(const Array<T>& other) : Array()
	{
		*this = other;
	}
	//! Destroys the container and all elements.
	~Array()
	{
		clearMemory();
	}


	//! Copies the elements of "other" to this container, replacing
	//! its current contents, and modifying its size accordingly.
	Array<T>& operator=(const Array<T>& other)
	{
		clear();
		addAll(other.raw(), other.count());

		return *this;
	}

	//! Same as add(), overloading stream operator allows adding
	//! multiple elements.
	Array<T>& operator<<(const T& element)
	{
		add(element);

		return *this;
	}
	//! Returns element at the specified index.
	T& operator[](int index)
	{
		return CALL_CONST_METHOD_AS_NON_CONST(operator[](index));
	}

	const T& operator[](int index) const
	{
		xassert_msg(isInside(index), "Index out of bounds.");

		return m_elements[index];
	}


	//! Adds an element to the container.
	void add(const T& element)
	{
		reserve(m_count + 1);
		Memory::construct(element, m_elements[m_count]);
		m_count++;
	}
	//! Adds multiple element to the container from a pointer to an
	//! array.
	void addAll(const T* elements, int count)
	{
		reserve(m_count + count);
		for (int i = 0; i < count; i++)
			Memory::construct(elements[i], m_elements[m_count + i]);
		m_count += count;
	}
	//! Inserts an element at specified index. Subsequent elements are
	//! transposed to cover the resulting gap, which may be a slow
	//! operation depending of the number of elements.
	void addAt(int index, const T& element)
	{
		addAt(index, &element, 1);
	}

	//! Adds an uninitialized elements.
	void addRaw(int count = 1)
	{
		resize(m_count + count);
	}

	//! Same as addAt() but allows adding multiple elements.
	void addAt(int index, const T* elements, int count)
	{
		// Shift elements right to create a gap
		reserve(m_count + count);
		int size = m_count - index;
		Memory::move(&m_elements[index], &m_elements[index + count], size);

		// Add elements
		for (int i = 0; i < count; i++)
			Memory::construct(elements[i], m_elements[index + i]);
		m_count += count;
	}
	//! Removes the last element.
	void removeLast()
	{
		xassert_msg(!isEmpty(), "No elements to remove.");
		last().~T();
		m_count--;
	}

	//! Removes element at index. Subsequent elements are transposed
	//! to cover the resulting gap. See also addAt().
	void removeAt(int index)
	{
		removeAt(index, 1);
	}

	//! Same as removeAt() but allows removing multiple elements.
	void removeAt(int index, int count)
	{
		xassert_msg(m_count - count >= 0, "No elements to remove.");

		// Remove elements
		for (int i = 0; i < count; i++)
			m_elements[index + i].~T();
		m_count -= count;

		// Shift right segment left to cover gap
		int rightSize = m_count - index;
		Memory::move(&m_elements[index + count], &m_elements[index], rightSize);
	}
	//! Fast removal of element by swapping the last element with the
	//! element deleted.
	void swapRemove(int index)
	{
		xassert_msg(!isEmpty(), "No elements to remove.");
		m_elements[index].~T();
		Memory::copy(&m_elements[m_count - 1], &m_elements[index], 1);
		m_count--;
	}

	//! Removes all elements.
	void clear()
	{
		for (int i = count() - 1; i >= 0; i--)
			m_elements[i].~T();
		m_count = 0;
	}
	//! Removes all elements without calling destructor.
	void clearRaw();
	//! Removes all elements and releases any allocated memory.
	void clearMemory()
	{
		clear();

		Memory::deallocate(m_elements);
		m_elements = nullptr;
		m_capacity = 0;
	}

	//! If "size" exceeds capacity, more memory is allocated until
	//! capacity is enough to hold "size" elements.
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
	//! Same as reserve(), except that the growth in capacity is
	//! limited to exactly "size" elements. This allows saving memory
	//! in some situation.
	void reserveExact(int size)
	{
		if (size > m_capacity)
		{
			m_capacity = size;

			T* tmp = Memory::allocate<T>(m_capacity);
			Memory::copy(m_elements[0], tmp[0], m_count);
			Memory::deallocate(m_elements);
			m_elements = tmp;
		}
	}
	//! Resized the container so that it contains "size" elements. New
	//! elements are uninitialized.
	void resize(int size)
	{
		if (size > m_count)
		{
			reserve(size);

			for (int i = m_count; i < m_count; i++)
				Memory::construct(T(), m_elements[i]);

			m_count = size;
		}
	}
	//! Returns the index of an element inside the container. Element
	//! must already be residing inside the container. Useful in some
	//! rare situations where an element do not know its index.
	int indexFromElement(T* element)
	{
		int index = static_cast<int>(&m_values[0] - &value);
		xassert_msg(isInside(index), "Element do not reside inside container.");

		return index;
	}

	//! Constructs element at index.
	void construct(const T& element, int index)
	{
		Memory::construct(element, m_elements[m_count]);
	}
	//! Destructs object at index.
	void destruct(int index)
	{
		Memory::destroy(m_elements[index]);
	}

	//! Returns the first item.
	T& first()
	{
		return CALL_CONST_METHOD_AS_NON_CONST(first());
	}
	const T& first() const
	{
		return (*this)[0];
	}

	//! Returns the last item.
	T& last()
	{
		return CALL_CONST_METHOD_AS_NON_CONST(last());
	}
	const T& last() const
	{
		return (*this)[m_count - 1];
	}
	//! Exposes the raw pointer storing the elements of the container.
	//! The pointer can be used to modify elements and remains valid
	//! as long as the container is not reallocated.
	T* raw()
	{
		return CALL_CONST_METHOD_AS_NON_CONST(raw());
	}

	const T* raw() const
	{
		return m_elements;
	}
	//! Returns the number of stored elements.
	int count() const
	{
		return m_count;
	}


	//! Returns the number of elements the array can contain before
	//! needing to resize.
	int capacity() const
	{
		return m_capacity;
	}
	//! Returns true if array contains no elements.
	bool isEmpty() const
	{
		return m_count == 0;
	}
	//! Returns true if adding another element will cause the array to
	//! resize.
	bool isFull() const
	{
		return m_count >= m_capacity;
	}
	//! Checks if "index" is within the boundaries of the array.
	bool isInside(int index) const
	{
		return index >= 0 && index < count();
	}

private:
	//T m_allocator;
	T* m_elements;
	int m_capacity;
	int m_count;

public:
	#pragma region Iterator
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
}