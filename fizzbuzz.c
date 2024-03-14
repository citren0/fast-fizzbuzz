#include <stdint.h>
#include <stdio.h>
#include <immintrin.h>

// gcc -O3 -mavx -mavx512f -mavx512vl fizzbuzz.c

#define LOOPS 800000000

__m256i mod(__m256i ini, __m256 mod)
{
	// convert ints to 32 bit floats.
	__m256 oginf = _mm256_cvtepi32_ps(ini);
	__m256 inf = _mm256_cvtepi32_ps(ini);

	// divide by the modulus
	inf = _mm256_div_ps(inf, mod);
	
	// Cast to int.
	__m256i divi = _mm256_cvttps_epi32(inf);

	// Cast back to float.
	inf = _mm256_cvtepi32_ps(divi);

	// Multiply by the modulus
	inf = _mm256_mul_ps(inf, mod);

	// Subtract
	__m256 diff = _mm256_sub_ps(oginf, inf);

	__m256i castback = _mm256_cvtps_epi32(diff);

	return castback;
}


int main()
{
	__m256i ints;
	__m256 mod3, mod5;
	int counter = 0;
	int f;
	int i;

	for (i = 1; i <= LOOPS; i += 8)
	{
		ints = _mm256_set_epi32(i, i+1, i+2, i+3, i+4, i+5, i+6, i+7);
		mod3 = _mm256_set1_ps(3.0f);
		mod5 = _mm256_set1_ps(5.0f);

		__m256i mod3i = _mm256_cvtps_epi32(mod5);

		__m256i mod3post = mod(ints, mod3);
		__m256i mod5post = mod(ints, mod5);
		__m256i mod3and5post = _mm256_or_si256(mod3post, mod5post);

		int mod3buf[8];
		int mod5buf[8];
		int modbothbuf[8];
		_mm256_store_epi32((void *)mod3buf, mod3post);
		_mm256_store_epi32((void *)mod5buf, mod5post);
		_mm256_store_epi32((void *)modbothbuf, mod3and5post);

		for (int f = 7; f >= 0; f--)
		{
			if (modbothbuf[f] == 0)
			{
				printf("FizzBuzz\n");
			}
			else if(mod3buf[f] == 0)
			{
				printf("Fizz\n");
			}
			else if(mod5buf[f] == 0)
			{
				printf("Buzz\n");
			}
			else
			{
				printf("%d\n", i+(7-f));
			}
			
		}

	}

}
