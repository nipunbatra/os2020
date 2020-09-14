### Lab assignment for 26th Sept 2018 for CSE 301

Reference: https://computing.llnl.gov/tutorials/pthreads/

*NB: The bonus questions will not be discussed for the whole class. Some of them are open ended too. Every few minutes the instructor will solve the questions for the whole class. You can also find the solutions here.*

1. Write a simple hello world program which uses 2 threads, each displaying its unique number/id - A and B. What happens if you do not use `join`? Extend the above program to use `join`.

Now create an array of 20 threads and the argument to be passed these threads is integer 1-20.
Use join to ensure a specific thread ordering. Run this program multiple times to show that the ordering between different threads can be different on different runs. 
 
In each of these threads define a variable x. Print the address of x? Do you see different addressed per thread? Why is this the case?

**Bonus** Use `pstree`, `ps`, `top` to dig more information about these threads. You may need to add some delays in the code to be able to see the results of these commands.

2. Write a program to pass multiple arguments to the calling thread function. Hint use structs.

**Bonus** Use `pstree`, `ps`, `top` along with watch to see how more threads are getting created.

3. Write a multi-threaded program which shares a variable count across multiple threads. Increment the variable in each thread for a given number of times in a loop. Use `objtool` to disassemble the code and find the critical section.
