import matplotlib.pyplot as plt     
from numpy import *                  
import os
from matplotlib import rc
import matplotlib.patches as patch

rc("text", usetex=True)
rc('font', **{'family': 'serif', 'serif': ['Random']})

#------ Jacobi's method -------------------------------------------------------
Analytical = []         # For storing the analytical eigenvalue
Computed = []           # For storing the computed eigenvalue
RelErr = []             # The relative error
Jacobi_Time = []        # Time used by Jacobi's method 
Armadillo_Time = []     # Time used by Jacobi's method 
n_Buckling = []         # For storing the dimension of matrix used
Iterations = []         # Storing number of iterations to reach the tollerance

#------- Qdot1 ----------------------------------------------------------------
n_Qdot1 = []            # For storing the dimension of matrix used        
Eigval3 = []            # For storing absolute error for first eigenvalue
Eigval7 = []            # For storing absolute error for second eigenvalue
Eigval11 = []           # For storing absolute error for third eigenvalue
Eigval15 = []           # For storing absolute error for fourth eigenvalue
Leading_Digits = 0.001  # Used for cheking when eigenvalue is below tollerance

#------- Qdot2 ----------------------------------------------------------------
wr = []                 # For storing the different omegas.
Gstate_eigval = []      # For storing the ground state eigenvalue     



def Read_file(filename):
    
    """
    Reading a file with specific name and extracting data from it, dependent
    on the method used, given by the filename.
    """
    
    with open(filename, 'r') as infile:
        
        # Data contained in all types of datasets.
        Method = infile.readline().split()[-1]
        Dimension = infile.readline().split()[-1]
        Tolerance = infile.readline().split()[-1]
        
        # Extracting data from Buckling beam txt file
        if filename.startswith("buckling"):
            n_Buckling.append(int(filename[9:-4]))
            Iterations.append(float(infile.readline().split()[-1]))
            Jacobi_Time.append(float(infile.readline().split()[-1]))
            Armadillo_Time.append(float(infile.readline().split()[-1]))
            infile.readline()
            infile.readline()
                  
            for Line in infile:
                Analytical.append(float(Line.split()[0]))
                Computed.append(float(Line.split()[1]))
                RelErr.append(float(Line.split()[2]))

        # Extracting data from Qdot1 txt file
        if filename.startswith("qdot1"):
            n_Qdot1.append(int(filename[6:-4]))
            Rho_max = float(infile.readline().split()[-1])
            infile.readline()
            infile.readline()
            Eigval3.append(float(infile.readline().split()[-1]))
            Eigval7.append(float(infile.readline().split()[-1]))
            Eigval11.append(float(infile.readline().split()[-1]))
            Eigval15.append(float(infile.readline().split()[-1]))

        # Extracting data from Qdot2 txt file
        if filename.startswith("qdot2"):
            Rho_max = float(infile.readline().split()[-1])
            wr.append(float(infile.readline().split()[-1]))
            Gstate_eigval.append(float(infile.readline().split()[-1]))
               
        infile.close() # Closing file after extacting all data needed


# Checking if a directory for storing the plots exists,
# if not, then a folder is made
if not os.path.exists("Figures"):
    os.makedirs("Figures")
else:
    print ("Folder already exists")


# Checking the current directory for files with a specific name
Buckling = [filename for filename in os.listdir(".") if filename.startswith("buckling_") and filename.endswith(".txt")] 
Qdot1 = [filename for filename in os.listdir(".") if filename.startswith("qdot1") and filename.endswith(".txt")]
Qdot2 = [filename for filename in os.listdir(".") if filename.startswith("qdot2") and filename.endswith(".txt")]

# Sorting the different files by values in filename
Buckling.sort(key=lambda n: int(n[9:-4]))
Qdot1.sort(key=lambda n: int(n[6:-4]))
Qdot2 = sorted(Qdot2, key = lambda x: (int(x[18]), float(x[24:-4])))

# Printing out all files to be read
print ("Listing files with matching name (Buckling): ", Buckling)
print ("Listing files with matching name (Qdot1): ", Qdot1)
print ("Listing files with matching name (Qdot2): ", Qdot2)

#Running through the files with desired name
for name in Buckling:
    Read_file("%s" % name)

for name in Qdot1:
    Read_file("%s" % name)
    
for name in Qdot2:
    Read_file("%s" % name)
    

#------------------------------------------------------------------------------
#Plotting for buckling
plt.figure()
plt.plot(n_Buckling, Jacobi_Time,"-", label = "Jacobi method", c="k")
plt.plot(n_Buckling, Armadillo_Time, "-", label = "Armadillo", c="r")
plt.title('CPU time used by Jacobi method vs. Armadillo \n for the \"Buckling beam problem.\" ', fontsize=14)
plt.xlabel('Dimension (n) of matrix', fontsize=13)
plt.ylabel('Time [$s$]', fontsize=13)
plt.tight_layout()
plt.legend(loc=2, prop={"size": 13})
plt.xlim(n_Buckling[0],n_Buckling[-1])


plt.figure()
plt.plot(n_Buckling, asarray(Iterations)/1000, label = "Iterations", c="k")
plt.title("Number of iterations as a function of the matrix dimension.", fontsize=14)
plt.xlabel("Dimension (n) of matrix", fontsize=13)
plt.ylabel(r"Iterations $\times$ $10^3$", fontsize=13)
plt.tight_layout()
plt.legend(loc=2, prop={"size": 13})
plt.xlim(n_Buckling[0],n_Buckling[-1])
plt.ylim(0,180)

#------------------------------------------------------------------------------
# Plotting for qdot1
plt.figure()
plt.plot(n_Qdot1,Eigval3,"-",label="$\lambda_0$ = 3", c="darkred")
plt.plot(n_Qdot1,Eigval7,"-", label="$\lambda_1$ = 7", c="darkgreen")
plt.plot(n_Qdot1,Eigval11,"-",label="$\lambda_2$ = 11", c="mediumvioletred")
plt.plot(n_Qdot1,Eigval15,"-", label="$\lambda_3$ = 15", c="navy")
plt.title("Absolute error for the 4 lowest eigenvalues \n as a function of dimension.", fontsize=14)
plt.xlim(n_Qdot1[0],100)
plt.ylim(0,2.8)
plt.xlabel("Dimension (n) of matrix", fontsize=13)
plt.ylabel("Absolute error", fontsize=13)
plt.legend(loc=1,prop={"size": 13})


plt.figure()
plt.plot(n_Qdot1,asarray(Eigval3)*1000,"-",label="$\lambda_0$ = 3", c="darkred")
plt.plot(n_Qdot1,asarray(Eigval7)*1000,"-", label="$\lambda_1$ = 7", c="darkgreen")
plt.plot(n_Qdot1,asarray(Eigval11)*1000,"-",label="$\lambda_2$ = 11", c="mediumvioletred")
plt.plot(n_Qdot1,asarray(Eigval15)*1000,"-", label="$\lambda_3$ = 15", c="navy")
plt.title("Absolute error for the 4 lowest eigenvalues \n as a function of dimension.", fontsize=14)
plt.xlabel("Dimension (n) of matrix", fontsize=13)
plt.ylabel(r"Absolute error $\times$ $10^{-3}$", fontsize=13)
plt.legend(loc=1,prop={"size": 13})
plt.axhline(Leading_Digits*1000, linestyle="--", c="k", label="Tolerance")
plt.axvline(430,linestyle="--",c="k", label="Dimension for tolerance")
plt.xlim(n_Qdot1[-3],n_Qdot1[-1])
plt.ylim(0,2)

#------------------------------------------------------------------------------
# PLotting for qdot2 
plt.figure()
plt.bar(wr, Gstate_eigval, width=0.3, color="navy")
plt.title(r"Groundstate eigenvalues as a function of $\omega_r$.",fontsize=14)
plt.ylabel("Groundstate eigenvalue", fontsize=13)
plt.xlabel("$\omega_r$",fontsize=13)
plt.xticks((wr[0],wr[1],wr[2],wr[3],wr[4],wr[5],wr[6]),("$\omega_{r1}$","$\omega_{r2}$","$\omega_{r3}$","$\omega_{r4}$","$\omega_{r5}$","$\omega_{r6}$","$\omega_{r7}$"),fontsize=12)
legend_text = patch.Patch(color="navy", label="$\omega_{r1}=0.01$ \n$\omega_{r2}=0.5$ \n$\omega_{r3}=1.0$ \n$\omega_{r4}=2.0$ \n$\omega_{r5}=3.0$ \n$\omega_{r6}=4.0$ \n$\omega_{r7}=5.0$")
plt.legend(handles=[legend_text],fontsize=12)


plt.show()