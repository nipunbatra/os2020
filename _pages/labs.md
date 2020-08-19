---
layout: page
permalink: /labs/
title: Labs
description: "Questions and Solutions for all Labs held"
---

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
**Q:** Find its parent

**A:** 
Run `ps -o ppid= -p <PID>`. If the child has PID 1234, run `ps -o ppid= -p 1234`.

### Question 11
**Q:** Find details of multiple processes using PID list.

**A:** 
If you want to find information about PIDs 123,234 and 456 run `ps =p 123,234,456`.
