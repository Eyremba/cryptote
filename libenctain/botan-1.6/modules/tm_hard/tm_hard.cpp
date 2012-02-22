/*************************************************
* Hardware Timer Source File                     *
* (C) 1999-2007 The Botan Project                *
*************************************************/

#include "botan-1.6/include/tm_hard.h"
#include "botan-1.6/include/config.h"

namespace Enctain {
namespace Botan {

/*************************************************
* Get the timestamp                              *
*************************************************/
#if defined(BOTAN_TARGET_ARCH_IS_IA32) || defined(BOTAN_TARGET_ARCH_IS_AMD64)

u64bit Hardware_Timer::clock() const
{
    u32bit rtc_low = 0, rtc_high = 0;
    asm volatile("rdtsc" : "=d" (rtc_high), "=a" (rtc_low));
    return ((u64bit)rtc_high << 32) | rtc_low;
}

#elif defined(BOTAN_TARGET_ARCH_IS_PPC) || defined(BOTAN_TARGET_ARCH_IS_PPC64)

u64bit Hardware_Timer::clock() const
{
    u32bit rtc_low = 0, rtc_high = 0;
    asm volatile("mftbu %0; mftb %1" : "=r" (rtc_high), "=r" (rtc_low));
    return ((u64bit)rtc_high << 32) | rtc_low;
}

#elif defined(BOTAN_TARGET_ARCH_IS_ALPHA)

u64bit Hardware_Timer::clock() const
{
    u64bit rtc = 0;
    asm volatile("rpcc %0" : "=r" (rtc));
    return rtc;
}

#elif defined(BOTAN_TARGET_ARCH_IS_SPARC64)

u64bit Hardware_Timer::clock() const
{
    u64bit rtc = 0;
    asm volatile("rd %%tick, %0" : "=r" (rtc));
    return rtc;
}

#else
   #warning "Unsure how to access hardware timer on this system"
#endif
}
}
