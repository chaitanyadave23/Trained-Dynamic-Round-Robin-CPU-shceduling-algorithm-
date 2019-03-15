import threading
from threading import Thread
import os

def run1():
    os.system(r"python C:\OSProj\TrainedDynamicRR\trainedDynamicRR.py")
def run2():
    os.startfile(r"C:\OSProj\TrainedDynamicRR\tdrr.exe")

print("Running Earliest Deadline First Algorithm Simulator")
Thread(target = run1).start()
Thread(target = run2).start()