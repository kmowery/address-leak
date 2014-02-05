#ifndef UTIL_H
#define UTIL_H

/**
 * Read the time source clock.
 *   &returns: THe source clock as a 64-bit unsignd integer.
 */

static inline uint64_t rdtsc()
{
   uint32_t a, d;
 
   __asm__ volatile("rdtsc" : "=a" (a), "=d" (d));
 
   return ((uint64_t)a) | (((uint64_t)d) << 32);
}

#endif
