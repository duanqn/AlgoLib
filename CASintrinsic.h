#pragma once

#include <cstdint>

#ifdef _MSC_VER
#include <intrin.h>
#endif  // _MSC_VER

int32_t CompareAndSwap(int32_t *dest, int32_t compare, int32_t newValue);

#ifdef _MSC_VER
int32_t CompareAndSwap(int32_t *dest, int32_t compare, int32_t newValue){
    static_assert(sizeof(int32_t) == sizeof(long));
    long * longptr = reinterpret_cast<long *>(dest);
    return static_cast<int32_t>(_InterlockedCompareExchange(longptr, newValue, compare));
}
#endif  // _MSC_VER
