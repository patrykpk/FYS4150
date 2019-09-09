from pylab import *
import numpy as np
import os
import time

h = []
max_error_G = []
max_error_S = []

def read_file(filename):
	start_time = time.time()
	with open("./Results/" + filename, 'r') as infile:

		n = int(filename[17:-4])

		infile.readline()

		x = []
		Exact = []
		Error_G = []
		Error_S = []
		Approx_Special = []
		Approx_General = []

		for e in infile:
			x.append(float(e.split()[0]))
			Exact.append(float(e.split()[1]))
			Approx_Special.append(float(e.split()[2]))
			Approx_General.append(float(e.split()[3]))
			Error_G.append(float(e.split()[4]))
			Error_S.append(float(e.split()[5]))

		infile.close()
		print ("Yey")
		plt.figure()
		plt.plot(x, Approx_General, "--r", label="$v(x) - Numerical$", linewidth=3)
		plt.plot(x, Exact, "-k", label="$u(x) - Analytical$")
		plt.title("Numerical and analytical solutions with %d datapoints." % n,fontsize=13)
		plt.xlabel("$x$ values", fontsize=12)
		plt.xlim(0,1)
		plt.ylim(0,0.75)
		plt.ylabel("$u(x) \quad &\quad  v(x)  $", fontsize=12)
		plt.legend(loc=1, fontsize=13)
		savefig("./Plots/PlotComparison_%d" % n)

		h.append(log10(1.0/(n+1.0)))
		max_error_G.append(nanmax(Error_G))
		max_error_S.append(nanmax(Error_S))
		plt.show()

	#print (filename)
	#print("--- %s seconds ---" % (time.time() - start_time))

		#savefig("PlotComparison_%d" % (int(filename[17:-4])))

#Checks the current directory for files with a specific name
Prefix = [filename for filename in os.listdir("./Results") if filename.startswith("Project_1") and filename.endswith(".txt")]
print (Prefix)
#Reads the files and extracts values into arrays


def Read_File_List_Error(filename):
        start_time = time.time()
        n = int(filename[17:-4])
        with open("./Results/"+filename, 'r') as infile:
                infile.readline()
                Error_S = []
                Error_G = []
                for e in infile:
                        Error_G.append(float(e.split()[-2]))
                        Error_S.append(float(e.split()[-1]))
                print("--- %s seconds ---" % (time.time() - start_time))
                h.append(log10(1.0/(n+1)))
                max_error_G.append(nanmax(Error_G))
                max_error_S.append(nanmax(Error_S))


for name in Prefix:
	if int(name[17:-4]) <= 1000:
		read_file("%s" % name)

	else:
		Read_File_List_Error("%s" % name)

plt.plot(h, max_error_G)
plt.plot(h,max_error_S)
plt.show()








#File_content = read_file("Output_Proj10.dat")

		#print ("Det her er x-verdiene: ", Values_x)
		#print ("Det her er Approx: ", Values_Approx)

		#Det her gjør ingenting siden det er ingen plots
"""
		#Reads the size of arrays from the filename
		Array_size = int(filename[17:-4])

		#Include the starting point and ending point
		File_Values = zeros((Array_size+2,5))

		for i in range(Array_size+2):
			File_Values[i] = infile.readline().split()

		Values_x = File_Values[:,0]
		Values_Exact = File_Values[:,1]
		Values_Approx_General = File_Values[:,2]
		Values_Approx_Special = File_Values[:,3]
		Values_Error = File_Values[:,4]
"""