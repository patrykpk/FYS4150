import numpy as np
import matplotlib.pyplot as plt
from matplotlib import colors
from scipy.stats import kde
from matplotlib import animation
import time
from matplotlib import rc, rcParams

rc('text', usetex=True)
rc('font', **{'family': 'serif', 'serif': ['Random']})

Path = '/Users/kristoffervarslott/Documents/C++/GitHub_Projects/FYS4150/Project_5/Results/1D - Diffusion'

# Defining a function Readfile that takes filename for argument, visualicaion later on.
# Reading files for the schemes under investigation.


def ReadFile(filename):
    Matrix = open(Path + filename, 'r').read()
    lines = Matrix.split("\n")
    Liste = []
    # Looping over every line in file, and appending into list.
    for k in range(len(lines)-1):
        splitted_lines = lines[k].split()
        c = list(map(float, splitted_lines))
        A = splitted_lines
        Liste.append(c)
    return Liste

# The analytical solution, which may be found in pdf located in ; https://github.com/patrykpk/FYS4150/tree/master/Project_5


def Analytic_solution(N, x, t):
    sum = 0
    for n in range(1, N):
        sum += (2.0*(-1)**n/(n*np.pi)*np.sin(x*np.pi*n)*np.exp(-np.pi*np.pi*n*n*t))
    f = sum + x
    return f


#####################################################################################################
# First files for dx = 0.1
FE = ReadFile("/FE_1D_0.100000.txt")
BE = ReadFile("/BE_1D_0.100000.txt")
CN = ReadFile("/CN_1D_0.100000.txt")

# Defining step-length to be 0.1:
x = np.linspace(0, 1, 10)
N_1 = 2
N_2 = 20
t_1 = N_1*0.005
t_2 = N_2*0.005


# Plotting values of u(x,t_1)
plt.figure(1)
plt.plot(x, FE[N_1], label="FE")
plt.plot(x, BE[N_1], label="BE")
plt.plot(x, CN[N_1], label="CN")
plt.title("Solution for $t_1 = 0.01s$, where $\Delta x = 0.1$", fontsize=15)
plt.plot(x, Analytic_solution(10, x, t_1), label="Analytic")
plt.xlabel("x", fontsize=14)
plt.ylabel("u(x,t=0.01)", fontsize=14)
plt.legend(prop={"size": 13})

# Plotting values of u(x,t_2)
plt.figure(2)
plt.plot(x, FE[N_2], label="FE")
plt.plot(x, BE[N_2], label="BE")
plt.plot(x, CN[N_2], label="CN")
plt.title("Solution for $t_2 = 0.1s$, where $\Delta x = 0.1$", fontsize=15)
plt.plot(x, Analytic_solution(10, x, t_2), label="Analytic")
plt.xlabel("x", fontsize=14)
plt.ylabel("u(x,t=0.1)", fontsize=14)
plt.legend(prop={"size": 13})

#####################################################################################################

# Second files for dx = 0.01
FE1 = ReadFile("/FE_1D_0.010000.txt")
BE1 = ReadFile("/BE_1D_0.010000.txt")
CN1 = ReadFile("/CN_1D_0.010000.txt")

# Defining step-length to be 0.01:
x1 = np.linspace(0, 1, 100)
N_3 = 200
N_4 = 2000
t_3 = N_3*5e-5
t_4 = N_4*5e-5

# Plotting values of u(x1,t_1)
plt.figure(3)
plt.plot(x1, (FE1[N_3]), label="FE")
plt.plot(x1, (BE1[N_3]), label="BE")
plt.plot(x1, (CN1[N_3]), label="CN")
plt.title("Solution for $t_1 =0.01 s$, where $\Delta x = 0.01$", fontsize=15)
plt.plot(x1, Analytic_solution(100, x1, t_3), label="Analytic")
plt.xlabel("x", fontsize=14)
plt.ylabel("u(x,t=0.01)", fontsize=14)
plt.legend(prop={"size": 13})

# Plotting values of u(x1,t_2)
plt.figure(4)
plt.plot(x1, (FE1[N_4]), label="FE")
plt.plot(x1, (BE1[N_4]), label="BE")
plt.plot(x1, (CN1[N_4]), label="CN")
plt.title("Solution for $t_2 = 0.1s$, where $\Delta x = 0.01$", fontsize=15)
plt.plot(x1, Analytic_solution(100, x1, t_4), label="Analytic")
plt.xlabel("x", fontsize=14)
plt.ylabel("u(x,t=0.1)", fontsize=14)
plt.legend(prop={"size": 13})
plt.show()

#####################################################################################################
# To find x-values need to loop over j = 0-9. each j need to be summed in order to collect rel_error.

# Relative error for dx = 0.1: Where Shemes refers to the three files for dx = 0.1:


def Rel_error_schemes(Scheme):
    x = np.linspace(0, 1, 11)
    Rel_error_final = []
    t = []
    for i in range(1, len(FE)-2):
        t_new = float(i * 0.005)
        analytic = Analytic_solution(10, x[1:-1], t_new)
        for j in range(1, 9):
            # Summation over all x-values for a given time(Depending on value of i).
            sum1 = 0
            sum2 = 0
            sum1 += (Scheme[i][j] - analytic[j])**2
            sum2 += analytic[j]**2
        # Collecting sum and defining the relative error
        Rel_error = np.sqrt(sum1/sum2)
        t.append(t_new)
        Rel_error_final.append(Rel_error)
    return Rel_error_final, t


# Inserting for the three different schemes
Rel_error_FE = Rel_error_schemes(FE)
Rel_error_BE = Rel_error_schemes(BE)
Rel_error_CN = Rel_error_schemes(CN)


# Plotting relative error for dx = 0.1
plt.figure(3)
# t = np.linspace(0, 1, len(FE)-1)
plt.plot(Rel_error_FE[1], Rel_error_FE[0], label="FE")
plt.plot(Rel_error_BE[1], Rel_error_BE[0], label="BE")
plt.plot(Rel_error_CN[1], Rel_error_CN[0], label="CN")
plt.legend(prop={"size": 13})
plt.title("Relative error as a function of time [t] for $\Delta x = 0.1$", fontsize=15)
plt.xlabel("t [s]", fontsize=14)
plt.ylabel("$\epsilon(t)$", fontsize=14)
plt.tight_layout()

#####################################################################################################


# Relative error for dx = 0.01. Same procedure, with different size of matrix-defined by dx = 0.01.
def Rel_error_schemes1(Scheme):
    x1 = np.linspace(0, 1, 101)
    t = []
    Rel_error_final = []
    for i in range(0, len(FE1)-2):
        t_new = float(i * 0.00005)
        analytic = Analytic_solution(100, x1[1:-1], t_new)
        for j in range(1, 99):
            # Summation over all x-values for a given time(Depending on value of i).
            sum1 = 0
            sum2 = 0
            sum1 += (Scheme[i][j] - analytic[j])**2
            sum2 += analytic[j]**2
        # Collecting sum and defining the relative error
        Rel_error = np.sqrt(sum1/sum2)
        t.append(t_new)
        Rel_error_final.insert(i, Rel_error)
    return Rel_error_final, t


# Inserting for the three different schemes
Rel_error_FE1 = Rel_error_schemes1(FE1)
Rel_error_BE1 = Rel_error_schemes1(BE1)
Rel_error_CN1 = Rel_error_schemes1(CN1)

# Plotting relative error for dx = 0.01
plt.figure(4)
plt.plot(Rel_error_FE1[1], Rel_error_FE1[0], label="FE")
plt.plot(Rel_error_BE1[1], Rel_error_BE1[0], label="BE")
plt.plot(Rel_error_CN1[1], Rel_error_CN1[0], label="CN")
plt.legend(prop={"size": 13})
plt.title("Relative error as a function of time [t] for $\Delta x = 0.01$", fontsize=15)
plt.xlabel("t [s]", fontsize=14)
plt.ylabel("$\epsilon(t)$", fontsize=14)
plt.tight_layout()
plt.show()
