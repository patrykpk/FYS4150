from numpy import *
import matplotlib.pyplot as plt

N = 1001
x = linspace(0,1, N)

"""
Bruke de her?
dt = (x[1]-x[0])**2/2
t = arange(0, 0.05, dt)
#print (x)
"""

t = linspace(0,1, N)

#print (t)

def Func(N, x,t):
	sum = 0
	for n in range(1, N):
		sum += (2.0*(-1)**n/(n*pi)*sin(x*pi*n)*exp(-pi*pi*n*n*t))
	f = sum + x
	return f
	#print (f)

#Func(10000, 1.89085, x)

plt.plot(x, Func(10000,x,t))
plt.show()


#Func(10000, 5, x)
#print (t)
#print (dt)
#print (x)
