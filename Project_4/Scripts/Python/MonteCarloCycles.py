import numpy as np
import matplotlib.pyplot as plt
import time
#from matplotlib import rc, rcParams


# plt.style.use('classic')
def Read_File(filename):
	graph_data = open(filename, 'r', encoding="utf8").read()
	lines = graph_data.split("\n")

	Temperature = float(lines[1].split()[-1])
	Spin = lines[2].split()[-1]

	MC = []
	E = []
	C_V = []
	M = []
	X = []


	start = time.time()
	for i in range(len(lines)-2):
		if (i > 6 and i < len(lines)):
			splitted_lines = lines[i].split()
			MC.append(float(splitted_lines[1]))
			E.append(float(splitted_lines[3]))
			C_V.append(float(splitted_lines[5]))
			M.append(float(splitted_lines[7]))
			X.append(float(splitted_lines[9]))
	end = time.time()
	print (Spin)
	print ("Code time:", end - start)

	plt.figure(1)
	plt.xscale("log")
	plt.plot(MC, E, linewidth=0.1, linestyle="-", marker="o", markersize=0.8)
	#plt.scatter(T, E, s=0.5)
	# plt.legend(loc='upper right', prop={"size": 12})
	plt.xlabel("Monte Carlo Cycles", fontsize=14)
	plt.ylabel(r'Mean Energy $\langle E \rangle$', fontsize=14)
	plt.title("Mean energy at T = %.1f (%s) as a\n function of Monte Carlo Cycles" % (Temperature, Spin), fontsize=15)
	plt.tight_layout()
	#plt.xlim(0, 10000)
	#plt.ylim(-2.0, -1.995)
	#plt.plot([0, 100000], [-1.99598208594, -1.99598208594], linestyle='--', color="k")

	plt.figure(2)
	plt.plot(MC, C_V, linewidth=0.5, color="tab:orange",
	         linestyle="-", marker="o", markersize=0.8)
	#plt.plot([0, 100000], [0.03208, 0.03208], linestyle='--', color="k")
	# plt.legend(loc='upper right', prop={"size": 12})
	plt.xlabel("Monte Carlo Cycles", fontsize=14)
	plt.ylabel('Heat Capacity $C_V$', fontsize=14)
	plt.title("Heat capacity", fontsize=15)
	# plt.tight_layout()

	plt.figure(3)
	plt.xscale("log")
	plt.plot(MC, M, linewidth=0.5, linestyle="-", marker="o", markersize=0.8)
	# plt.legend(loc='upper right', prop={"size": 12})
	plt.xlabel("Monte Carlo Cycles", fontsize=14)
	plt.ylabel(r'Mean Magnetization $\langle \mathscr{M} \rangle$', fontsize=14)
	plt.title("Mean magnetization at T = %.1f (%s) as a\n function of Monte Carlo Cycles" % (Temperature, Spin), fontsize=15)
	# plt.tight_layout()

	plt.figure(4)
	plt.plot(MC, X, linewidth=0.5, linestyle="-", marker="o", markersize=0.8)
	# plt.legend(loc='upper right', prop={"size": 12})
	# plt.xlabel("Number of iterations [N]", fontsize=14)
	# plt.ylabel('Relative error $\epsilon$', fontsize=14)
	plt.title("Susceptibility", fontsize=15)
	# plt.tight_layout()
	plt.show()

#Read_File("MonteExpect_20_O_24_Riktig.txt") #FAKTISK RIKTIG
#Read_File("MonteExpect_20_O_1_Riktig.txt") #RIKTIG
#Read_File("MonteExpect_20_U_24_Riktig.txt") #RIKTIG 2.4 Temp
Read_File("MonteExpect_20_U_1_Riktig.txt") #RIKTIG FEIL INNHOLD