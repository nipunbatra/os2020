---
layout: page
permalink: /labs/
title: Labs
description: "Questions and Solutions for all Labs held"
---

# Table of Contents
- [Lab 1](#lab-1)
  * [Question 1](#question-1)
  * [Question 2](#question-2)
  * [Question 3](#question-3)
  * [Question 4](#question-4)
  * [Question 5](#question-5)
  * [Question 6](#question-6)
  * [Question 7](#question-7)
  * [Question 8](#question-8)
  * [Question 9](#question-9)
  * [Question 10](#question-10)
  * [Question 11](#question-11)
  * [Question 12](#question-12)
  * [Question 13](#question-13)
  * [Question 14](#question-14)
  * [Question 15](#question-15)
  * [Question 16](#question-16)
- [Lab 2](#lab-2)
  * [Question 1](#question-1-1)
  * [Question 2](#question-2-1)
  * [Question 3](#question-3-1)
  * [Question 4](#question-4-1)
  * [Question 5](#question-5-1)
  * [Question 6](#question-6-1)
  * [Question 7](#question-7-1)
  * [Question 8](#question-8-1)

# Lab 1
### Question 1
**Q:** Fire the terminal and run the `ps` command on the terminal without any arguments. What output do you see? Where is this program being run?

**A:** 
Reports a snapshot of the current processes. By default it returns the Process ID, the terminal, the duration, and command that is running. The TTY corresponding to ps gives the terminal in which this ps command is running.

### Question 2
**Q:** Fire up a program. Can you see it using `ps`?

**A:** No. To list all programs run by the user run `ps -e` instead of `ps`. 

### Question 3
**Q:** Look at the manual for ps using man ps. Try out the command with all the flags and note the output in each case.

**A:** 
Run `man ps` in your terminal

### Question 4
**Q:** How can you get details of all the running processes?

**A:** 
Run `ps -e -l` in your terminal. The `-e` option displays all processes running. The `-l` option is for displaying the information in long format i.e. to display more information for each process than the plain `ps` command.

### Question 5
**Q:** Which order are the above processes sorted by? Can you sort them using same criteria but opposite order?

**A:** 
They processes are sorted by the process ID by default. Inorder to reverse sort by process ID use `ps --sort -pid -e`.

### Question 6
**Q:** Can you sort them using some other criteria? i.e. by CPU usage?

**A:** Use `ps --sort=-%cpu -au`. `-au` gives all the information about the processes run by the current user.

### Question 7
**Q:** Use ps to find unique users?

**A:** 
Run `ps -eo user --no-header | sort -u`.

### Question 8
**Q:** Find number of processes per user.

**A:** 
Run `ps -eo user --no-header | sort | uniq -c`.

### Question 9
**Q:** Find process by PID.

**A:** 
Run `ps <PID>`. If the process you want to see has PID 1234, run `ps 1243` to find its parent.

### Question 10
**Q:** Find its parent.

**A:** 
Run `ps -o ppid= -p <PID>`. If the child has PID 1234, run `ps -o ppid= -p 1234`.

### Question 11
**Q:** Find details of multiple processes using PID list.

**A:** 
If you want to find information about PIDs 123, 234 and 456 run `ps =p 123,234,456`.

### Question 12
**Q:** Use `-o` to output PID, PPID.

**A:** Run `ps -o pid,ppid`.

### Question 13
**Q:** Find total running time of all processes.

**A:** For running time of single process (suppose PID is 1) run `ps -p -1 -o etime`. For running time of all processes run `ps -eo user, label, etime`.

### Question 14
**Q:** Sort processes in decreasing order of running time.

**A:** Run `ps -eo user, label, etime --sort=-etime`.

### Question 15
**Q:** Use `watch` utility to perform real-time monitoring over `ps`.

**A:** Run `watch -n 1 'ps -eo pid,ppid,cmd,%mem,%cpu --sort=-%mem | head'`. `-n 1` specifies the refresh rate to be 1 second. You can set it to decimals like 0.1 seconds (`-n 0.1`) too.

### Question 16
**Q:** Change the monitoring period of watch

**A:** Run `watch -n 0.1 'ps -eo pid,ppid,cmd,%mem,%cpu --sort=-%mem | head'`. `-n 0.1` specifies the monitoring frequency to be 0.1 seconds.

# Lab 2

### Question 1
**Q:** Write a program that calls `fork()`. Before calling `fork()`, have the main process access a variable (e.g., `x`) and set its value to something (e.g., `100`). What value is the variable in the child process? What happens to the variable when both the child and parent change the value of x? 

**Code:**
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 
int main(int argc, char *argv[])
{
    int myVariable = 100;
    printf("hello world (pid:%d)\n", (int)getpid());
    printf("Value of myVariable before fork is %d\n", myVariable);
    int rc = fork();
    if (rc < 0)
    {
        // fork failed; exit`
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        // child (new process)
        printf("hello, I am child (pid:%d)\n", (int)getpid());
        printf("Value of myVariable from child is %d\n", myVariable);
        printf("Changing the value of myVariable in child to 200\n");
        myVariable = 200;
        printf("The changed value of myVariable from child is %d\n", myVariable);
    }
    else
    {
        // parent goes down this path (original process)
        printf("hello, I am parent of %d (pid:%d)\n",
               rc, (int)getpid());
        printf("Value of myVariable from parent after fork is %d\n", myVariable);
        printf("Changing the value of myVariable in parent to 300\n");
        myVariable = 300;
        printf("The changed value of myVariable from parent is %d\n", myVariable);
    }
    return 0;
}
```

**Output:**
```
hello world (pid:529)
Value of myVariable before fork is 100
hello, I am parent of 530 (pid:529)
Value of myVariable from parent after fork is 100
Changing the value of myVariable in parent to 300
The changed value of myVariable from parent is 300
hello, I am child (pid:530)
Value of myVariable from child is 100
Changing the value of myVariable in child to 200
The changed value of myVariable from child is 200
```

**Observation:** The child and parent have separate copies of the variable and changing one doesn’t affect the other.

### Question 2

**Q:**  Write a program that opens a file (with the `open()` system call) and then calls `fork()` to create a new process. Can both the child and parent access the file descriptor returned by `open()`? What happens when they are writing to the file concurrently, i.e., at the same time?

**Code for simultaneous reading:**
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>
 
int main(int argc, char *argv[])
{
    printf("hello world (pid:%d)\n", (int)getpid());
    int fd = open("q2.c", O_RDONLY);
    if(fd == -1 ){
        printf("Unable to open the file\n exiting....\n");
        return 0;
    }
    
    int rc = fork();
    if (rc < 0)
    {
        // fork failed; exit`
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        // child (new process)
        printf("hello, I am child (pid:%d)\n", (int)getpid());
        char myChar;
        read(fd, &myChar,1);
        printf("Reading a character from the file from child and printing it\n%c\n", myChar);
    }
    else
    {
        wait(NULL);
        // parent goes down this path (original process)
        printf("hello, I am parent of %d (pid:%d)\n",
               rc, (int)getpid());
        char myChar;
        read(fd, &myChar,1);
        printf("Reading a character from the file from parent and printing it\n%c\n", myChar);
    }
    return 0;
}
```

**Output:**
```
hello world (pid:754)
hello, I am child (pid:755)
Reading a character from the file from child and printing it
#
hello, I am parent of 755 (pid:754)
Reading a character from the file from parent and printing it
i
```

**Observation:** Both share the same descriptor. 

**Code for simultaneous writing:**
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>
 
int main(int argc, char *argv[])
{
    printf("hello world (pid:%d)\n", (int)getpid());
    int fd = open("myFile.txt", O_CREAT|O_RDWR);
    if(fd == -1 ){
        printf("Unable to open the file\n exiting....\n");
        return 0;
    }
    
    int rc = fork();
    if (rc < 0)
    {
        // fork failed; exit`
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        // child (new process)
        printf("hello, I am child (pid:%d)\n", (int)getpid());
        char myChar='a';
        write(fd, &myChar,1);
        printf("writing a character to the file from child\n");
    }
    else
    {
        //wait(NULL);
        // parent goes down this path (original process)
        printf("hello, I am parent of %d (pid:%d)\n",
               rc, (int)getpid());
        char myChar='b';
        write(fd, &myChar,1);
        printf("writing a character to the file from parent\n");
    }
    return 0;
}
```

**Observation:** Both can write to the same file, but their outputs in file will appear in some random order.

### Question 3

**Q:**  Write another program using `fork()`. The child process should print “hello”; the parent process should print “goodbye”. You should try to ensure that the child process always prints first; can you do this *without* calling **wait()** in the parent?

**Code:**
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 
int main(int argc, char *argv[])
{
    int myVariable = 100;
    printf("hello world (pid:%d)\n", (int)getpid());
    int rc = fork();
    if (rc < 0)
    {
        // fork failed; exit`
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        // child (new process)
        printf("hello, I am child (pid:%d)\n", (int)getpid());
    }
    else
    {
        for (int i = 0; i < 100000; i++)
        {
            ;
        }
        // parent goes down this path (original process)
        printf("goodbye, I am parent of %d (pid:%d)\n",
               rc, (int)getpid());
    }
    return 0;
}
```

**Output:**
```
hello world (pid:994)
hello, I am child (pid:995)
goodbye, I am parent of 995 (pid:994)
```

**Observation:** We can use `for` loop to implement waiting for some time. Alternatively you could use `sleep()`. 

### Question 4

**Q:**  Write a program that calls `fork()` and then calls some form of `exec()` to run the program `/bin/ls`. See if you can try all of the variants of `exec()`, including (on Linux) `execl()`, `execle()`, `execlp()`, `execv()`, `execvp()`, and `execvpe()`. Why do you think there are so many variants of the same basic call?

**Code:**
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //this header is important
#include <string.h>
#include <sys/wait.h>
 
int main(int argc, char *argv[])
{
    printf("hello world (pid:%d)\n", (int)getpid());
    int rc = fork();
    if (rc < 0)
    {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        // child (new process)
        printf("hello, I am child (pid:%d)\n", (int)getpid());
 
        //     int execl(const char *pathname, const char *arg, ...
        //                    /* (char  *) NULL */);
        //    int execlp(const char *file, const char *arg, ...
        //                    /* (char  *) NULL */);
        //    int execle(const char *pathname, const char *arg, ...
        //                    /*, (char *) NULL, char *const envp[] */);
        //    int execv(const char *pathname, char *const argv[]);
        //    int execvp(const char *file, char *const argv[]);
        //    int execvpe(const char *file, char *const argv[],
        //                    char *const envp[]);
 
        // Function Description POSIX?
        // execl()  NULL-terminated argument list   Yes
        // execle() NULL-terminated argument list, specify the new process's environment    Yes
        // execlp() NULL-terminated argument list, search for the new process in PATH   Yes
        // execlpe()    NULL-terminated argument list, search for the new process in PATH, specify the new process's environment    No
        // execv()  NULL-terminated array of arguments  Yes
        // execve() NULL-terminated array of arguments, specify the new process's environment   Yes
        // execvp() NULL-terminated array of arguments, search for the new process in PATH  Yes
        // execvpe()    NULL-terminated array of arguments, search for the new process in PATH, specify the new process's environment   No
 
        char *myargs[3];
        myargs[0] = strdup("ls");         // program: "ls"
        myargs[1] = strdup("-a");         // argument:
        myargs[2] = NULL;                 // marks end of array
        char *const envp[2] = {"", NULL}; // here you can set environment variables.
 
        //uncomment the next line to execute execvp
        //execvp(myargs[0], myargs);
        execle("/usr/bin/ls", "-a", NULL, envp);
 
        printf("this shouldn't print out");
    }
    else
    {
        // parent goes down this path (original process)
        int wc = wait(NULL);
        printf("hello, I am parent of %d (wc:%d) (pid:%d)\n",
               rc, wc, (int)getpid());
    }
    return 0;
}
```

**Output:**
```
hello world (pid:1213)
hello, I am child (pid:1214)
'1 copy.c'   1.c   2.c   3.c   4.c   a.out   myFile.txt
hello, I am parent of 1214 (wc:1214) (pid:1213)
```

### Question 5

**Q:** Now write a program that uses `wait()` to wait for the child process to finish in the parent. What does `wait()` return? What happens if you use `wait()` in the child?

**Code**
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
 
int
main(int argc, char *argv[])
{
    printf("hello world (pid:%d)\n", (int) getpid());
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        printf("hello, I am child (pid:%d)\n", (int) getpid());
    sleep(1);
    } else {
        // parent goes down this path (original process)
        int wc = wait(NULL);
        printf("hello, I am parent of %d (wc:%d) (pid:%d)\n",
           rc, wc, (int) getpid());
    }
    return 0;
}
```

**Code (with wait in child):**
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
 
int main(int argc, char *argv[])
{
    printf("hello world (pid:%d)\n", (int)getpid());
    int rc = fork();
    if (rc < 0)
    {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        // child (new process)
        printf("hello, I am child (pid:%d)\n", (int)getpid());
        sleep(1);
        int wc = wait(NULL);
        printf("The value of return from wait in child program is %d\n", wc);
    }
    else
    {
        // parent goes down this path (original process)
        int wc = wait(NULL);
        printf("hello, I am parent of %d (wc:%d) (pid:%d)\n",
               rc, wc, (int)getpid());
    }
    return 0;
}
```

**Observations:** `wait()` returns the PID of the child process when used in the parent. `wait()` returns the `-1`  when used in the child.

### Question 6

**Q:** Write a slight modification of the previous program, this time using `waitpid()` instead of `wait()`. When would `waitpid()` be useful?

**Code:**
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
 
#include <sys/types.h> 
 
int main(int argc, char *argv[])
{
    printf("hello world (pid:%d)\n", (int)getpid());
    pid_t rc = fork();
    int status;
    if (rc < 0)
    {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        // child (new process)
        printf("hello, I am child (pid:%d)\n", (int)getpid());
        sleep(1);
    }
    else
    {
        // parent goes down this path (original process)
        //         Wait for a child matching PID to die.
        // If PID is greater than 0, match any process whose process ID is PID.
        // If PID is (pid_t) -1, match any process.
        // If PID is (pid_t) 0, match any process with the
        // same process group as the current process.
        // If PID is less than -1, match any process whose
        // process group is the absolute value of PID.
        // If the WNOHANG bit is set in OPTIONS, and that child
        // is not already dead, return (pid_t) 0. If successful,
        // return PID and store the dead child's status in STAT_LOC.
        // Return (pid_t) -1 for errors. If the WUNTRACED bit is
        // set in OPTIONS, return status for stopped children; otherwise don't.

        pid_t wc = waitpid(rc, &status, WUNTRACED);
        printf("hello, I am parent of %d (wc:%d) (pid:%d)\n",
               rc, wc, (int)getpid());
    }
    return 0;
}
```

**Observation:** `waitpid` allows for more finegrained control over which process to wait for, what to wait

### Question 7

**Q:** Write a program that creates a child process, and then in the child closes standard output (`STDOUT FILENO`). What happens if the child calls `printf()` to print some output after closing the descriptor?

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/wait.h>
 
int
main(int argc, char *argv[])
{
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
    // child: redirect standard output to a file
    close(STDOUT_FILENO); 
    open("theoutput.txt", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
    printf("I am printing from the child\n");
    
    } else {
        // parent goes down this path (original process)
        int wc = wait(NULL);
    assert(wc >= 0);
    }
    return 0;
}
```

**Observation:** If you don’t open a file to redirect the output printed by the child, the output is lost.

### Question 8

**Q:** Write a program that creates two children, and connects the standard output of one to the standard input of the other, using the `pipe()` system call.

**Code:**
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/wait.h>
 
int main(int argc, char *argv[])
{
    int fd1[2]; // Used to store two ends of first pipe
    //[0] is the reading end
    //[1] is the writing end
    if (pipe(fd1) == -1)
    {
        fprintf(stderr, "Pipe Failed");
        return 1;
    }
 
    int rc1 = fork();
    if (rc1 < 0)
    {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc1 == 0)
    { //body of the first child
 
        // child: redirect standard output to a file
        //setting the standard output of first child to end of the pipe
        /* Standard file descriptors.  */
        // #define  STDIN_FILENO    0   /* Standard input.  */
        // #define  STDOUT_FILENO   1   /* Standard output.  */
        // #define  STDERR_FILENO   2   /* Standard error output.  */
        dup2(fd1[1], 1); // redirect stdout
 
        printf("Hello this is a message from first child\n");
    }
    else
    {
        int rc2 = fork();
        if (rc2 < 0)
        {
            // fork failed; exit
            fprintf(stderr, "fork failed\n");
            exit(1);
        }
        else if (rc2 == 0)
        {
            //body of the second child
            dup2(fd1[0], STDIN_FILENO); //setting the input of second child to output of first)
            sleep(1);
            char message[100];
            //scanf("%s",message);
            gets(message);
            printf("The message from the first child is \"%s\"\n", message);
        }
        else
        {
            //body of the parent
            //sleep(1);
            wait(NULL);
        }
    }
    return 0;
}
```
