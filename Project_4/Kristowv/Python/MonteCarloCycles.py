import numpy as np
import matplotlib.pyplot as plt
import time
from matplotlib import rc, rcParams

rc('text', usetex=True)
rc('font', **{'family': 'serif', 'serif': ['Random']})

# plt.style.use('classic')
graph_data = open(
    '/Users/kristoffervarslott/Documents/C++/FYS4150/Project4/Project_4_General/Monte1.txt', 'r').read()

lines = graph_data.split("\n")
ENCUT = []

T = []
E = []
C_V = []
M = []
X = []


start = time.time()
for i in range(len(lines)-2):
    if (i > 6 and i < len(lines)):
        splitted_lines = lines[i].split()
        T.append(float(splitted_lines[1]))
        E.append(float(splitted_lines[3]))
        C_V.append(float(splitted_lines[5]))
        M.append(float(splitted_lines[7]))
        X.append(float(splitted_lines[9]))

end = time.time()
print ("Code time:", end - start)

plt.figure(1)
plt.plot(T, E, linewidth=0.5, linestyle="-", marker="o", markersize=0.8)
#plt.scatter(T, E, s=0.5)
# plt.legend(loc='upper right', prop={"size": 12})
plt.xlabel("Monte Carlo Cycles", fontsize=14)
plt.ylabel('[E]', fontsize=14)
plt.title("Energy", fontsize=15)
# plt.tight_layout()
plt.plot([0, 100000], [-1.99598208594, -1.99598208594], linestyle='--', color="k")

plt.figure(2)
plt.plot(T, C_V, linewidth=0.5, color="tab:orange",
         linestyle="-", marker="o", markersize=0.8)
plt.plot([0, 100000], [0.03208, 0.03208], linestyle='--', color="k")
# plt.legend(loc='upper right', prop={"size": 12})
plt.xlabel("Monte Carlo Cycles", fontsize=14)
plt.ylabel('Heat Capacity $C_V$', fontsize=14)
plt.title("Heat capacity", fontsize=15)
# plt.tight_layout()

plt.figure(3)
plt.plot(T, M, linewidth=0.5, linestyle="-", marker="o", markersize=0.8)
# plt.legend(loc='upper right', prop={"size": 12})
plt.xlabel("Monte Carlo Cycles", fontsize=14)
plt.ylabel('Magnetization $/Xsi$', fontsize=14)
plt.title("Magnetization", fontsize=15)
# plt.tight_layout()

plt.figure(4)
plt.plot(T, X, linewidth=0.5, linestyle="-", marker="o", markersize=0.8)
# plt.legend(loc='upper right', prop={"size": 12})
# plt.xlabel("Number of iterations [N]", fontsize=14)
# plt.ylabel('Relative error $\epsilon$', fontsize=14)
plt.title("Susceptibility", fontsize=15)
# plt.tight_layout()

plt.show()
