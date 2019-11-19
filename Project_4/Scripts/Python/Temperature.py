import numpy as np
import matplotlib.pyplot as plt
import time

from matplotlib import rc, rcParams

# Uncomment the section below for better looking font
"""
rc('text', usetex=True)
rc('font', **{'family': 'serif', 'serif': ['Helvetica']})
plt.style.use('classic')
path = "./"
"""

# Opening all files for L = 40, 60, 80, 100
graph_data1 = open(path + 'Temperature_40_Unordered_64.txt', 'r', encoding="utf8").read()
lines1 = graph_data1.split("\n")

graph_data2 = open(path + 'Temperature_60_Unordered_64.txt', 'r', encoding="utf8").read()
lines2 = graph_data2.split("\n")

graph_data3 = open(path + 'Temperature_80_Unordered_64.txt', 'r', encoding="utf8").read()
lines3 = graph_data3.split("\n")

graph_data4 = open(path + 'Temperature_100_Unordered_64.txt', 'r', encoding="utf8").read()
lines4 = graph_data4.split("\n")

# Critical temperature, not used.
T_C = 2.269

# Defining empty list for values of interest.
T = []

E1 = []
C_V1 = []
M1 = []
X1 = []

E2 = []
C_V2 = []
M2 = []
X2 = []

E3 = []
C_V3 = []
M3 = []
X3 = []

E4 = []
C_V4 = []
M4 = []
X4 = []


start = time.time()
# Looping thorugh each file and appending to lists.
for i in range(len(lines1)-2):
    if (i > 6 and i < len(lines1)):
        splitted_lines1 = lines1[i].split()
        splitted_lines2 = lines2[i].split()
        splitted_lines3 = lines3[i].split()
        splitted_lines4 = lines4[i].split()

        T.append(float(splitted_lines1[1]))

        E1.append(float(splitted_lines1[3]))
        C_V1.append(float(splitted_lines1[5]))
        M1.append(float(splitted_lines1[7]))
        X1.append(float(splitted_lines1[9]))

        E2.append(float(splitted_lines2[3]))
        C_V2.append(float(splitted_lines2[5]))
        M2.append(float(splitted_lines2[7]))
        X2.append(float(splitted_lines2[9]))

        E3.append(float(splitted_lines3[3]))
        C_V3.append(float(splitted_lines3[5]))
        M3.append(float(splitted_lines3[7]))
        X3.append(float(splitted_lines3[9]))

        E4.append(float(splitted_lines4[3]))
        C_V4.append(float(splitted_lines4[5]))
        M4.append(float(splitted_lines4[7]))
        X4.append(float(splitted_lines4[9]))

end = time.time()
print ("Code time:", end - start)
# May be used if one would like to divide temperature on T_C.
#T = list(map(lambda x: x/T_C, T1))

"""
Plotting all values given by the lists:
"""

# Energy vs Tempeature
plt.figure(1)
plt.margins(0)

plt.plot(T, E1, linewidth=0.5, linestyle="-", label="L  = 40")
plt.plot(T, E2, linewidth=0.5, linestyle="-", label="L = 60")
plt.plot(T, E3, linewidth=0.5, linestyle="-", label="L = 80")
plt.plot(T, E4, linewidth=0.5, linestyle="-", label="L = 100")
plt.legend(loc='upper left', prop={"size": 13})
plt.xlabel("Tempeature T [kT/J]", fontsize=16)
plt.ylabel("Mean energy" + r" $\langle E \rangle$", fontsize=16)
plt.title("Mean energy as a function of temperature", fontsize=17)
plt.tight_layout()


# Heat capacity vs Tempeature
plt.figure(2)
plt.margins(0)

# Finding for which temperature the max heat capacity occurs.
for i in range(len(C_V1)):
    if C_V1[i] == max(C_V1):
        T_CV1 = T[i]
plt.plot(T, C_V1, linewidth=0.5, linestyle="-", label='L = 40')
plt.plot(T_CV1, max(C_V1), marker="o", color="C0", markersize=4)

# Finding for which temperature the max heat capacity occurs.
for i in range(len(C_V2)):
    if C_V2[i] == max(C_V2):
        T_CV2 = T[i]
plt.plot(T, C_V2, linewidth=0.5, linestyle="-", label='L = 60')
plt.plot(T_CV2, max(C_V2), marker="o", color="C1", markersize=4)

# Finding for which temperature the max heat capacity occurs.
for i in range(len(C_V3)):
    if C_V3[i] == max(C_V3):
        T_CV3 = T[i]
plt.plot(T, C_V3, linewidth=0.5, linestyle="-", label="L = 80")
plt.plot(T_CV3, max(C_V3), marker="o", color="C2", markersize=4)


# Finding for which temperature the max heat capacity occurs.
for i in range(len(C_V4)):
    if C_V4[i] == max(C_V4):
        T_CV4 = T[i]
plt.plot(T, C_V4, linewidth=0.5, linestyle="-", label="L = 100")
plt.plot(T_CV4, max(C_V4), marker="o", color="C3", markersize=4)

# Plotting straight lines to visualize approximated curie temperature :
plt.plot([T_CV1, T_CV1], [min(C_V1), max(C_V1)], linestyle="--", color="k", linewidth=0.3)
plt.plot([T_CV2, T_CV2], [min(C_V1), max(C_V2)], linestyle="--", color="k", linewidth=0.3)
plt.plot([T_CV3, T_CV3], [min(C_V1), max(C_V3)], linestyle="--", color="k", linewidth=0.3)
plt.plot([T_CV4, T_CV4], [min(C_V1), max(C_V4)], linestyle="--", color="k", linewidth=0.3)

plt.legend(loc='upper right', prop={"size": 13})
plt.xlabel("Tempeature T [kT/J]", fontsize=16)
plt.ylabel('Heat capacity' + r" $C_V$", fontsize=16)
plt.title("Heat capacity as a function of temperature", fontsize=17)
plt.tight_layout()


# Magnetization vs Temperature
plt.figure(3)
plt.margins(0)

plt.plot(T, M1, linewidth=0.5, linestyle="-", label="L = 40")
plt.plot(T, M2, linewidth=0.5, linestyle="-", label="L = 60")
plt.plot(T, M3, linewidth=0.5, linestyle="-", label="L = 80")
plt.plot(T, M4, linewidth=0.5, linestyle="-", label="L = 100")
plt.legend(loc='upper right', prop={"size": 13})
plt.xlabel("Tempeature T [kT/J]", fontsize=16)
plt.ylabel('Mean magnetization' + r" $\langle$" + "$|M|$" + r"$\rangle$", fontsize=16)
plt.title("Mean magnetization as a function of temperature", fontsize=17)
plt.tight_layout()

# Susceptibility vs Tempeature
plt.figure(4)
plt.margins(0)

plt.plot(T, X1, linewidth=0.5, linestyle="-", label="L = 40")
plt.plot(T, X2, linewidth=0.5, linestyle="-", label="L = 60")
plt.plot(T, X3, linewidth=0.5, linestyle="-", label="L = 80")
plt.plot(T, X4, linewidth=0.5, linestyle="-", label="L = 100")

plt.legend(loc='upper right', prop={"size": 13})
plt.xlabel("Tempeature T [kT/J]", fontsize=16)
plt.ylabel('Susceptibility' + r" $\chi$", fontsize=16)
plt.title("Susceptibility as a function of temperature", fontsize=17)
plt.tight_layout()


# Interpolating using polyfit of first degree. Where L-inverse and the approximated curie temperature for L = [40, 60 ,80, 100].
TC = [T_CV1, T_CV2, T_CV3, T_CV4]
L_inv = [1./40, 1./60, 1./80, 1./100]

p = np.polyfit(L_inv, TC, 1)
slope, intercept = np.polyfit(L_inv, TC, 1)
u = np.linspace(0, 1./40, 100)   # Evaluate the polynomial at (other) points
v = np.polyval(p, u)

plt.figure(5)
plt.plot(L_inv, TC, "o", label="L = [40,60,80,100]")
plt.plot(u, v, "--r", linewidth=0.8,  label="y=%.4f x + %.4f" % (slope, intercept))
plt.legend(loc='upper left', prop={"size": 13})
plt.xlabel(r"$L^{-1}$", fontsize=16)
plt.ylabel(r'$T_C$ [kT/J]', fontsize=16)
plt.title("Approximation of" + r' $T_C$' + " for altered L", fontsize=17)
plt.grid(True)
plt.show()
