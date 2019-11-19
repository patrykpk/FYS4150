import numpy as np
import matplotlib.pyplot as plt
import time


# plt.style.use('classic')
# Function for reading the file
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
	# Omitting the information on the first lines
	# Looping over the rest and appending values into lists
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

	# Plotting
	plt.figure(1)
	plt.xscale("log")
	plt.plot(MC, E, linewidth=0.1, linestyle="-", marker="o", markersize=0.8)

	plt.xlabel("Monte Carlo Cycles", fontsize=14)
	plt.ylabel(r'Mean Energy $\langle E \rangle$', fontsize=14)
	plt.title("Mean energy at T = %.1f (%s) as a\n function of Monte Carlo Cycles" % (Temperature, Spin), fontsize=15)
	plt.tight_layout()

	# Not used (Uncomment if wanted)
	"""
	plt.figure(2)
	plt.plot(MC, C_V, linewidth=0.5, color="tab:orange",
	         linestyle="-", marker="o", markersize=0.8)

	plt.xlabel("Monte Carlo Cycles", fontsize=14)
	plt.ylabel('Heat Capacity $C_V$ as a function\n of Monte Carlo cycles', fontsize=14)
	plt.title("Heat capacity", fontsize=15)
	"""

	plt.figure(3)
	plt.xscale("log")
	plt.plot(MC, M, linewidth=0.5, linestyle="-", marker="o", markersize=0.8)
	plt.xlabel("Monte Carlo Cycles", fontsize=14)
	plt.ylabel(r'Mean Magnetization $\langle \mathscr{M} \rangle$', fontsize=14)
	plt.title("Mean magnetization at T = %.1f (%s) as a\n function of Monte Carlo Cycles" % (Temperature, Spin), fontsize=15)

	# Not used (Uncomment if wanted)
	"""
	plt.figure(4)
	plt.plot(MC, X, linewidth=0.5, linestyle="-", marker="o", markersize=0.8)
	plt.xlabel("Monte Carlo Cycles", fontsize=14)
	plt.ylabel(r"Susceptibility $\chi$", fontsize=14)
	plt.title("Susceptibility as a function\n of Monte Carlo cycles", fontsize=15)
	plt.show()
	"""

#Read_File("MonteExpect_20_O_24_Riktig.txt")
#Read_File("MonteExpect_20_O_1_Riktig.txt")
#Read_File("MonteExpect_20_U_24_Riktig.txt")
Read_File("MonteExpect_20_U_1_Riktig.txt")