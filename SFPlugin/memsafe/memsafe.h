#ifndef MEMSAFE_H
#define MEMSAFE_H

#include <cstdint>
#include <vector>
#include <windows.h>


int memcpy_safe(void *dest, const void *src, uint32_t len, int check = NULL, const void *checkdata = NULL);
int memset_safe(void *_dest, int c, uint32_t len);
int memcmp_safe(const void *_s1, const void *_s2, uint32_t len);
bool isBadPtr_handlerAny(void *pointer, ULONG size, DWORD dwFlags);

#endif // MEMSAFE_H
