# Reproducibility Guide :closed_book:


## Project 2: Jacobi's method for solving eigenvalue problems

Reproducing the results found in this directory is essential and this file is supposed
to make it possible for another person to verify that these results are indeed correct.
This file contains a guide on how the programs should be run without any problems and/or errors occuring.

All of the C++ scripts are contained in the folder called **":file_folder:C++ Scripts"** and the Python file **``Read_File_Project_2.py``** is found outside of this folder. 

> :exclamation: **Note:** QtCreator creates seperate build folder after compiling the C++ files.

# C++ Scripts:
### Compiling :link:
Inside the folder **":file_folder:C++ Scripts"** there are two **``main``** files that have to be compiled separetely. One of them being **``main.cpp``** and the other one being **``test.cpp``**.

In order to compile **``main.cpp``**, the other C++ files **``Jacobi.cpp``**, **``initializematrix.cpp``** and **``functions.cpp``** have to be included during compilation with their corresponding header files located in the same folder. 

Compiling **``test.cpp``** requires the same C++ files as **``main.cpp``** during compilation. That means that **``Jacobi.cpp``**, **``initializematrix.cpp``** and **``functions.cpp``** have to be included when compiling **``test.cpp``**. In addition the **``catch.hpp``** header file has to be located in the same folder when compiling.
> :exclamation: **Note:** When compiling these files make sure that the Armadillo library is present, which again requires you having LAPACK and LBLAS. 

### Running :computer:
***Test-Function - (test.cpp)***  
Running the compiled and linked **``test.cpp``** file is rather simple and doesn't require any specific input. Let's assume  that the executable file produced by compiling and linking is **``test.exe``**. This file can be run in the terminal the following way.

**An example of running the compiled file (Terminal):**  
![Patrykpk_Github](https://user-images.githubusercontent.com/54407312/65923538-9c428100-e3e9-11e9-9922-a30f84467974.png)

**Result from terminal:**  
>Running Buckling  
>\====================================================  
>All tests passed (51 assertions in 2 test cases)
___
***Solving eigenvalue problem - (main.cpp)***  
Running the compiled and linked **``main.cpp``** file requires some command line arguments in order to execute. There are in total 4 command line arguments that can be inserted, with 3 of them being mandatory for the first two methods and 4 for the last method.

First command line argument is the dimension of the matrix that we want to work with and must be given as an integer. Second command line argument is <img src="https://latex.codecogs.com/gif.latex?\rho_{max}"/>. Third command line argument is the method that will be used, for this input only three alternatives are accepted. The input here has to be one of the following **[ *buckling, qdot1, qdot2* ]** written the exact way as shown in the brackets. Fourth and last input is only required if **qdot2** is used and represents the frequency <img src="https://latex.codecogs.com/gif.latex?\omega_{r}"/>. Assuming that the executable file produced after compiling and linking is **``Project_2.exe``**, then this file could be run the following way.


**An example of running the compiled file (Terminal):**  
![Patrykpk_Github_2](https://user-images.githubusercontent.com/54407312/65923602-cf851000-e3e9-11e9-8857-e4098b02beec.png)


**QtCreator:**  
**Command line arguments:** 100 5.5 qdot1  

**Input:**
> **Project_2.exe** - Executable file from compiling and linking  
> **100** - Dimension of the matrix (n)  
> **5.5** - <img src="https://latex.codecogs.com/gif.latex?\rho_{max}"/>  
> **qdot1** - Method

**Result from terminal:**  
>Running Qdot1  
>Number of iterations for Jacobi: 17578  
>Eigenvalues: (Computed)  
>2.9991  
>6.9953  
>10.9885  
>14.9787  


Running this file also outputs a **``.txt``** file based on the method used and other input parameters. This file contains a lot more information compared to the output from terminal and also higher precision for the values evaluated. 
 
# Python script:
Running the Python script requires a specific directory layout 
Saving :floppy_disk:  
Necessary layout for the directories is a prerequisite for the Python file to work properly.

:file_folder:Project_2   
├:file_folder:C++ Scripts   
├:file_folder:Figures   
├:file_folder:Results   
**│└**:file_folder:Buckling_beam   
**│└**:file_folder:Qdot1   
**│└**:file_folder:Qdot2   
├:page_facing_up:Read_File_Project_2.py   

```python
import os

if not os.path.exists("My_Folder"):
	os.makedirs("My_Folder")
else:
	print ("Folder already exists")
```
