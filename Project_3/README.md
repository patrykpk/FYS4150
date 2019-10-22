# Reproducibility Guide :closed_book:


## Project 3: Ground state correlation energy of the helium atom using different numerical methods

Reproducing the results found in this directory is essential and this file is supposed
to make it possible for another person to verify that these results are indeed correct.
This file contains a guide on how the programs should be run without any problems and/or errors occuring.

All of the C++ scripts are contained in the folder called **":file_folder:C++ Scripts"** and the Python scripts are contained in another directory **":file_folder:Python Scripts"**. These directories are found within  **":file_folder:Scripts"**

> :exclamation: **Note:** QtCreator creates seperate build folder after compiling the C++ files.  
> :exclamation: **Another Note:** Two of the files used in this project haven't been developed by us. Those files are **``catch.hpp``** and **``lib.cpp``**.

# C++ Scripts:
### Compiling :link:
Inside the folder **":file_folder:C++ Scripts"** there are three **``main``** files that have to be compiled separetely. One of them being **``main.cpp``**, second one being **``test.cpp``** and the third one being **``MPI_main.cpp``**. Each of them is contained in their seperate directory **":file_folder:Main_Program"**, **":file_folder:Unit_Test"** and **":file_folder:Parallelization"** respecitvely with the required source and header files for compiling the scripts.  

> :exclamation: **Note:** Many of the files inside these folders will be the same, but they were still put there in order to see what other files that are required during compilation.

In order to compile **``main.cpp``**, the other C++ files **``lib.cpp``**, **``MonteCarlo.cpp``**, **``CoordinateSystem.cpp``** and **``GaussianQuadrature.cpp``** have to be included during compilation with their corresponding header files located in the same folder. 

Compiling **``test.cpp``** requires **``lib.cpp``** and the corresponding header file during compilation. In addition the **``catch.hpp``** header file has to be located in the same folder when compiling.

Compiling **``MPI_main.cpp``** is more demanding and requires MPI. C++ files **``lib.cpp``**, **``MonteCarlo.cpp``**, **``CoordinateSystem.cpp``** and **``GaussianQuadrature.cpp``** have to be included in the same folder with their corresponding header files. During this **Project** compiling with OpenMPI in QtCreator didn't work and the compiling was thus done in the Terminal.

**An example of compiling and linking**  
![Patrykpk_Github_MPI_Compile](https://user-images.githubusercontent.com/54407312/67162693-bdeab480-f366-11e9-872d-bc152c512806.png)  
![Patrykpk_Github_MPI_Compile_](https://user-images.githubusercontent.com/54407312/67190153-bde2c700-f3ef-11e9-900f-29457eca9bcd.png)



> :exclamation: **Note:** Errors occured when implementing Parallelization in the main file, so we had to split into another file. That's the reason why Parallelization is done in a seperate file **``MPI_main.cpp``**. When compiling **``MPI_main.cpp``** make sure that you have OpenMPI installed.

___

### Running :computer:   
***Numerical Integration - (main.cpp)***  
Running the compiled and linked **``main.cpp``** file doesn't require any command line arguments in order to execute. Everything is done through the terminal where you simply choose what you want to do based on the choices you're given.

Assuming that the executable file produced after compiling and linking is **``Project_3``**, then this file could be run the following way.

**An example of running the compiled file (Terminal):**  
![Patrykpk_Github_3](https://user-images.githubusercontent.com/54407312/67162195-1d929100-f362-11e9-8ad3-f802f620c302.png)

**Result from terminal:**  
>What would you like to do?  
>Values listed below give output for one value of 'n' in the terminal  
>[1] Legendre, [2] Laguerre, [3] MonteCarlo  
>
>Remaining options write the output to file up to the given value of 'n' for  
>[4] Legendre & Laguerre or [5] MonteCarlo  
>Method:  

Right after running the file you'll be asked to give a number between **1-5**. After choosing what you would like to do other inputs will be required based on the method. Every input in this script regardless of method is a number.

Running option **[4]** and **[5]** outputs a **``.txt``** file based on the method used and other input parameters. Running option **[4]** outputs a **``Project_3_GQ.txt``** file while running option **[5]** outputs **``Project_3_MC.txt``**.  

___

***Unit Tests - (test.cpp)***  
Running the compiled and linked **``test.cpp``** file is rather simple and doesn't require any specific input. Let's assume  that the executable file produced by compiling and linking is **``test``**. This file can be run in the terminal the following way.

**An example of running the compiled file (Terminal):**  
![Test_Running](https://user-images.githubusercontent.com/54407312/67162027-91339e80-f360-11e9-948c-8c99f60bb6ee.png)

**Result from terminal:**  
> ====================================================  
> All tests passed (9 assertions in 2 test cases)

___

***Parallelized Monte Carlo - (MPI_main.cpp)***  
Running the compiled and linked **``MPI_main.cpp``** is different from the others. As we didn't get QtCreator to work with Open MPI the following instruction is on running the script from terminal. In order to run the compiled script there is a special way to do so with MPI, where you have to specify the amount of processes to be run simultaneously. In addition to that **``MPI_main.cpp``** requires the number of sampling points as an input in the command line.
  
**An example of running the compiled file (Terminal):**  
![Patrykpk_Github_MPI_Run](https://user-images.githubusercontent.com/54407312/67162704-e70b4500-f366-11e9-9527-6877b6bf5da5.png)

Where ./MPI is the compiled and linked file that was mentioned in the section **"Compiling"** and 1000000 is the amount of sampling points. The remaining options seen above are specific to Open MPI.

**Result from terminal:**  
>\-----------------------------------------------------------------------------   
>Parallelization of Monte Carlo Importance Sampling   
>Integral Importance sampling: 0.192613  
>Time Monte Carlo Importance Sampling: 0.094643 s  
>\-----------------------------------------------------------------------------  
>Parallelization of Monte Carlo Brute Force  
>Integral Brute Force: 0.178396   
>Time Monte Carlo Brute Force: 0.085934 s  

# Python scripts:
<img align ="right" width="262" height="301" src="https://user-images.githubusercontent.com/54407312/67201749-3bfe9800-f407-11e9-880a-bf3b61dfceb0.png"> Running Python scripts can be done in two ways. After acquiring the results from running C++ scripts the **``.txt``**  files must be either placed in the same directory as the Python scripts or like visualised by the layout to the right. This is not needed for **:page_facing_up:Project_3_3D.py** since it doesn't read any **``.txt``** files. A folder **":file_folder:Figures"** will be created after running the scripts and the location of it depends on where the **``.txt``** files were placed when the Python scripts were ran. Figures from running the scripts will be saved:floppy_disk: in that folder.

> :exclamation: **Note:** In order to reproduce the figures seen [here](https://github.com/patrykpk/FYS4150/tree/master/Project_3/Figures), the content in **":file_folder:Results"** on this Github have to be downloaded or generated by running the C++ scripts.

# Listing of files: 
### Developed by us:
* **``CooordinateSystem.cpp``**
* **``GaussianQuadrature.cpp``**
* **``MonteCarlo.cpp``**
* **``main.cpp``**
* **``MPI_main.cpp``**
* **``test.cpp``**
* **``Project_3_3D.py``**
* **``Project_3_GQ.py``**
* **``Project_3_MC.py``**

### Not developed by us:
* **``lib.cpp``**
* **``catch.hpp``**
