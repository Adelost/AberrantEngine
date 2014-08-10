#pragma once

#include <string>

class StringConvert
{
public:
	static float toFloat(std::string s);
	static int toInt(std::string s);
	static std::string toString(float a);
	static std::string toString(int a);
	static std::string toString(bool a);
};