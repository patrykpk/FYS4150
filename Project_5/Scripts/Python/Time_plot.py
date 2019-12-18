
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import colors
from scipy.stats import kde
from matplotlib import animation
import time
from matplotlib import rc, rcParams

#rc('text', usetex=True)
#rc('font', **{'family': 'serif', 'serif': ['Random']})

# Opening the file to be read.
#Matrix = open('data_BE.dat', 'r').read()

#t1 = 
#t2 = 

dt = 0.005
T = 1

TimeValue = 0.01
Index = TimeValue/5e-5

print (Index)


ChoosenTime = 25*0.005
print (ChoosenTime)

#ChooseTime = T/dt*

def ReadFile(filename):
    Matrix = open(filename, 'r').read()
    lines = Matrix.split("\n")
    Liste = []
    for k in range(len(lines)-1):
        splitted_lines = lines[k].split()
        c = list(map(float, splitted_lines))
        A = splitted_lines
        Liste.append(c)
    return Liste


# Defining a funciton matrix for visualicaion later on.
def matrix(i):
    Liste = []
    # Looping over every line in file, and appending into list.
    for k in range(len(lines)-1):
        splitted_lines = lines[k].split()
        c = list(map(float, splitted_lines))
        A = splitted_lines
        Liste.append(c)

    L = Liste[i]

    return L

def Func(N, x,t):
    sum = 0
    for n in range(1, N):
        sum += (2.0*(-1)**n/(n*np.pi)*np.sin(x*np.pi*n)*np.exp(-np.pi*np.pi*n*n*t))
    f = sum + x
    return f

FE = ReadFile("FE_1D_0.100000.txt")
BE = ReadFile("BE_1D_0.100000.txt")
CN = ReadFile("CN_1D_0.100000.txt")


print (FE[2])
print (BE[2])
print (CN[2])


x = np.linspace(0, 1, 10)
#plt.plot(x, FE[5], label="FE")
#plt.plot(x, BE[5], label="BE")
#plt.plot(x, CN[5], label="CN")
#plt.legend()

FE1 = ReadFile("FE_1D_0.010000.txt")
BE1 = ReadFile("BE_1D_0.010000.txt")
CN1 = ReadFile("CN_1D_0.010000.txt")

x1 = np.linspace(0, 1, 100)
plt.semilogy(x1, (FE1[200]), label="FE")
plt.semilogy(x1, (BE1[200]), label="BE")
plt.semilogy(x1, (CN1[200]), label="CN")
plt.legend()

#plt.plot(x1, Func(10000,x1,t)-FE[200])

t = 0.01
plt.semilogy(x1, Func(10000,x1,t), color="k", label="Analytic")


tid = 5e-5*200
print (tid)

#print (matrix())

#plt.plot(x, matrix(100))
plt.show()

# Plotting over the range of 100 Monte Carlo cycles.
"""
x = np.linspace(0, 1, 100)
plt.figure()
for i in range(1000):
    plt.plot(x, matrix(i))
    plt.pause(0.001)
plt.show()
"""
