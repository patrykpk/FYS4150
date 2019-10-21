import numpy as np
import matplotlib.pyplot as plt
import time
from matplotlib import rc, rcParams

rc('text', usetex=True)
rc('font', **{'family': 'serif', 'serif': ['Random']})

# plt.style.use('classic')

# Checks if the file is found in either the same directory
# or within a folder with results (Layout from Github)
path = False
for filename in os.listdir("./"):
    if filename == "Project_3_MC.txt":
        path = "Project_3_MC.txt"
        savepath = "./Figures/"

if os.path.exists("../../Results"):
    for filename in os.listdir("../../Results"):
        if filename == "Project_3_MC.txt":
            path = "../../Results/Project_3_MC.txt"
            savepath = "../../Figures/"

if not path:
    print ("File not found")

graph_data = open(path, 'r').read()

lines = graph_data.split("\n")

N = []

MC_BF = []
MC_IS = []

CPU_MC_BF = []
CPU_MC_IS = []

SD_BF = []
SD_IS = []

Exact = []

start = time.time()
for i in range(len(lines)-1):
    if (i > 1 and i < len(lines)):
        splitted_lines = lines[i].split()
        c = list(map(float, splitted_lines))
        N.append(c[0])           # Appends value of N
        MC_BF.append(c[1])       # Integral of Monte Carlo Brute Force
        CPU_MC_BF.append(c[2])   # CPU time for Monte Carlo Brute Force
        SD_BF.append(c[3])       # Standard devation for Monte Carlo Brute Force
        MC_IS.append(c[4])       # Integral of Monte Carlo Importance Sampling
        CPU_MC_IS.append(c[5])   # CPU time for Monte carlo Importance Sampling
        SD_IS.append(c[6])       # Standard deviation for Monte Carlo Importance Sampling
        Exact.append(c[7])       # Exact value of the integral

end = time.time()
print ("Code time:", end - start)

# Checking if a directory for storing the plots exists,
# if not, then a folder is made
if not os.path.exists(savepath):
    os.makedirs(savepath)
else:
    print ("Folder already exists")

plt.figure(1)
plt.xscale('log')
plt.plot(N, MC_BF, linewidth=0.5, linestyle="-", label='MC brute force')
plt.plot(N, Exact, linewidth=0.5, color="tab:green", linestyle="--", label='Exact solution')
plt.legend(loc='upper right', prop={"size": 10})
plt.xlabel("Number of iterations [N]", fontsize=14)
plt.ylabel('Approximated solution of integral', fontsize=14)
plt.title("Solution based on Monte Carlo [Brute force]", fontsize=15)
#plt.xlim(10000, 1000000000)
#plt.ylim(0.035, 0.7)
plt.tight_layout()

plt.figure(2)
plt.xscale('log')
plt.plot(N, MC_IS, linewidth=0.5, color="tab:orange", linestyle="-", label='MC Importance sampling')
plt.plot(N, Exact, linewidth=0.5, linestyle="--", color="tab:green", label='Exact solution')
plt.legend(loc='upper right', prop={"size": 10})
plt.xlabel("Number of iterations [N]", fontsize=14)
plt.ylabel('Approximated solution of integral', fontsize=14)
plt.title("Solution based on Monte Carlo [Importance sampling]", fontsize=15)
#plt.xlim(10000, 1000000000)
#plt.ylim(0.182, 0.215)
plt.tight_layout()

plt.figure(3)
plt.xscale('log')
plt.plot(N, SD_BF, linewidth=0.5, linestyle="-", label='Brute force')
plt.plot(N, SD_IS, linewidth=0.5, linestyle="-", label='Importance sampling')
plt.legend(loc='upper right', prop={"size": 10})
plt.xlabel("Number of iterations [N]", fontsize=14)
plt.ylabel('Relative error $\epsilon$', fontsize=14)
plt.title("Relative error [brute force $\&$ importance sampling]", fontsize=15)
#plt.xlim(10000, 1000000000)
#plt.ylim(-0.2, 2.55)
plt.tight_layout()


plt.figure(4)

plt.loglog(N, CPU_MC_BF, linewidth=0.5, linestyle="-", label='brute force')
plt.loglog(N, CPU_MC_IS, linewidth=0.5, linestyle="-", label='Importance sampling')

plt.loglog(N_1, CPU_4_BF, linewidth=0.5, linestyle="--", label='brute force')
plt.loglog(N_1, CPU_4_IS, linewidth=0.5, linestyle="--", label='Importance sampling')
plt.legend(loc='upper left', prop={"size": 10})
plt.xlabel("Number of iterations [N]", fontsize=14)
plt.ylabel('CPU-time [s]', fontsize=14)
plt.title("CPU-time [brute force $\&$ importance sampling]", fontsize=15)

plt.tight_layout()


plt.show()
