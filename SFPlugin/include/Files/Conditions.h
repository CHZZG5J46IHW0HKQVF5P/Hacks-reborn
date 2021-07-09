#pragma once
#include "stdarg.h"
#include "stddef.h"
#include <cstring>
namespace Lippets
{
	namespace Conditions
	{
		template <typename T>
		inline bool multEqual(T var, size_t elements, ...)
		{
			va_list factor;
			va_start(factor, elements);
			for (size_t i = 0; i < elements; i++)
				if (var == va_arg(factor, T))
					return true;
			va_end(factor);
			return false;
		}

		template <typename T>
		inline bool multEqual2(T var, ...)
		{
			T cp;
			va_list factor;
			va_start(factor, var);
			while (cp = va_arg(factor, T))
				if (var == cp)
					return true;
			va_end(factor);
			return false;
		}

		bool multiStrStr(bool AND, const char *var, size_t elements, ...);
		bool multiStrStr2(bool AND, const char *var, ...); // last parameter always must be zero
		template <typename T>
		inline bool isInBounds(const T &var, const T &min, const T &max)
		{
			return (var >= min && var <= max);
		}

	} // namespace Conditions
} // namespace Lippets		 ]]


inline bool Lippets::Conditions::multiStrStr(bool AND, const char* var, size_t elements, ...)
{
    va_list factor;
    va_start(factor, elements);
    if (AND)
    {
        for (size_t i = 0; i < elements; i++)
            if (!strstr(var, va_arg(factor, char*)))
                return false;
        va_end(factor);
        return true;
    }
    else
    {
        for (size_t i = 0; i < elements; i++)
            if (strstr(var, va_arg(factor, char*)))
                return true;
        va_end(factor);
        return false;
    }
}
inline bool Lippets::Conditions::multiStrStr2(bool AND, const char* var, ...) // last parameter always must be zero
{
    va_list par;
    const char* cp;
    va_start(par, var);
    if (AND) // &&
    {
        while (cp = va_arg(par, const char*))
            if (!strstr(var, cp))
            {
                va_end(par);
                return false;
            }
        va_end(par);
        return true;
    }
    else // ||
    {
        while (cp = va_arg(par, const char*))
            if (strstr(var, cp))
            {
                va_end(par);
                return true;
            }
        va_end(par);
        return false;
    }
}