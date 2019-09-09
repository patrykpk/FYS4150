
Reproducing the results found in this directory is essential and this file is supposed to make it possible for another person to verify that these results are indeed correct. This file contains a guide on how the programs should be run without any problems and/or errors occuring.

All of the files are supposed to be in the same folder and that includes:
**main.cpp**, **algorithms.cpp**, **algorithms.h** and **Read_File_Project1.py**
depending on where the output file is made.
> **Note:** QtCreator creates seperate build folder after compiling the C++ files where the **Read_File_Project1.py** has to be placed.

# C++ scripts:
Both of the .cpp files have to be compiled together and require Armadillo library.
For our case this has been done by QtCreator itself. 
Running the compiled file requires some input in the command line.

Required command line arguments are the **output filename** without extension 
and a value of **n** given as an int.
**Optional:** Inserting an arbitary third argument will also run LU-Decomposition and a message that it is running will be shown in the terminal. 

**An example of running the compiled file (Terminal):**
kristoffervarslott$ ./Project1 Project_1_Results 10 Y

**QtCreator:**
Command line arguments: Project_1_Results 10 Y

>**Project1** - Compiled file

>**Project_1_Results** - Output filename

>**10** - Value of n

>**Y** - Arbitary argument to run LU-Decomposition


**Result from terminal:**

/////////////////////////////////////////////////////////////

Checking time while performing general and special algorithm:

/////////////////////////////////////////////////////////////


\--------------------------------------------------

Performing general algorithm required: 0.00000400s

Performing special algorithm required: 0.00000200s

\--------------------------------------------------

You have entered a third argument: Running LU

\--------------------------------------------------

Performing LU required: 0.00059000s

\--------------------------------------------------


# Python script:
Python script does not require any arguments and simply running it in the folder that contains the output files does the work. The script searches for all files starting with 
**"Project_1_Results"** in the directory and creates a folder named **"Plots"** where the figures are stored.