import matplotlib.pyplot as plt
import numpy as np
import os

def Read_file(filename):
    """
    Reading a file with specific name and extracting the n value from it.
    Stores additional information for files with small amount of datapoints (n)
    within lists in order to make plots. Otherwise omitting that and only extracting
    the error and step length.
    """

    #Extracts the value of n from the name
    n = int(filename[17:-4])

    with open(filename, 'r') as infile:

    	#Storing the error values within the function
        Error_S = []    #Special
        Error_G = []    #General

        infile.readline()

        #Stores additional information
        if n <= 1000:
            x = []
            Exact = []
            Approx_Special = []
            Approx_General = []

            #Reads the file and extracts values into lists
            for e in infile:
                x.append(float(e.split()[0]))
                Exact.append(float(e.split()[1]))
                Approx_Special.append(float(e.split()[2]))
                Approx_General.append(float(e.split()[3]))
                Error_G.append(float(e.split()[4]))
                Error_S.append(float(e.split()[5]))
           
            infile.close()


            #Plotting the figure for numerical and analytical solution
            plt.figure()
            plt.plot(x, Approx_Special, "--r", label="$v(x) - Numerical$", linewidth=3)
            plt.plot(x, Exact, "-k", label="$u(x) - Analytical$")
            plt.title("Numerical and analytical solutions with %d datapoints." % n, fontsize=13)
            plt.xlabel("$x$ values", fontsize=12)
            plt.xlim(0,1)
            plt.ylim(0,0.75)
            plt.ylabel("$u(x) \quad &\quad  v(x)  $", fontsize=12)
            plt.legend(loc=1, fontsize=13)
            plt.savefig("./Plots/PlotComparison_%d" % n)

        else:
            #Extracting the error and step length
            for e in infile:
                Error_G.append(float(e.split()[4]))
                Error_S.append(float(e.split()[5]))

            infile.close()

        #Appending to lists outside the function to keep them
        h.append(np.log10(1.0/(n+1.0)))            #Step Length
        max_error_G.append(np.nanmax(Error_G))     #Max relative error for general case
        max_error_S.append(np.nanmax(Error_S))     #Max relative error for special case

#---------------------------------------------------------------------------------------

#Checking if a directory for storing the plots exists
#if not then a folder is made
if not os.path.exists("Plots"):
    os.makedirs("Plots")
else:
    print ("Folder already exists")

#Storing the error and step length for every file
h = []
max_error_G = []
max_error_S = []


#Checking the current directory for files with a specific name
Prefix = [filename for filename in os.listdir(".") if filename.startswith("Project_1_Results") and filename.endswith(".txt")]
Prefix.sort()
print ("Listing files with matching name: ", Prefix)

#Running through the files with desired name
for name in Prefix:
    Read_file("%s" % name)

#Plotting the figure for error vs step length
plt.figure()
plt.title("Comparison of error between general and special alorithm.", fontsize=12)
plt.plot(h, max_error_G, "-k", label="$\epsilon$: General algorithm")
plt.plot(h, max_error_S, "--r", label="$\epsilon$: Special algorithm", linewidth=2)
plt.xlabel("Logarithmic stepsize     [$\log_{10}(h)$]", fontsize=12)
plt.ylabel("Logarithmic relative error     [$\epsilon$]", fontsize=12)
plt.legend(fontsize=13)
plt.savefig("./Plots/PlotError")
plt.show()
