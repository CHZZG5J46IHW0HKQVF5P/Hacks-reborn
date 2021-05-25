#include "C:\Lippets\Files\Numbers.h"

bool Lippets::Numbers::Random::rBool()
{
    return rand() % 2;
}

int Lippets::Numbers::Random::rInt(int MAX, int MIN, bool lessThenZero)
{
    if (lessThenZero)
        return rBool() ? -(MIN + rand() % MAX - MIN) : (MIN + rand() % MAX - MIN);
    else
        return MIN + rand() % MAX - MIN;
}
float Lippets::Numbers::Random::rFloat()
{
    return abs((float(rand()) / float((RAND_MAX))));
}

int Lippets::Numbers::ctoi(char number)
{
    return number - 48;
}
float Lippets::Numbers::Map(float value, float begin1, float end1, float begin2, float end2)
{
    return ((value - begin1) / (end1 - begin1)) * (end2 - begin2) + begin2;
}
float Lippets::Numbers::getDistanceBetween2d(float x, float y, float xx, float yy)
{
    return sqrt(pow(x - xx, 2) + pow(y - yy, 2));
}
float Lippets::Numbers::getDistanceBetween(float X, float Y, float Z, float XX, float YY, float ZZ)
{
    return sqrt((X - XX) * (X - XX) + (Y - YY) * (Y - YY) + (Z - ZZ) * (Z - ZZ));
}