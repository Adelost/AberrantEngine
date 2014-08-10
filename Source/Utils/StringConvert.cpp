#include "StringConvert.h"

#include <sstream> // stringstream

std::string StringConvert::toString(int a)
{
	return std::to_string(a);
}

std::string StringConvert::toString(float a)
{
	return std::to_string(a);
}

std::string StringConvert::toString(bool a)
{
	if (a)
		return "True";
	return "False";
}

int StringConvert::toInt(std::string s)
{
	int n;
	std::stringstream ss(s);
	ss >> n;
	if (ss.fail())
		n = -1;
	return n;
}

float StringConvert::toFloat(std::string s)
{
	float n;
	std::stringstream ss(s);
	ss >> n;
	if (ss.fail())
		n = -1.0f;
	return n;
}
