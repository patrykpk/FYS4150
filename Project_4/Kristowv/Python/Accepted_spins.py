from numpy import *
import matplotlib.pyplot as plt

Monte = []
Flips = []
path = "/Users/kristoffervarslott/Documents/C++/FYS4150/Project4/Project_4_General/"
# plt.style.use('classic')


def Read_File(filename):
    with open(filename, 'r', encoding="utf8") as infile:
        lines = infile.read().split("\n")
        Amount_of_Data = len(lines[7:-2])
        print (Amount_of_Data)
        for i in range(len(lines)-2):
            if (i > 6 and i < len(lines)):
                splitted_lines = lines[i].split()
                Monte.append(float(splitted_lines[0]))
                Flips.append(float(splitted_lines[1]))


Read_File(path + "Accepted_Flips.txt")

plt.plot(Monte, asarray(Flips)/400, "-")
# plt.ylim(0,200)
plt.xscale("log")
plt.show()
