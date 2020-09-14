## Applications of multi-threading

1. Write a multi-threaded program with 2 threads to add the numbers in a large array. The first thread adds the first half elements, the second thread adds the second half elements. Also, write a non-threaded program to compute the result. Do you get the same answer? 

Now, write a generalised version of this code, which can allow any number of threads. If you use the ceil function from math.h, how do you compile the program?

This program can be written in two ways - one create the array as a global variable; second pass the array as an argument to the n threads. Write both implementations. Do you get the same answer both the implementations?

What is the maximum number of threads that works for you? What is thr maximum allowed number of threads?

**Bonus** Study multi-processing and multi-threading in Python. Use `pool` to parallelize image processing on a large batch of images. Do some simple operation like batch convert from colour to grayscale.


## Empirical evaluation/scientific experiments
**Bonus** Vary the number of threads and compute time v/s number of threads. Vary the size of the array now to see if more threads means more performance.

## Try to build a trivial lock without hardware support
2. Use load-store to implement a basic version of a lock. See Book 28.6. Run the program and confirm that this lock still does not solve the issue of mutual exclusion. Use `objdump` to disassemble the code and find the critical section.

Use `atomic` types in c11 to create correct concurrent thread program to increment counter. Reference: https://lumian2015.github.io/lockFreeProgramming/c11-features-in-currency.html

**Bonus** Compute the time spent spinning on the CPU waiting for the other thread to release the lock.

## Build a correct lock!
3. Use pthread mutex to write a fully correct working version of a multi-threaded program which shares a variable count across multiple threads. Increment the variable in each thread for a given number of times in a loop.. Use `objdump` to disassemble the code and find out more.

## Tools for threads and synchronisation
4. Questions 1 and 2 from the textbook Chapter 27 (Threads API).

## Mixing assembly and C
5. Write a simple single threaded program in C to increment a number by 1. The increment should be done via inline assembly.

## Build your own thread using assembly and atomic hardware instructions
6. Use `xchg` instruction in assembly to build your own lock. Test for its correctness by comparing to Q3.


