#pragma once

#include "Array.h"
#include "PoolArray.h"

// TODO: Not done

template<class T>
class Memory
{
public:
	PoolAllocator()
	{

	}
private:
	Array<T> m_memory;
};


template<class T>
class PoolAllocator
{
private:
	class Memory
	{

	};

public:
	PoolAllocator()
	{
		add();
	}
	void add()
	{
	}

private:
	int m_count;
	Array<Memory> m_memory;
	PoolArray<T*> m_memory;
};

