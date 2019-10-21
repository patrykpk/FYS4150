import numpy as np
import matplotlib.pyplot as plt
import time
from matplotlib import rc, rcParams
import os

rc('text', usetex=True)
rc('font', **{'family': 'serif', 'serif': ['Random']})

# plt.style.use('classic')


# Checks if the file is found in either the same directory
# or within a folder with results (Layout from Github)
path = False
for filename in os.listdir("./"):
    if filename == "Project_3_GQ.txt":
        path = "Project_3_GQ.txt"
        savepath = "./Figures/"

if os.path.exists("../../Results"):
    for filename in os.listdir("../../Results"):
        if filename == "Project_3_GQ.txt":
            path = "../../Results/Project_3_GQ.txt"
            savepath = "../../Figures/"

if not path:
    print ("File not found")


graph_data = open(path, 'r').read()

lines = graph_data.split("\n")

N = []
N_even = []
N_odd = []

leg = []
leg_even = []
leg_odd = []
lag = []

error_leg_odd = []
error_leg_even = []
error_leg = []
error_lag = []

CPU_leg = []
CPU_lag = []

exact = []

start = time.time()
for i in range(len(lines)-1):
    if (i > 1 and i < len(lines)):
        splitted_lines = lines[i].split()
        c = list(map(float, splitted_lines))
        N.append(c[0])                   # First element N-values
        if (i % 2) == 0:
            leg_odd.append(c[1])         # Legendre Odd value of N
            error_leg_odd.append(c[3])   # Relative Error Legendre Odd
            N_odd.append(c[0])           # Appends the value of N to list
        else:
            leg_even.append(c[1])        # Legendre Even value of N
            error_leg_even.append(c[3])  # Relative Error Legednre Odd
            N_even.append(c[0])          # Appends the value of N to list another list

        leg.append(c[1])        # Integral value for Legendre for all N
        lag.append(c[4])        # Integral value for Laguerre for all N

        exact.append(c[7])      # Exact value of the integral

        error_leg.append(c[3])  # Legendre Error
        error_lag.append(c[6])  # Laguerre Error

        CPU_leg.append(c[2])  # CPU time for Legendre
        CPU_lag.append(c[5])  # CPU time for Laguerre

end = time.time()
print ("Code time:", end - start)

# Checking if a directory for storing the plots exists,
# if not, then a folder is made
if not os.path.exists(savepath):
    os.makedirs(savepath)
else:
    print ("Folder already exists")


plt.figure(1)
plt.plot(N_even, leg_even, linewidth=0.5,
         marker="o", color="r", markersize=2, label='Gaussian-Legendre Even')
plt.plot(N_odd, leg_odd, linewidth=0.5, marker="o",
         markersize=2, c='C0', label='Gaussian-Legendre Odd')
plt.plot(N, lag, linewidth=0.5, color="orange", linestyle="-", label='Gaussian-Laguerre')
plt.plot(N, exact, linewidth=0.5, color="green", linestyle="--", label='Exact solution')
plt.legend(loc='upper right', prop={"size": 10})
plt.xlabel("Number of iterations [N]    ", fontsize=14)
plt.ylabel('Estimated solution of integral', fontsize=14)
plt.title("Convergency of Legendre $\&$ Laguerre", fontsize=15)
plt.savefig(path+"GQ_Integral_Even_Odd")
plt.tight_layout()

plt.figure(2)
plt.plot(N, leg, linewidth=0.5, linestyle="-", markersize=2, label='Gaussian-Legendre')
plt.plot(N, lag, linewidth=0.5, linestyle="-", label='Gaussian-Laguerre')
plt.plot(N, exact, linewidth=0.5, color="green", linestyle="--", label='Exact solution')
plt.legend(loc='upper right', prop={"size": 10})
plt.xlabel("Number of iterations [N]", fontsize=14)
plt.ylabel('Estimated solution of integral', fontsize=14)
plt.title("Convergency of Legendre $\&$ Laguerre", fontsize=15)
plt.savefig(path+"GQ_Integral")
plt.tight_layout()

plt.figure(3)
plt.plot(N, error_leg, linewidth=0.5, linestyle="--", label='Legendre')
plt.plot(N, error_lag, linewidth=0.5, linestyle="--", label='Laguerre')
plt.legend(loc='upper right', prop={"size": 10})
plt.xlabel("Number of iterations [N]", fontsize=14)
plt.ylabel('Relative error $\epsilon$', fontsize=14)
plt.title("Relative error [Legendre $\&$ Laguerre]", fontsize=15)
plt.savefig(path+"GQ_Relative_Error")
plt.tight_layout()

plt.figure(4)
# plt.yscale('log')
plt.plot(N, CPU_leg, linewidth=0.5, linestyle="--", label='CPU-time Legendre')
plt.plot(N, CPU_lag, linewidth=0.5, linestyle="--", label='CPU-time Laguerre')
plt.legend(loc='upper left', prop={"size": 10})
plt.xlabel("Number of iterations [N]", fontsize=14)
plt.ylabel('CPU-time [s]', fontsize=14)
plt.title("CPU-time for [Legendre $\&$ Laguerre]", fontsize=15)
plt.savefig(path+"CPU_Time_GQ")
plt.tight_layout()

plt.figure(5)
plt.plot(N_even, error_leg_even, marker="o", markersize=2, color="r",
         linewidth=0.5, linestyle="--", label='Legendre even')
plt.plot(N_odd, error_leg_odd, marker="o", markersize=2,
         linewidth=0.5, linestyle="--", label='Legendre odd')
plt.plot(N, error_lag, linewidth=0.5, linestyle="--", label='Laguerre')
plt.legend(loc='upper right', prop={"size": 10})
plt.xlabel("Number of iterations [N]", fontsize=14)
plt.ylabel('Relative error $\epsilon$', fontsize=14)
plt.title("Relative error [Legendre $\&$ Laguerre]", fontsize=15)
plt.savefig(path+"GQ_Relative_Error_Even_Odd")
plt.tight_layout()
plt.show()
