import threading
import time
import sys

loops = int(sys.argv[1])

global counter
counter = 0


def worker():
    for i in range(loops):
        global counter
        counter = counter + 1

class MyThread(threading.Thread):
    def run(self):
        print("{} started!".format(self.getName())) 
        #time.sleep(1)   
        worker()
        print("{} finished!".format(self.getName()))

for x in range(4):
    mt = MyThread(name = "Thread-{}".format(x + 1))
    mt.start()

print(counter)
