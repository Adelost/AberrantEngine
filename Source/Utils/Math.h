#pragma once

namespace ae
{
	/**	Math utility class. */
	class Math
	{
	public:
		static const float PI;
		static const float TWO_PI;
		static const int INT32_MAX;
		static const float FLOAT_MAX;
		static const double DOUBLE_MAX;

		/** Returns "x*x". */
		static float square(float x);
		/** Returns square root of "x". */
		static float sqrt(float x);
		/** Returns "base^exponent". */
		static float pow(float base, float exponent);
		/** Returns the absolute value of "x". */
		static int abs(int x);
		/** Returns the absolute value of "x". */
		static float abs(float x);

		/** Returns the rounded value of "x". */
		static int round(float x);
		/** Returns the value of "x" rounded down. */
		static int roundDown(float x);
		/** Returns the value of "x" rounded up. */
		static int roundUp(float x);
		/** Clamp value of "x" between min and max. */
		static float clamp(float min, float max, float x);
		/** Linear interpolation from "a" to "b". */
		static float lerp(float a, float b, float amount);

		/** Converts radians to degrees. */
		static float degrees(float radians);
		/** Converts degrees to radians. */
		static float radians(float degrees);
		/** Normalizes an angle in radians between -PI and PI. */
		static float normalizeAngle(float radians);
	};
}
