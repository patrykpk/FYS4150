from matplotlib.ticker import LinearLocator, FormatStrFormatter, LogFormatter
import matplotlib as mpl
from matplotlib import cm
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
import os
import matplotlib.pyplot as plt
from matplotlib import rc

rc('text', usetex=True)
rc('font', **{'family': 'serif', 'serif': ['Random']})

# Checking if the folder to store files exists
# otherwise stores the file in current directory
if os.path.exists("../../Results"):
	savepath = "../../Figures/"
else:
	savepath = "./Figures/"


fig = plt.figure(figsize=(8.0, 5.0))
ax = fig.gca(projection='3d')

r_1 = np.linspace(-3, 3, 1000)
r_2 = np.linspace(-3, 3, 1000)


x1, y1 = np.meshgrid(r_1, r_2)
F = np.exp(-2*np.sqrt(x1**2 + y1**2))

# Plot the surface.
ax.tick_params(labelsize=14)

surf = ax.plot_surface(x1, y1, F, cmap=cm.jet,
                       linewidth=0)

cbar = fig.colorbar(surf, shrink=0.8, aspect=30)
cbar.ax.tick_params(labelsize=14)

# Checking if a directory for storing the plots exists,
# if not, then a folder is made
if not os.path.exists(savepath):
    os.makedirs(savepath)
else:
    print ("Folder already exists")

ax.set_xlabel('$x$', fontsize=16)
ax.set_ylabel('$y$', fontsize=16)
ax.set_zlabel('$|\psi(x,y)|^2$', fontsize=17)
plt.title("Probability density : Approximating [$\infty$ $\\rightarrow$ $\lambda$]", fontsize=20)
plt.savefig(savepath+"Probability_Density_3D")
plt.show()