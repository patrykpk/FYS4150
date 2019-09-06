from pylab import *
import numpy as np
import os
import time

def read_file(filename):
	start_time = time.time()
	with open(filename, 'r') as infile:
		infile.readline()

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

	#print (filename)
	#print("--- %s seconds ---" % (time.time() - start_time))

		#savefig("PlotComparison_%d" % (int(filename[17:-4])))

		

#Checks the current directory for files with a specific name
Prefix = [filename for filename in os.listdir(".") if filename.startswith("Project_1") and filename.endswith(".txt")]

#Reads the files and extracts values into arrays
for i in Prefix:
	read_file("%s" % i)








#File_content = read_file("Output_Proj10.dat")

		#print ("Det her er x-verdiene: ", Values_x)
		#print ("Det her er Approx: ", Values_Approx)

		#Det her gjør ingenting siden det er ingen plots
