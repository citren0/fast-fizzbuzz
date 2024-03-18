# Fast Fizzbuzz

There exists a challenge on the internet to write the fastest FizzBuzz program.

You can read about it here: [https://codegolf.stackexchange.com/questions/215216/high-throughput-fizz-buzz](https://codegolf.stackexchange.com/questions/215216/high-throughput-fizz-buzz)

The most basic, standard implementation is in basic.c, with my more sophisticated solution in fizzbuzz.c.

I chose to write mine with AVX2 instructions and can achieve a throughput of 430 MiB/s on my laptop.

This is a work in progress, and you will likely see it improve over time.

## Build

    $ make

## Clean

    $ make clean

## Run and Benchmark

    $ ./fizzbuzz | pv > /dev/null
