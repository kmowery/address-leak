#include <stdio.h>
#include <stdint.h>
#include "util.h"


int main()
{
	int i;
	volatile float a, b, x;
	uint64_t base, denorm, zero;

	a = 1.0f;
	x = 0.1f;
	base = rdtsc();
	for(i = 0; i < 500000; i++)
		b = a * x;
	base = rdtsc() - base;

	a = 1e-43f;
	x = 0.1f;
	denorm = rdtsc();
	for(i = 0; i < 500000; i++)
		b = a * x;
	denorm = rdtsc() - denorm;

	a = 1e-43f;
	x = 0.0f;
	zero = rdtsc();
	for(i = 0; i < 500000; i++)
		b = a * x;
	zero = rdtsc() - zero;

	printf("denorm: %f\n", (float)denorm / (float)base);
	printf("zero: %f\n", (float)zero / (float)base);

	return 0;
}
