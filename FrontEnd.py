from tkinter import *
import os
def novel(event):
    print("Running Novel Algorithm Simulator...")
    os.startfile(r"C:\OSProj\novel.exe")

def pmhrrn(event):
    print("Running PMHRRN Algorithm Simulator")
    os.startfile(r"C:\OSProj\pmhrrn.exe")

def igbtq(event):
    print("Running IGBTQ Algorithm Simulator")
    os.startfile(r"C:\OSProj\igbtq.exe")

def edf(event):
    print("Running Earliest Deadline First Algorithm Simulator")
    os.startfile(r"C:\OSProj\edf.exe")

def tdrr(event):
    print("Running TDRR Algorithm Simulator")
    os.startfile(r"C:\OSProj\link.bat")

root=Tk()

titleText = "Project Front-End\nSimulation and Analysis of Novel and Innovative Algorithms"
descText = "Please click on any button to run the required scheduling algorithm simulation:"

title = Label(root, text=titleText,font="Times 20 bold")
title.grid(row=0,columnspan=5)

desc = Label(root, text=descText)
desc.grid(row=1,columnspan=5,sticky="w",pady=10)

novelBtn = Button(root, text='Simulate Novel')
novelBtn.grid(row=2,column=0,pady=5)
novelBtn.bind('<Button-1>', novel)

pmhrrnBtn = Button(root, text='Simulate PMHRRN')
pmhrrnBtn.grid(row=2,column=1,pady=5)
pmhrrnBtn.bind('<Button-1>', pmhrrn)

igbtqBtn = Button(root, text='Simulate IGBTQ')
igbtqBtn.grid(row=2,column=2,pady=5)
igbtqBtn.bind('<Button-1>', igbtq)

edfBtn = Button(root, text='Simulate EDF')
edfBtn.grid(row=2,column=3,pady=5)
edfBtn.bind('<Button-1>', edf)

edfBtn = Button(root, text='Simulate Trained Dynamic RR')
edfBtn.grid(row=2,column=4,pady=5)
edfBtn.bind('<Button-1>', tdrr)

root.mainloop()
