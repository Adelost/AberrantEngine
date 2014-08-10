#pragma once

#include <iostream>
#include <ostream> // std::ostream

// This file allows using "cout" to print various classes.

// ...

#include "Array.h" 
template<class T>
std::ostream& operator << (std::ostream& os, Array<T>& data)
{
	os << "[";
	for (int i = 0; i < data.count() - 1; i++)
		os << data[i] << ", ";
	if (!data.isEmpty())
		os << data.last();
	os << "]";

	return os;
}

#include <vector>
template<class T>
std::ostream& operator << (std::ostream& os, std::vector<T>& data)
{
	os << "[";
	for (size_t i = 0; i < data.size() - 1; i++)
		os << data[i] << ", ";
	if (!data.empty())
		os << data.back();
	os << "]";

	return os;
}