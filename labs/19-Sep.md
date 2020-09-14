    1. Install Chromium for Linux
    2. Use ps command to find all threads for Chrome
    3. Open new tabs in Chrome. How does the number of threads increase
    4. Use top command for find all threads for Chrome
    5. Use pstree to find all threads for Chrome
    6. Use /proc/pid to find out more:
        1. cmdline?
        2. Exe? Hexdump on exe.
        3. Status
        4. Tasks
        5. Explore other things...
        6. can you see the process page map?
    7. What are different processes and threads corresponding to Chrome
        1. What are their cmdlines
        2. Open Chrome in different modes using different arguments and see how #threads/processes vary per #tabs/#unique domains
        3. Any secret key?
        4. How does Chrome send data to Google?
        5. Syscalls? Attach strace to the process
    8. What does /proc contain
        1. watch -n 1 cat interrupts
        2. cat cpuinfo
        3. devices
        4.  ...
        5. ...
    9. Write hello world threaded program without any variable sharing
    10. How do you compile this program?
    11. Write hello world program that has two threads increasing the value of a counter
        1. Do an object dump to find the critical section of the cod

