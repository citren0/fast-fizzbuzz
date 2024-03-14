any: fizzbuzz.c
	gcc -O3 -march=native -mavx fizzbuzz.c -o fizzbuzz

debug: fizzbuzz.c
	gcc -O3 -march=native -g -mavx fizzbuzz.c -o fizzbuzz

clean:
	rm fizzbuzz
