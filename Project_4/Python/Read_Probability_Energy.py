import matplotlib.pyplot as plt
from numpy import *

def Read_File(filename):
	with open(filename, 'r', encoding="utf8") as infile:
		lines = infile.read().split("\n")
		Temperature = float(lines[1].split()[-1])
		Amount_of_Data = len(lines[7:-1])
		print (Amount_of_Data)
		Energy = zeros(Amount_of_Data-1)
		for i in range(7, Amount_of_Data+6):
			split_line = lines[i].split()
			Energy[i-7] = float(split_line[3])

		std = Energy.std()
		weights = ones_like(Energy)/float(len(Energy))

		# Change amount of bins based on what you plot (T = 1 use 5 bins, T = 2.4 use 122 bins)
		plt.hist(Energy, bins=122, weights=weights, edgecolor='black', linewidth=1.3, align="left")
		plt.title("Probability distribution for the energy T = %.1f" % (Temperature), fontsize=15)
		plt.ylabel("Probability P(E)", fontsize=14)
		plt.xlabel("Energy E", fontsize=14)
		plt.legend([r"$\sigma_E$=%.4f" % std], fontsize=12)
		plt.show()

# Plot one at a time
#Read_File("Data_After_Equilibrium_20_1_1000000.txt")
Read_File("Data_After_Equilibrium_20_24_1000000.txt")

