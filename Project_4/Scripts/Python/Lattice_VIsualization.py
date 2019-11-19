# Libraries
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import colors
from scipy.stats import kde
from matplotlib import animation
import time

plt.style.use('classic')
# Opening the file to be read.
Matrix = open('./SpinConfig_100_Ordered_24.txt', 'r').read()
lines = Matrix.split("\n")


# Defining a funciton matrix for visualicaion later on.
def matrix(i):
    Liste = []
    # Looping over every line in file, and appending into list.
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


# Plotting over the range of 100 Monte Carlo cycles.
plt.figure()
for i in range(100):
    plt.pcolor(matrix(i), cmap="Greys", edgecolors="r", vmin=-1, vmax=1)
    plt.pause(0.001)
plt.show()
