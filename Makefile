any: fizzbuzz.c
	gcc -O3 -mavx -mavx512f -mavx512vl fizzbuzz.c -o fizzbuzz

clean:
	rm fizzbuzz
