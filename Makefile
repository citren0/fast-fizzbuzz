any: fizzbuzz.c
	gcc -Ofast -march=native -mavx fizzbuzz.c -o fizzbuzz

debug: fizzbuzz.c
	gcc -Og -march=native -g -mavx fizzbuzz.c -o fizzbuzz

basic: basic.c
	gcc basic.c -o fizzbuzz

clean:
	rm fizzbuzz

run:
	./fizzbuzz | pv > /dev/null
