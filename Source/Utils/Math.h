#pragma once

class Math
{
public:
	Math();

	static const float PI;
	static const float TWO_PI;
	static const int INT32_MAX;
	static const float FLOAT_MAX;
	static const double DOUBLE_MAX;

	static float square(float x);
	static float sqrt(float x);
	static float pow(float base, float exponent);
	static int abs(int x);
	static float abs(float x);

	static int round(float x);
	static int roundDown(float x);
	static int roundUp(float x);
	/// Clamp value between min and max
	static float clamp(float min, float max, float x);
	/// Linear interpolation from a to b
	static float lerp(float a, float b, float amount);

	static float degrees(float radians);
	static float radians(float degrees);
	/// Normalizes an angle in radians between -PI and PI
	static float normalizeAngle(float radians);

	static void initRandomSeed();
	static int randomInt(int max);
	static int randomInt(int min, int max);
	static float randomFloat(float min, float max);
};
