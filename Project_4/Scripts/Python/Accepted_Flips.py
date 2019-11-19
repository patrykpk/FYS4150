from numpy import *
import matplotlib.pyplot as plt

Monte = []
Flips = []

Lattice = 20*20          # Total amount of spins
Amount_of_Data = 100000; # Lines with data

# Function to read files
def Read_File(filename):
	with open(filename, 'r', encoding="utf8") as infile:
		lines =infile.read().split("\n")
		# Looping over the content of the file and appending to lists
		for i in range(len(lines)-2):
			if (i > 6 and i < len(lines)):
				splitted_lines = lines[i].split()
				Monte.append(float(splitted_lines[0]))
				Flips.append(float(splitted_lines[1]))

Read_File("Accepted_Flips_20_O_24_Riktig.txt")
Read_File("Accepted_Flips_20_U_24_Riktig.txt")
Read_File("Accepted_Flips_20_O_1_Riktig.txt")
Read_File("Accepted_Flips_20_U_1_Riktig.txt")


# Plotting
plt.figure(1)
plt.title("Ratio of accepted spin configurations as a function\n of Monte Carlo cylces (T = 2.4)", fontsize=15)
plt.plot(Monte[0:Amount_of_Data], asarray(Flips[0:Amount_of_Data])/Lattice, label="Ordered")
plt.plot(Monte[Amount_of_Data:Amount_of_Data*2], asarray(Flips[Amount_of_Data:Amount_of_Data*2])/Lattice, label="Unordered")
plt.xlabel("Monte Carlo Cycles", fontsize=14)
plt.ylabel("Ratio of accepted spins", fontsize=14)
plt.legend(prop={"size": 13})
plt.xscale("log")
plt.show()

plt.figure(2)
plt.title("Ratio of accepted spin configurations as a function\n of Monte Carlo cylces (T = 1.0)", fontsize=15)
plt.plot(Monte[Amount_of_Data*2:Amount_of_Data*3], asarray(Flips[Amount_of_Data*2:Amount_of_Data*3])/Lattice, label="Ordered")
plt.plot(Monte[Amount_of_Data*3:Amount_of_Data*4], asarray(Flips[Amount_of_Data*3:Amount_of_Data*4])/Lattice, label="Unordered")
plt.xlabel("Monte Carlo Cycles", fontsize=14)
plt.ylabel("Ratio of accepted spins", fontsize=14)
plt.legend(prop={"size": 13})
plt.xscale("log")
plt.show()
