./x86.py -p loop.s -t 1 -i 100 -R dx

./x86.py -p loop.s -t 2 -i 100 -a dx=3,dx=3 -R dx

./x86.py -p loop.s -t 2 -i 3 -r -a dx=3,dx=3 -R dx

./x86.py -p looping-race-nolock.s -t 1 -M 2000 

./x86.py -p looping-race-nolock.s -t 2 -a bx=3 -M 2000

./x86.py -p looping-race-nolock.s -t 2 -M 2000 -i 4 -r -s 0 

./x86.py -p looping-race-nolock.s -t 2 -M 2000 -i 4 -r -s 1

./x86.py -p looping-race-nolock.s -t 2 -M 2000 -i 4 -r -s 2

./x86.py -p looping-race-nolock.s -a bx=1 -t 2 -M 2000 -i 1

./x86.py -p looping-race-nolock.s -a bx=1 -t 2 -M 2000 -i 2

./x86.py -p looping-race-nolock.s -a bx=1 -t 2 -M 2000 -i 3


