#pragma once
#ifndef __NUMBERS_H__
#define __NUMBERS_H__
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
			bool rBool();
			int rInt(int MAX, int MIN, bool lessThenZero);
			float rFloat();
		} // namespace Random
		int ctoi(char number);
		float Map(float value, float begin1, float end1, float begin2, float end2);
		float getDistanceBetween2d(float x, float y, float xx, float yy);
		float getDistanceBetween(float X, float Y, float Z, float XX, float YY, float ZZ);
	}
} // namespace Lippets
#endif // __NUMBERS_H__