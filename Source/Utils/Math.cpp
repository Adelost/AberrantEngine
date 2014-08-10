#include "Math.h"

#include "StaticCall.h"

#include <cmath> // abs, sqrt
#include <cassert> // assert
#include <time.h> // time
#include <stdlib.h> // srand
#include <limits.h> // int max
#include <float.h> // float max

// Constants
const float Math::PI = 3.141592741f;
const float Math::TWO_PI = PI * 2.0f;
const int Math::INT32_MAX = INT_MAX;
const float Math::FLOAT_MAX = FLT_MAX;
const double Math::DOUBLE_MAX = DBL_MAX;

// Init constructor automatically
STATIC_CALL(Math math;)

Math::Math()
{
	// Init random seed
	initRandomSeed();
}

float Math::degrees(float radians)
{
	return radians * (180.f / PI);
}

float Math::radians(float degrees)
{
	return degrees * (PI / 180.f);
}

void Math::initRandomSeed()
{
	srand((unsigned int)time(nullptr));
}

int Math::randomInt(int max)
{
	return rand() % max + 1;
}

int Math::randomInt(int min, int max)
{
	return rand() % (max - min + 1) + min;
}

float Math::randomFloat(float min, float max)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	random = random * (max - min);
	return min + random;
}

float Math::normalizeAngle(float radians)
{
	radians += PI;
	float d = (float)(roundDown(radians / TWO_PI));
	radians -= d * TWO_PI;
	radians -= PI;
	return radians;
}

int Math::round(float x)
{
	return (int)(x + 0.5f);
}

float Math::lerp(float a, float b, float amount)
{
	return a * amount + b * (1.0f - amount);
}

int Math::roundUp(float x)
{
	if ((int)x < x)
		++x;
	return (int)x;
}

int Math::roundDown(float x)
{
	return (int)x;
}

float Math::clamp(float min, float max, float x)
{
	if (x < min) return min;
	if (x > max) return max;
	return x;
}

float Math::square(float x)
{
	return x * x;
}

float Math::sqrt(float x)
{
	return ::sqrt(x);
}

float Math::pow(float base, float exponent)
{
	return ::powf(base, exponent);
}

int Math::abs(int x)
{
	return ::abs(x);
}

float Math::abs(float x)
{
	return ::abs(x);
}


