from pylab import *
import numpy as np
import os
import matplotlib.pyplot as plt

h = []
max_error = []
def read_file(filename):
	with open(filename, 'r') as infile:
                infile.readline()
                Array_size = int(filename[17:-4]) #Reads the size of arrays from the filename
                File_Values = np.zeros((Array_size+2,5))
                for i in range(Array_size+2):
                        File_Values[i] = infile.readline().split()
                Values_x = File_Values[:,0]
                Values_Exact = File_Values[:,1]
                Values_Approx_General = File_Values[:,2]
                Values_Approx_Special = File_Values[:,3]
                Values_Error = File_Values[:,4]
        #infile.close()
        

                plt.figure()
                plt.plot(Values_x, Values_Approx_General, "-k", label="$v(x) - Numerical$", linewidth=3)
                plt.plot(Values_x, Values_Exact, "--r", label="$u(x) - Analytical$")
                plt.title("Numerical and analytical soulutions with %d datapoints." % (int(filename[17:-4])),fontsize=13)
                plt.xlabel("$x$ values", fontsize=12)
                plt.xlim(0,1)
                plt.ylim(0,0.75)
                plt.ylabel("$u(x) \quad &\quad  v(x)  $", fontsize=12)
                plt.legend(loc=1, fontsize=13)
                savefig("PlotComparison_%d" % (int(filename[17:-4])))
        
                h.append(log10(1.0/(Array_size+1.0)))
                max_error.append(max(Values_Error[1:-1]))
                plt.show()
        
        
		

#Checks the current directory for files with a specific name
Prefix = [filename for filename in os.listdir(".") if filename.startswith("Project_1") and filename.endswith(".txt")]
print (Prefix)
#Reads the files and extracts values into arrays
for i in Prefix:
	read_file("%s" % i)
"""
plt.plot(h,max_error)
plt.show()
"""