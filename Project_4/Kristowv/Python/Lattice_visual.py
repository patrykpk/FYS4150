# Libraries
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import colors
from scipy.stats import kde
from matplotlib import animation
import time
# plt.style.use('classic')

Matrix = open(
    '/Users/kristoffervarslott/Documents/C++/FYS4150/Project4/Project_4_General/SpinConfig.txt', 'r').read()
lines = Matrix.split("\n")


def matrix(i):
    Liste = []
    # Matrix = [item.split() for item in Matrix.split('\n')[:-1]]
    for k in range(len(lines)):
        if (k >= 0 and k <= len(lines)):
            splitted_lines = lines[k].split()
            c = list(map(float, splitted_lines))
            # print (lines)
            if (splitted_lines == []):
                None
            else:
                A = splitted_lines
                Liste.append(c)
    L = Liste[len(A)*i:(len(A)*i+len(A))]
    return L


plt.figure()
# plt.ion()
for i in range(101):
    plt.pcolor(matrix(i), cmap="Greys", edgecolors="r", vmin=-1, vmax=1)
    plt.pause(0.5)

plt.show()
