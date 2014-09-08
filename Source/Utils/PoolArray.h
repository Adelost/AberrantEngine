#pragma once

#include "Array.h"
#include "Math.h"
#include "XAssert.h"

/// Template class that provides pool-based allocation of elements
/**
    Container structure useful when fast allocation and
    deallocation of elements is needed. Adding and removing
	elements is O(1) average and O(n) worst case.

	Works by the same principle as a pool allocator. Same
    size elements are allocated in a preallocated memory
    block. The structure is traversed linearly, as an array,
    as compared to a more common linked list approach. An
    iterator is needed to traverse the values stored inside,
    as the array may contain gaps.
*/

template<class T>
class PoolArray
{
public:
	PoolArray()
	{
		clear();
	}
	void clear()
	{
		m_count = 0;
		m_firstGap = 0;
		m_lastGap = 0;
	}

	// Adds value to container, returns index where value was stored
	int add(const T& value)
	{
		// Add element, reuse gaps if any
		int index = nextIndex();
		xassert_msg(index <= m_values.count(),
		            "index is larger than array, this should never happen");
		if (index == m_values.count())
		{
			m_values.addEmpty();
			m_gaps.addEmpty();
		}
		m_values[index] = value;
		m_gaps[index] = false;
		m_count++;

		// Find next gap
		findNextGap();

		return index;
	}
	void removeAt(int index)
	{
		if (!isGap(index))
		{
			// Remove value
			m_gaps[index] = true;
			m_count--;

			// Check if new first gap is
			// needed
			if (index < m_firstGap)
				m_firstGap = index;

			// If value was next to last gap
			// a new gap is needed
			if (index == m_lastGap - 1)
			{
				findNextLastGap();
			}
		}
	}

	int nextIndex()
	{
		return m_firstGap;
	}

	/// Returns element at index, do not use to iterate, use iterator instead
	T& operator[](int index)
	{
		return m_values[index];
	}

// 	void debug()
// 	{
// 		using namespace std;
// 		cout << "-------------" << endl;
// 		for (int i = 0; i < m_firstGap; i++)
// 		{
// 			cout << "  ";
// 		}
// 		cout << "<" << endl;
// 		for (int i = 0; i < m_values.count(); i++)
// 		{
// 			if (isGap(i))
// 				cout << "# ";
// 			else
// 				cout << m_values[i] << " ";
// 		}
// 		cout << endl;
// 		for (int i = 0; i < m_lastGap; i++)
// 		{
// 			cout << "  ";
// 		}
// 		cout << ">" << endl;
// 	}

protected:
	bool isGap(int index) const
	{
		return m_gaps[index];
	}
	void findNextGap()
	{
		// Step forward until new gap is found
		// or until end is reached.
		m_firstGap++;
		while (m_firstGap < m_lastGap && !isGap(m_firstGap))
		{
			m_firstGap++;
		}

		if (m_lastGap < m_firstGap)
			m_lastGap = m_firstGap;
	}
	void findNextLastGap()
	{
		m_lastGap--;
		while (m_lastGap > 0 && isGap(m_lastGap - 1))
		{
			m_lastGap--;
		}
	}

	Array<T> m_values;
	Array<bool> m_gaps;

	int m_firstGap;
	int m_lastGap;

	int m_count;


	#pragma region Iterator
public:
	class Iterator
	{
	public:
		Iterator(PoolArray* target, int index)
		{
			m_target = target;
			m_index = index;
			ignoreGaps()
		}
		void reset()
		{
			m_index = 0;
		}
		bool operator!=(const Iterator& other) const
		{
			return m_index < other.m_index;
		}
		T& operator*()
		{
			return m_target->m_values[m_index];
		}
		const T& operator*() const
		{
			return m_target->m_values[m_index];
		}
		const Iterator& operator++()
		{
			m_index++;
			ignoreGaps();

			return *this;
		}

	private:
		void ignoreGaps()
		{
			while (m_index < m_target->m_lastGap && m_target->isGap(m_index))
			{
				m_index++;
			}
		}

		int m_index;
		PoolArray* m_target;
	};
	Iterator begin()
	{
		return Iterator(this, 0);
	}
	Iterator end()
	{
		return Iterator(this, m_lastGap);
	}
	#pragma endregion
};





//////////////////////////////////////////////////////////////////////////
// Useful when debugging
//////////////////////////////////////////////////////////////////////////
/*


    #include "StopWatch.h"
    void profile()
    {
	StopWatch watch;
	int tmp = false;

	watch.start();

	for (int j = 0; j < 1000; j++)
	{
		for (int i = 0; i < m_array.count(); i++)
		{
			tmp += *(int*)&m_array[i];
		}
	}

	std::cout << "Time 1: " << watch.stop() << std::endl;

	watch.start();

	for (int j = 0; j < 1000; j++)
	{
		for (int i = 0; i < m_gaps.count(); i++)
		{
			tmp += *(int*)&m_gaps[i];
		}
	}

	std::cout << "Time 2: " << watch.stop() << std::endl;
	std::cout << "Control: " << tmp << std::endl;
    }
*/