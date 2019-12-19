# Libraries
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import colors
from matplotlib import cm
from mpl_toolkits.mplot3d import Axes3D

#---------------------------------------------------------------------
# Uncomment one file at a time

#Matrix = open('./Implicit2D_0.100000_dt=0.0025_T0.1.txt', 'r').read()
#Matrix = open('./Explicit2D_0.100000_dt=0.0025_T0.1.txt', 'r').read()

Matrix = open('./Implicit2D_0.010000_dt=0.000025_T0.1.txt', 'r').read()
#Matrix = open('./Explicit2D_0.010000_dt=0.000025_T0.1.txt', 'r').read()

#Matrix = open('./Compare_Implicit2D_vs_Analytic_0.100000_dt=0.0025_T0.1.txt', 'r').read()
#Matrix = open('./Compare_Explicit_vs_Analytic_0.100000_dt=0.0025_T0.1.txt', 'r').read()

#Matrix = open('./Compare_Implicit2D_vs_Analytic_0.010000_dt=0.000025_T0.1.txt', 'r').read()
#Matrix = open('./Compare_Explicit_vs_Analytic_0.010000_dt=0.000025_T0.1.txt', 'r').read()

#Matrix = open('./NoStability_Explicit2D_0.010000_t=0.1_dt=0.000026.txt', 'r').read()

lines = Matrix.split("\n")

# Change this input based on the file
Time = 0.1
dx = 0.1
Scheme = "Explicit"


#---------------------------------------------------------------------------------

# Defining a funciton matrix for visualicaion later on.
def matrix(i):
    Liste = []
    # Looping over every line in file, and appending into list.
    for k in range(len(lines)):
        if (k >= 0 and k <= len(lines)):
            splitted_lines = lines[k].split()
            Size = splitted_lines
            c = list(map(float, splitted_lines))
            # print (lines)
            if (splitted_lines == []):
                None
            else:
                A = splitted_lines
                Liste.append(c)

    L = Liste[len(A)*i:(len(A)*i+len(A))]
    L = np.asarray(L)
    return L

Values = matrix(0)
Size = (len(Values))

x = np.linspace(0, 1, Size+1)
y = np.linspace(0, 1, Size+1)
x,y = np.meshgrid(x,y)

# Plotting of the heatmap in 2D
# Change cmap to "Greys" when comparing and remove vmin and vmax
plt.pcolor(x,y, abs(matrix(0)), edgecolors="k", cmap=cm.jet, vmin=0, vmax=1)
plt.xlabel("$x$", fontsize=14)
plt.ylabel("$y$", fontsize=14)
plt.title(r"%s Scheme for t = %.2fs and $\Delta$x = %.2f " % (Scheme, Time, dx))
cbar = plt.colorbar()
cbar.set_label("$u(x, y, t = %.2fs)$" % (Time), fontsize = 12)
plt.show()

#---------------------------------------------------------------------------------

def Analytic_2D(x,y,t):
	f = np.sin(np.pi*x)*np.sin(np.pi*y)*np.exp(-2*np.pi**2*t)
	return f


# Don't know why but the grid starts in the bottom left corner,
# so in order to show 1.0 I have to linspace up to 1.1
x = np.linspace(0, 1.1, Size+1)
y = np.linspace(0, 1.1, Size+1)

x, y = np.meshgrid(x,y)

# Plotting of the heatmap in 2D
plt.pcolor(x,y, Analytic_2D(x,y,Time), edgecolors="k", cmap=cm.jet, vmin=0, vmax=1)
plt.xlabel("$x$", fontsize=14)
plt.ylabel("$y$", fontsize=14)
plt.title(r"Analytic solution for t = %.2fs and $\Delta$x = %.2f " % (Time, dx))
cbar = plt.colorbar()
cbar.set_label("$u(x, y, t = %.2fs)$" % (Time), fontsize = 12)
plt.show()

#---------------------------------------------------------------------------------

# Plotting the values in 3D

x = np.linspace(0, 1, Size)
x, y = np.meshgrid(x, x)

fig = plt.figure(figsize=(8.0,5.0))
ax = fig.gca(projection="3d")
ax.set_zlim(0, 1.00)
surf = ax.plot_surface(x, y, Analytic_2D(x,y,Time), cmap=cm.jet, vmin=0, vmax=1)
ax.set_xlabel("$x$", fontsize=14)
ax.set_ylabel("$y$", fontsize=14)
ax.set_zlabel("u(x,y,t = %.2f)" % (Time), fontsize=14)
ax.tick_params(labelsize=12)
#plt.title(r"Initial function at t = 0 with $\Delta$x = 0.01")
plt.title(r"Analytic solution in 2D for t = %.2f and $\Delta$x = %.2f" % (Time, dx))
cbar = fig.colorbar(surf, shrink=0.8, aspect=30)
cbar.ax.tick_params(labelsize=12)


#---------------------------------------------------------------------------------

# Plotting the values in 3D

data = np.array(matrix(0))

fig = plt.figure(figsize=(8.0,5.0))
ax = fig.gca(projection="3d")
ax.set_zlim(0, 1.00)
surface1 = ax.plot_surface(x,y,abs(data), cmap=cm.jet, vmin=0, vmax=1)
ax.set_xlabel("$x$", fontsize=14)
ax.set_ylabel("$y$", fontsize=14)
ax.set_zlabel("u(x,y,t = %.2f)" % (Time), fontsize=14)
ax.tick_params(labelsize=12)
cbar = fig.colorbar(surface1, shrink=0.8, aspect=30)
cbar.ax.tick_params(labelsize=12)
plt.title(r"%s Scheme in 2D for t = %.2f and $\Delta$x = %.2f" % (Scheme, Time, dx))
plt.show()

#---------------------------------------------------------------------------------





















"""
#fig.colorbar(surf, shrink=0.8, aspect=30)
x, y = np.meshgrid(len(matrix(0)), len(matrix(0)))

data = np.array(matrix(0))

fig = plt.figure()
ax = fig.gca(projection="3d")
ax.set_zlim(0, 1.00)
surf = ax.plot_surface(x, y, data, cmap=cm.jet)

cbar = fig.colorbar(surf, shrink=0.8, aspect=30)
#cbar.ax.tick_params(labelsize=14)
"""
#plt.show()


"""
def plot(f):
	x = np.linspace(0, 1, 1); y = np.linspace(0,1, 11)
	x, y = np.meshgrid(x,y)
	plt.pcolormesh(x,y,f, cmap="inferno")
	plt.show()

data = np.loadtxt('./Hello.txt')
plot(data)
"""