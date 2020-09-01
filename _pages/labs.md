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
- [Lab 3](#lab-3)
  * [Question 1](#question-1-2)
  * [Question 2](#question-2-2)
  * [Question 3](#question-3-2)
  * [Question 4](#question-4-2)
- [Lab 4](#lab-4)
  * [Question 1](#question-1-3)
  * [Question 2](#question-2-3)
  * [Question 3](#question-3-3)
  * [Question 4](#question-4-3)
  * [Question 5](#question-5-2)
  * [Question 6](#question-6-2)
  * [Question 7](#question-7-2)
  * [Question 8](#question-8-2)

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

# Lab 3

### Question 1

**Q:** Write your own version of the command line program `stat`, which simply calls the  stat()  system call on a given file or directory. Print out file size, number of blocks allocated, reference (link) count, and so forth. What is the link count of a directory, as the number of entries in the directory changes? Useful interfaces: `stat()`, naturally.

**Code:**
```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
// For stat
#include <sys/stat.h>
#include <unistd.h>
// For catching errors in errno:
#include <errno.h>
// For formatting errno to string:
#include <string.h>
// For formatting time:
#include <time.h>
// For username from UID
#include <pwd.h>
// For groupname from GID
#include <grp.h>

// Here is how the structure returned by stat looks:
//     struct stat {
//                 dev_t     st_dev;         /* ID of device containing file */
//                 ino_t     st_ino;         /* Inode number */
//                 mode_t    st_mode;        /* File type and mode */
//                 nlink_t   st_nlink;       /* Number of hard links */
//                 uid_t     st_uid;         /* User ID of owner */
//                 gid_t     st_gid;         /* Group ID of owner */
//                 dev_t     st_rdev;        /* Device ID (if special file) */
//                 off_t     st_size;        /* Total size, in bytes */
//                 blksize_t st_blksize;     /* Block size for filesystem I/O */
//                 blkcnt_t  st_blocks;      /* Number of 512B blocks allocated */
//                 struct timespec st_atim;  /* Time of last access */
//                 struct timespec st_mtim;  /* Time of last modification */
//                 struct timespec st_ctim;  /* Time of last status change */
//                 
//                 #define st_atime st_atim.tv_sec      /* Backward compatibility */
//                 #define st_mtime st_mtim.tv_sec
//                 #define st_ctime st_ctim.tv_sec
//     };

void print_stat(char *filename){
    struct stat file_stat;
    if (stat(filename, &file_stat) == -1){
        // Error handling
        fprintf(stderr, "stat: cannot stat '%s': %s\n", filename,strerror(errno));
        exit(EXIT_FAILURE);
    } else {
        printf("%10s %s\n", "File:", filename);
        printf("%10s %ld\n", "Size:", file_stat.st_size);
        printf("%10s %ld\n", "Blocks:", file_stat.st_blocks);
        printf("%10s %ld\n", "IO Block:", file_stat.st_blksize);
        printf("%10s ", "File Type:");
        // How to get the various types of files
            // S_ISREG(m)  is it a regular file?
            if(S_ISREG(file_stat.st_mode)) printf("regular file\n");
            // S_ISDIR(m)  directory?
            if(S_ISDIR(file_stat.st_mode)) printf("directory\n");
            // S_ISCHR(m)  character device?
            if(S_ISCHR(file_stat.st_mode)) printf("character device\n");
            // S_ISBLK(m)  block device?
            if(S_ISBLK(file_stat.st_mode)) printf("block device\n");
            // S_ISFIFO(m) FIFO (named pipe)?
            if(S_ISFIFO(file_stat.st_mode)) printf("FIFO (named pipe)\n");
            // S_ISLNK(m)  symbolic link?
            if(S_ISLNK(file_stat.st_mode)) printf("symbolic link\n");
            // S_ISSOCK(m) socket?
            if(S_ISSOCK(file_stat.st_mode)) printf("socket\n");
        printf("%10s %lx\n", "Device:",file_stat.st_dev);
        printf("%10s %lu\n", "Inode:", file_stat.st_ino);
        printf("%10s %lu\n", "Links:", file_stat.st_nlink);
        printf("%10s %04o\n", "Access:", file_stat.st_mode&0777);
        // Getting Username from UID
        struct passwd *pws;
        pws = getpwuid(file_stat.st_uid);
        printf("%10s (%5d/%s)\n", "Uid:", file_stat.st_uid , pws->pw_name);
        //Getting Group Name from GID
        struct group *grp;
        grp = getgrgid(file_stat.st_gid);
        printf("%10s (%5d/%s)\n", "Gid:", file_stat.st_gid , grp->gr_name);
        // Format times using ctime from time.h
        printf("%10s %s", "Access:", ctime(&file_stat.st_atime));
        printf("%10s %s", "Modify:", ctime(&file_stat.st_mtime));
        printf("%10s %s", "Change:", ctime(&file_stat.st_ctime));
    }
}

int main(int argc, char* argv[]){
    if (argc==1){
        // If not other argument is given
        fprintf(stderr,"stat: missing operand\n");
    } else {
        // print info one argument at a time
        for(int i=1;i<argc;i++){
            print_stat(argv[i]);
        }
    }
    return 0;
}
```

### Question 2

**Q:** Write a program that lists files in the given directory. When called without any arguments, the program should just print the file names. When invoked with the `-l` flag, the program should print out information about each file, such as the owner, group, permissions, and other information obtained from the `stat()` system call. The program should take one additional argument, which is the directory to read, e.g., `myls -l directory`. If no directory is given, the program should just use the current working directory. Useful interfaces: `stat()`, `opendir()`, `readdir()`, `getcwd()`.

**Code:**
```c
#include <stdio.h>    
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>   
#include <dirent.h>    // opendir, readdir, closedir
#include <string.h>    // strlen, strncpy, strncat
#include <stdbool.h>   // For booleans
#include <errno.h>
#include <time.h>   
#include <pwd.h>
#include <grp.h>

#define STRINGSIZE 1024

void print_file(struct stat sb) {
    // Getting Username from UID
    struct passwd *pws;
    pws = getpwuid(sb.st_uid);
    //Getting Group Name from GID
    struct group *grp;
    grp = getgrgid(sb.st_gid);
    // Time String
    char* time_str = ctime(&sb.st_mtime);
    time_str[strlen(time_str) - 1] = '\0';
    printf("%6o %3lu %12s %12s %6ld %s ", sb.st_mode, sb.st_nlink , pws->pw_name, grp->gr_name, sb.st_size, time_str);
}

int main(int argc, char *argv[]) {
    struct stat sb;
    char * pathname = ".";
    bool list;
    DIR *dp;

    list = (argc>1 && strcmp(argv[1], "-l")==0);
    if (argc == 2 + list) pathname = argv[1+list];
    else if(argc!=1 + list) {
        // Error handling
        fprintf(stderr,"Usage: %s [-l] [filename]", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    if (stat(pathname, &sb) == -1){
        // Error handling
        fprintf(stderr, "stat: cannot stat '%s': %s\n", pathname,strerror(errno));
        exit(EXIT_FAILURE);
    }

    if (S_ISDIR(sb.st_mode)) {
        if ((dp = opendir(pathname)) == NULL){
            // Error handling
            fprintf(stderr, "opendir: cannot opendir '%s': %s\n", pathname,strerror(errno));
            exit(EXIT_FAILURE);
        }
        struct dirent *d;
        while ((d = readdir(dp)) != NULL) {
            if (list) {
                char filePath[STRINGSIZE] = "";
                strncpy(filePath, pathname, strlen(pathname));
                strncat(filePath, "/", 1);
                strncat(filePath, d->d_name, strlen(d->d_name));
                if (stat(filePath, &sb) == -1){
                    // Error handling
                    fprintf(stderr, "stat: cannot stat '%s': %s\n", pathname,strerror(errno));
                    exit(EXIT_FAILURE);
                }
                print_file(sb);
            }
            printf("%s\n", d->d_name);
        }
        closedir(dp);
    } else {
        if (list)
            print_file(sb);
        printf("%s\n", pathname);
    }
    return 0;
}
```

### Question 3

**Q:** Write a program that prints out the last few lines of a file. The program should be efficient, in that it seeks to near the end of the file, reads in a block of data, and then goes backwards until it finds the requested number of lines; at this point, it should print out those lines from beginning to the end of the file. To invoke the program, one should type: `mytail -n file`, where `n` is the number of lines at the end of the file to print. Useful interfaces: `stat()`, `lseek()`, `open()`, `read()`, `close()`.

**Code:**
```c
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc, char* argv[]){
    if(argc != 3 || strlen(argv[1]) <= 1 || argv[1][0] != '-'){
        fprintf(stderr, "Usage: %s -<offset> <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    } else {
        int num_lines = atoi(argv[1]+1) - 1;
        struct stat sb;
        if (stat(argv[2], &sb) == -1){
            // Error handling
            fprintf(stderr, "stat: cannot stat '%s': %s\n", argv[2],strerror(errno));
            exit(EXIT_FAILURE);
        } else {
            int fd = open(argv[2], O_RDONLY);
            long rd_size = sb.st_blksize;
            char buf[rd_size+1];
            long offset = lseek(fd,0,SEEK_END);
            int bytes_read;

            while (num_lines >= 0 && offset > 0)
            {
                int seek_rel_to = (offset>=rd_size)?SEEK_CUR:SEEK_SET;
                long seek_to =  (offset>=rd_size)?-rd_size:0;
                int read_len = (offset>=rd_size)?rd_size:offset;
                lseek(fd, seek_to, seek_rel_to);
                bytes_read = read(fd,buf,read_len);
                for(int i=bytes_read;i>=0;i--){
                    if(buf[i]=='\n'){
                        num_lines--;
                        if(num_lines<0){
                            offset = lseek(fd,-bytes_read + i+1,SEEK_CUR);
                            goto found_all;
                        }
                    }
                }
                offset = lseek(fd, seek_to, seek_rel_to);
            }
            
            found_all:
            while((bytes_read = read(fd,buf,rd_size)) > 0){
                buf[bytes_read] = '\0';
                printf("%s", buf);
            }
            close(fd);
        }
    }
    return 0;
}
```

### Question 4

**Q:** Write a program that prints out the names of each file and directory in the file system tree, starting at a given point in the tree. For example, when run without arguments, the program should start with the current working directory and print its contents, as well as the contents of any sub-directories, etc., until the entire tree, root at the CWD, is printed. If given a single argument (of a directory name), use that as the root of the tree instead. Refine your recursive search with more fun options, similar to the powerful `find` command line tool. Useful interfaces: figure it out.

**Code:**
```c
#include <stdio.h>    
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>    
#include <dirent.h>    // opendir, readdir, closedir
#include <string.h>    // strlen, strncpy, strncat
#include <errno.h>
#include <pwd.h>
#include <grp.h>

#define STRINGSIZE 1024

void print_dir(char *pathname) {
    DIR *dp;
    struct stat sb;
    if (stat(pathname, &sb) == -1){
        // Error handling
        fprintf(stderr, "stat: cannot stat '%s': %s\n", pathname,strerror(errno));
        exit(EXIT_FAILURE);
    }

    if (S_ISDIR(sb.st_mode)) {
        if ((dp = opendir(pathname)) == NULL){
            // Error handling
            fprintf(stderr, "opendir: cannot opendir '%s': %s\n", pathname,strerror(errno));
            exit(EXIT_FAILURE);
        }
        struct dirent *d;
        while ((d = readdir(dp)) != NULL) {
            if(strcmp(d->d_name,".")==0) printf("%s\n",pathname);
            else if (strcmp(d->d_name,"..")!=0) {
                char path_string[STRINGSIZE] = "";
                strcpy(path_string, pathname);
                strcat(path_string,"/");
                strcat(path_string,d->d_name);
                print_dir(path_string);
            }
        }
        closedir(dp);
    } else {
        printf("%s\n", pathname);
    }
}

int main(int argc, char *argv[]) {
    char * pathname = ".";

    if(argc>2) {
        // Error handling
        fprintf(stderr,"Usage: %s [filename]", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (argc==2) pathname = argv[1];
    print_dir(pathname);
    return 0;
}
```

# Lab 4

### Question 1

**Q:** The first Linux tool you should check out is the very simple tool `free`. First, type `man free` and read its entire manual page; it's short, don't worry!

**A:** Self-explanatory. Just run `man free`.

### Question 2

**Q:** Now, run `free`, perhaps using some of the arguments that might be useful (e.g., `-m`, to display memory totals in megabytes). How much memory is in your system? How much is free? Do these numbers match your intuition?

**A:** Try different arguments with `free`. A very useful argument is `-h` which makes all the units in human readable format like MB, GB according to the size of the number. Try `free -h` to see for yourself. You will see two rows in the output, one will be for the physical RAM memory and the other will be for swap memory. Swap is a portion of memory which resides on your harddrive, usually as a separate partition and is used only when the RAM is full, so that the OS doesn't crash or malfunction as soon as the physical memory is filled and there is some leeway to recover from the excessive memory usage if need be. Meanwhile, when swap memory is being used, there is a significant slowdown in the operations as memory access from harddisks is trypically much slower that RAM even if you have an SSD. 

### Question 3

**Q:** Next, create a little program that uses a certain amount of memory, called `memory-user.c`. This program should take one commandline argument: the number of megabytes of memory it will use. When run, it should allocate an array, and constantly stream through the array, touching each entry. The program should do this indefinitely, or, perhaps, for a certain amount of time also specified at the command line.

**Code:** 
```c
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>


int main(int argc, char* argv[]){
    printf("Current Process ID = %d\n",getpid());
    long long int size = ((long long int)atoi(argv[1]))*1024*1024; //in bytes
    int* buffer = (int*)malloc(size);

    //run the while loop for given amount of time.
    time_t endwait, seconds, start;
    seconds=atoi(argv[2]);
    start=time(NULL);
    endwait = start + seconds;

    while(start<endwait){
        printf(".");
        fflush(stdout);
        for(long long int i=0; i<size/sizeof(int); i++){
            buffer[i] = i;
        }
        start = time(NULL);
    }
    printf("(done)\n");
    return 0;
}
```

**Usage:** After compiling this program, just run with two arguments. The first argument is the number of MB to reserve and the second is the minimum number of seconds to run the program for. 

**Additional:** Find out why you need to run through the array. What happens if we don't do so?

### Question 4

**Q:** Now, while running your `memory-user` program, also (in a different terminal window, but on the same machine) run the `free` tool. How do the memory usage totals change when your program is running? How about when you kill the `memory-user` program? Do the numbers match your expectations? Try this for different amounts of memory usage. What happens when you use really large amounts of memory?

**A:** Keep a watch on the memory using `watch -n 1 free -m`. When the `memory-user` program is run, you see that the amount of MB you gave as argument gets added to the statistics shown by `free`. When the program is killed, the used memory decreases by the amount of MB you gave as argument. Also, when a large amount of memory is entered, we observe that the swap is being filled after the RAM is almost full.

### Question 5

**Q:** Let's try one more tool, known as `pmap`. Spend some time, and read the `pmap` manual page in detail.

**A:** Self-explanatory. Just run `man pmap` and read the manual.

### Question 6

**Q:** To use `pmap`, you have to know the **process ID** of the process you're interested in. Thus, first run `ps auxw` to see a list of all processes; then, pick an interesting one, such as a browser. You can also use your `memory-user` program in this case (indeed, you can even have that program call `getpid()` and print out its PID for your convenience).

**A:** Use the pid of `memory-user` or any other process and check its memory map using `pmap -q <PID>`. 

### Question 7

**Q:** Now run `pmap` on some of these processes, using various flags (like `-X`) to reveal many details about the process. What do you see? How many different entities make up a modern address space, as opposed to our simple conception of code/stack/heap?

**A:** Beside stack and heap, we observe `Anonymous memory`: Memory not relating to any named object or file within the file system. You might also observe `vDSO` and `vsyscall` in the output depending on the program and the specific system you're using. They are both ways to accelerate system calls. You can read more about these ![here](https://stackoverflow.com/questions/19938324/what-are-vdso-and-vsyscall).  

### Question 8

**Q:** Finally, let's run `pmap` on your `memory-user` program, with different amounts of used memory. What do you see here? Does the output from `pmap` match your expectations?

**A:** On execution of `memory-user`, as we increase heap allocation, the same is visible in the output of `pmap`. 
