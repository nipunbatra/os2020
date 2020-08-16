import sys
import subprocess
import time
ppid = sys.argv[1]

def is_number(s):
    try:
        float(s)
        return True
    except ValueError:
        return False
out_string = str(ppid)
while is_number(ppid):
    try:
        ppid = subprocess.check_output('ps -p {} -o ppid|tail -1'.format(ppid), shell=True)
        ppid = ppid.decode('UTF-8').replace("\n", "")
        print(ppid) 
    except:
        sys.exit(0)
