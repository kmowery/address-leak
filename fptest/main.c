#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <limits.h>
#include <float.h>


#define NLOOP 1000000

/**
 * Read the time source clock.
 *   &returns: The source clock as a 64-bit unsignd integer.
 */

static inline uint64_t rdtsc()
{
   uint32_t a, d;
 
   __asm__ volatile("rdtsc" : "=a" (a), "=d" (d));
 
   return ((uint64_t)a) | (((uint64_t)d) << 32);
}


int main()
{
	volatile float a, b, c;
	unsigned int i;
	uint64_t tm, base;

	a = 1.0f;
	tm = rdtsc();
	for(i = NLOOP - 1; i != UINT_MAX; i--) {
		b += a * 0.90f;
	}
	tm = rdtsc() - tm;
	base = tm;
	printf("basetime\t%lu\n", tm);

	a = 1.0e-40f;
	tm = rdtsc();
	for(i = NLOOP - 1; i != UINT_MAX; i--) {
		b += a * 0.90f;
	}
	tm = rdtsc() - tm;
	printf("denorm * norm\t%lu\t%.1f%%\n", tm, 100.0f * tm / base);

	a = 1.0e-40f;
	c = 0.0f;
	tm = rdtsc();
	for(i = NLOOP - 1; i != UINT_MAX; i--) {
		b += a * c;
	}
	tm = rdtsc() - tm;
	printf("denorm * 0\t%lu\t%.1f%%\n", tm, 100.0f * tm / base);

	a = 1.0e-40f;
	c = INFINITY;
	tm = rdtsc();
	for(i = NLOOP - 1; i != UINT_MAX; i--) {
		b += a * c;
	}
	tm = rdtsc() - tm;
	printf("denorm * inf\t%lu\t%.1f%%\n", tm, 100.0f * tm / base);

	a = 1.0;
	c = INFINITY;
	tm = rdtsc();
	for(i = NLOOP - 1; i != UINT_MAX; i--) {
		b += a * c;
	}
	tm = rdtsc() - tm;
	printf("norm * inf\t%lu\t%.1f%%\n", tm, 100.0f * tm / base);

	a = FP_NAN;
	c = INFINITY;
	tm = rdtsc();
	for(i = NLOOP - 1; i != UINT_MAX; i--) {
		b += a * c;
	}
	tm = rdtsc() - tm;
	printf("nan * inf\t%lu\t%.1f%%\n", tm, 100.0f * tm / base);

	a = FP_NAN;
	c = 1.0e-40;
	tm = rdtsc();
	for(i = NLOOP - 1; i != UINT_MAX; i--) {
		b += a * c;
	}
	tm = rdtsc() - tm;
	printf("nan * denorm\t%lu\t%.1f%%\n", tm, 100.0f * tm / base);

	a = 1.0e-40f;
	tm = rdtsc();
	for(i = NLOOP - 1; i != UINT_MAX; i--) {
		b += a + 0.90f;
	}
	tm = rdtsc() - tm;
	printf("denorm + norm\t%lu\t%.1f%%\n", tm, 100.0f * tm / base);

	a = 1.0e-40f;
	c = 0.0f;
	tm = rdtsc();
	for(i = NLOOP - 1; i != UINT_MAX; i--) {
		b += a + c;
	}
	tm = rdtsc() - tm;
	printf("denorm + 0\t%lu\t%.1f%%\n", tm, 100.0f * tm / base);

	a = 1.0e-40f;
	c = INFINITY;
	tm = rdtsc();
	for(i = NLOOP - 1; i != UINT_MAX; i--) {
		b += a + c;
	}
	tm = rdtsc() - tm;
	printf("denorm + inf\t%lu\t%.1f%%\n", tm, 100.0f * tm / base);

	a = 1.0;
	c = INFINITY;
	tm = rdtsc();
	for(i = NLOOP - 1; i != UINT_MAX; i--) {
		b += a + c;
	}
	tm = rdtsc() - tm;
	printf("norm + inf\t%lu\t%.1f%%\n", tm, 100.0f * tm / base);

	a = FP_NAN;
	c = INFINITY;
	tm = rdtsc();
	for(i = NLOOP - 1; i != UINT_MAX; i--) {
		b += a + c;
	}
	tm = rdtsc() - tm;
	printf("nan + inf\t%lu\t%.1f%%\n", tm, 100.0f * tm / base);

	a = FP_NAN;
	c = 1.0e-40;
	tm = rdtsc();
	for(i = NLOOP - 1; i != UINT_MAX; i--) {
		b += a + c;
	}
	tm = rdtsc() - tm;
	printf("nan + denorm\t%lu\t%.1f%%\n", tm, 100.0f * tm / base);

	return 0;
}
