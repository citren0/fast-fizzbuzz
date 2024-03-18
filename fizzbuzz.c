#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <immintrin.h>


#define LOOPS 800000000

#define OUTBUFSIZE 16384
char outbuf[OUTBUFSIZE];
int cursor = 0;


// ITOA by Robert Jan Schaper
char * itoa(char * buf, int val)
{
	int i = 30;
	register int base = 10;
	
	for(; val && i ; --i, val /= base)
	{
		buf[i] = "0123456789abcdef"[val % base];
	}
	
	return &buf[i+1];
	
}


void writeToOutBuf(char * str, int length)
{
	if (cursor + length >= OUTBUFSIZE)
	{
		fwrite(outbuf, 1, OUTBUFSIZE, stdout);
		cursor = 0;
	}

	memcpy(&outbuf[cursor], str, length);
	cursor += length;
}


__m256i mod(__m256i ini, __m256 mod)
{
	// convert ints to 32 bit floats.
	__m256 oginf = _mm256_cvtepi32_ps(ini);
	__m256 inf = _mm256_cvtepi32_ps(ini);

	// divide by the modulus
	inf = _mm256_div_ps(inf, mod);

	__m256 offset = _mm256_set1_ps(0.05f);
	inf = _mm256_add_ps(inf, offset);
	
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


// Broken mod?
// __m256i mod(__m256i ini, __m256i modi)
// {
// 	// convert ints to 32 bit floats.
// 	__m256 inf = _mm256_cvtepi32_ps(ini);
// 	__m256 modf = _mm256_cvtepi32_ps(modi);

// 	// divide by the modulus
// 	inf = _mm256_div_ps(inf, modf);
	
// 	// Cast to int.
// 	__m256i divi = _mm256_cvttps_epi32(inf);

// 	// Multiply by the modulus
// 	__m256i in2 = _mm256_mul_epi32(divi, modi);

// 	// Subtract
// 	__m256i diff = _mm256_sub_epi32(ini, in2);

// 	return diff;
// }


int main()
{
	int err;
	err = setvbuf(stdout, NULL, _IOFBF, OUTBUFSIZE);

	if (err != 0)
	{
		exit(1);
	}

	register __m256i ints;
	register __m256 mod3;
	register __m256 mod5;
	register __m256i mod3post, mod5post, mod3and5post;
	int counter = 0;
	int f;
	int i;
	int32_t mod3ex, mod5ex, modexboth;
	char arr1[32];
	char * arr2;

	for (i = 1; i <= LOOPS; i += 8)
	{
		ints = _mm256_set_epi32(i, i+1, i+2, i+3, i+4, i+5, i+6, i+7);
		mod3 = _mm256_set1_ps(3.0f);
		mod5 = _mm256_set1_ps(5.0f);

		__m256i mod3post = mod(ints, mod3);
		__m256i mod5post = mod(ints, mod5);
		__m256i mod3and5post = _mm256_or_si256(mod3post, mod5post);

		for (int f = 0; f < 8; f++)
		{

			switch(f)
			{
				case 0:
					mod3ex = _mm256_extract_epi32(mod3post, 7);
					mod5ex = _mm256_extract_epi32(mod5post, 7);
					modexboth = _mm256_extract_epi32(mod3and5post, 7);
					break;
				case 1:
					mod3ex = _mm256_extract_epi32(mod3post, 6);
					mod5ex = _mm256_extract_epi32(mod5post, 6);
					modexboth = _mm256_extract_epi32(mod3and5post, 6);
					break;
				case 2:
					mod3ex = _mm256_extract_epi32(mod3post, 5);
					mod5ex = _mm256_extract_epi32(mod5post, 5);
					modexboth = _mm256_extract_epi32(mod3and5post, 5);
					break;
				case 3:
					mod3ex = _mm256_extract_epi32(mod3post, 4);
					mod5ex = _mm256_extract_epi32(mod5post, 4);
					modexboth = _mm256_extract_epi32(mod3and5post, 4);
					break;
				case 4:
					mod3ex = _mm256_extract_epi32(mod3post, 3);
					mod5ex = _mm256_extract_epi32(mod5post, 3);
					modexboth = _mm256_extract_epi32(mod3and5post, 3);
					break;
				case 5:
					mod3ex = _mm256_extract_epi32(mod3post, 2);
					mod5ex = _mm256_extract_epi32(mod5post, 2);
					modexboth = _mm256_extract_epi32(mod3and5post, 2);
					break;
				case 6:
					mod3ex = _mm256_extract_epi32(mod3post, 1);
					mod5ex = _mm256_extract_epi32(mod5post, 1);
					modexboth = _mm256_extract_epi32(mod3and5post, 1);
					break;
				case 7:
					mod3ex = _mm256_extract_epi32(mod3post, 0);
					mod5ex = _mm256_extract_epi32(mod5post, 0);
					modexboth = _mm256_extract_epi32(mod3and5post, 0);
					break;
			}

			if (modexboth == 0)
			{
				writeToOutBuf("FizzBuzz\n", 9);
			}
			else if(mod3ex == 0)
			{
				writeToOutBuf("Fizz\n", 5);
			}
			else if(mod5ex == 0)
			{
				writeToOutBuf("Buzz\n", 5);
			}
			else
			{
				arr2 = itoa(arr1, i+f);
				writeToOutBuf(arr2, strlen(arr2));
				writeToOutBuf("\n", 1);
			}
			
		}

	}

}
