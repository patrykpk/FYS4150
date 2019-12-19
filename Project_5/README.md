# Reproducibility Guide :closed_book: <img align ="right" width="434" height="43" src="https://user-images.githubusercontent.com/54407312/68308291-e97ed600-00ac-11ea-829f-992cf0c9a1eb.gif">

## Project 5: Numerical study of the diffusion/heat equation in one and two dimensions

Reproducing the results found in this directory is essential and this file is supposed
to make it possible for another person to verify that these results are indeed correct.
This file contains a guide on how the programs should be run without any problems and/or errors occuring.

All of the C++ scripts are contained in the folder called **":file_folder:C++ Scripts"** and the Python scripts are contained in another directory **":file_folder:Python Scripts"**. These directories are found within  **":file_folder:Scripts"**

> :exclamation: **Note:** QtCreator creates seperate build folder after compiling the C++ files. 

# C++ Scripts:
### Compiling :link:

Inside the folder **":file_folder:C++ Scripts"** there are two **``main``** files that have to be compiled separetely. One of them being 
**``main.cpp``** and the other one being **``test.cpp``**. Each of them is contained in their seperate directory 
**":file_folder:Main_Program"** and **":file_folder:Unit_Test"** with the required source and header files for compiling the scripts.

> :exclamation: **Note:** Many of the files inside these folders will be the same with perhaps some minor changes in returning the
values, but they were still put there in order to see what other files that are required during compilation.

In order to compile **``main.cpp``**, the other C++ files **``Algorithms1D.cpp``**, **``Algorithms2D.cpp``** and **``Solvers.cpp``** have
to be included during compilation with their corresponding header files loacated in the same folder.

Compiling **``test.cpp``** requires **``Algorithms1D.cpp``**, **``Algorithms2D.cpp``** and **``Solvers.cpp``** with their corresponding 
header file in the same folder. In addition the **``catch.hpp``** header file has to be located in the same folder when compiling.

**An example of compiling and linking**

> :exclamation: **Note:** When compiling these files make sure that the Armadillo library is present, which again requires you 
having LAPACK and LBLAS. Compiling here was done on Linux, use <br/> **``-lomp``** instead of **``-fopenmp``** if you're using an OS X.

___

### Running :computer:   
***Numerical analysis - (main.cpp)***  
Running the compiled and linked **``main.cpp``** file doesn't require any command line arguments in order to execute. Everything is
done through the terminal where you simply choose what you want to do based on the choices you're given.  

Assuming that the executable file produced after compiling and linking is **``Project_5``**, then this file could be run the
following way.  

**An example of running the compiled file (Terminal):** 

You will be given the choice of either writing the output to a file in a form of a **``.txt``** or simply writing the 
output to the terminal.

___

***Unit Tests - (test.cpp)***  
Running the compiled and linked **``test.cpp``** file is rather simple and doesn't require any specific input except for some choices
in the terminal. Let's assume that the executable file produced by compiling and linking is **``test``**. This file can be run in the 
terminal the following way.

**An example of running the compiled file (Terminal):**  
![Test_Running](https://user-images.githubusercontent.com/54407312/67162027-91339e80-f360-11e9-948c-8c99f60bb6ee.png)

**Result from terminal:**  
> Choose step length for time Δt  
> 0.05  
> Choose how long you want to run the calculation (s):  
> 2  
> \----------------------------------------------------  
> Information for the calculation:  
> Amount of points N = 10  
> Step-Length Δx = 0.1  
> Step length Δt = 0.05  
> Total time T = 2  
> Number of time iterations n = 41  
> Alpha α = 5  
> \---------------------------------------------------  
> \====================================================  
> All tests passed (19 assertions in 2 test cases)

___

# Python scripts:  
After acquiring the results from running C++ scripts the **``.txt``**  files must placed in the same directory as the Python scripts. 
**:page_facing_up:1D_Diffusion.py** uses the output found in **/Results/1D - Diffusion/** in this Github repository.<br/> 
**:page_facing_up:Read_Diffusion_2D.py** uses the output found in **/Results/2D - Diffusion/** in this Github repository.<br/> 
The latter one requires some changes within the file based on the desired output, this is explained within the file itself.

# Listing of files: 
### Developed by us:
* **``main.cpp``**
* **``test.cpp``**
* **``Algorithms1D.cpp``**
* **``Algorithms2D.cpp``**
* **``Solvers.cpp``**
* **``1D_Diffusion.py``**
* **``Read_Diffusion_2D.py``**

### Not developed by us:
* **``catch.hpp``**
