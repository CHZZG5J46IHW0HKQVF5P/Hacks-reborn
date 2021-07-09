#pragma once

#include <cmath>
#include <cfloat>
#include <string>

typedef unsigned short shsize;
namespace Lippets
{
	namespace Numbers
	{
		namespace Random
		{
			inline bool rBool()
			{
				return rand() % 2;
			}
			inline int rInt(int MAX, int MIN, bool lessThenZero)
			{
				if (lessThenZero)
					return rBool() ? -(MIN + rand() % MAX - MIN) : (MIN + rand() % MAX - MIN);
				else
					return MIN + rand() % MAX - MIN;
			}
			inline float rFloat()
			{
				return abs((float(rand()) / float((RAND_MAX))));
			}
		} // namespace Random
		inline int ctoi(char number)
		{
			return number - 48;
		}
		inline float Map(float value, float begin1, float end1, float begin2, float end2)
		{
			return ((value - begin1) / (end1 - begin1)) * (end2 - begin2) + begin2;
		}
		inline float getDistanceBetween2d(float x, float y, float xx, float yy)
		{
			return sqrtf(pow(x - xx, 2) + pow(y - yy, 2));
		}
		inline float getDistanceBetween(float X, float Y, float Z, float XX, float YY, float ZZ)
		{
			return sqrtf((X - XX) * (X - XX) + (Y - YY) * (Y - YY) + (Z - ZZ) * (Z - ZZ));
		}
	}
} // namespace Lippets

