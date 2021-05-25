#include "C:\Lippets\Files\Conditions.h"

bool Lippets::Conditions::multiStrStr(bool AND, const char *var, size_t elements, ...)
{
    va_list factor;
    va_start(factor, elements);
    if (AND)
    {
        for (size_t i = 0; i < elements; i++)
            if (!strstr(var, va_arg(factor, char *)))
                return false;
        va_end(factor);
        return true;
    }
    else
    {
        for (size_t i = 0; i < elements; i++)
            if (strstr(var, va_arg(factor, char *)))
                return true;
        va_end(factor);
        return false;
    }
}
bool Lippets::Conditions::multiStrStr2(bool AND, const char *var, ...) // last parameter always must be zero
{
    va_list par;
    const char *cp;
    va_start(par, var);
    if (AND) // &&
    {
        while (cp = va_arg(par, const char *))
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
        while (cp = va_arg(par, const char *))
            if (strstr(var, cp))
            {
                va_end(par);
                return true;
            }
        va_end(par);
        return false;
    }
}