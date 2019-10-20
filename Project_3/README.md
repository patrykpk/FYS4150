# Reproducibility Guide :closed_book:


## Project 3: Numerical Integration

Reproducing the results found in this directory is essential and this file is supposed
to make it possible for another person to verify that these results are indeed correct.
This file contains a guide on how the programs should be run without any problems and/or errors occuring.

All of the C++ scripts are contained in the folder called **":file_folder:C++ Scripts"** and the Python scripts are contained in another directory **":file_folder:Python Scripts"**. These directories are found within  **":file_folder:Scripts"**

> :exclamation: **Note:** QtCreator creates seperate build folder after compiling the C++ files.

# C++ Scripts:
### Compiling :link:
Inside the folder **":file_folder:C++ Scripts"** there are three **``main``** files that have to be compiled separetely. One of them being **``main.cpp``**, second one being **``test.cpp``** and the third one being **``MPI_main.cpp``**. Each of them is contained in their seperate directory **":file_folder:Main_Program"**, **":file_folder:Test_Function"** and **":file_folder:Parallelized"** respecitvely with the required source and header files for compiling the scripts.

In order to compile **``main.cpp``**, the other C++ files **``lib.cpp``**, **``MonteCarlo.cpp``**, **``CoordinateSystem.cpp``** and **``GaussianQuadrature.cpp``** have to be included during compilation with their corresponding header files located in the same folder. 

Compiling **``test.cpp``** requires **``lib.cpp``** and the corresponding header file during compilation. In addition the **``catch.hpp``** header file has to be located in the same folder when compiling.

Compiling **``MPI_main.cpp``** is more demanding and requires OpenMPI. C++ files **``lib.cpp``**, **``MonteCarlo.cpp``**, **``CoordinateSystem.cpp``** and **``GaussianQuadrature.cpp``** have to be included in the same folder with their corresponding header files. During this **Project** compiling with OpenMPI in QtCreator didn't work and the compiling was thus done in the Terminal.

**An example of compiling and linking**  
![Project_3_Compile_MPI](https://user-images.githubusercontent.com/54407312/67159388-23797980-f344-11e9-9eb9-fde14aacc733.png)


> :exclamation: **Note:** Errors occured when implementing Parallelization in the main file, so we had to split into another file. That's the reason why Parallelization is done in a seperate file **``MPI_main.cpp``**. When compiling **``MPI_main.cpp``** make sure that you have OpenMPI installed.



### Running :computer:   
***Numerical Integration - (main.cpp)***  
Running the compiled and linked **``main.cpp``** file doesn't require any command line arguments in order to execute. Everything is done through the terminal where you simply choose what you want to do based on the choices you're given.

Assuming that the executable file produced after compiling and linking is **``Project_3``**, then this file could be run the following way.

**An example of running the compiled file (Terminal):**  
![Patrykpk_Github_3](https://user-images.githubusercontent.com/54407312/67162195-1d929100-f362-11e9-8ad3-f802f620c302.png)


**Result from terminal:**  
>Running Qdot1  
>Number of iterations for Jacobi: 17578  
>Eigenvalues: (Computed)  
>2.9991  
>6.9953  
>10.9885  
>14.9787  

Right after running the file you'll be asked to give a number between **1-5**. After choosing what you would like to do other inputs will be required based on the method. Every input in this script regardless of method is a number

Running option **[4]** and **[5]** outputs a **``.txt``** file based on the method used and other input parameters. Running option **[4]** outputs a **``Project_3_GQ.txt``** file while running option **[5]** outputs **``Project_3_MC.txt``**.  

___

***Test-Function - (test.cpp)***  
Running the compiled and linked **``test.cpp``** file is rather simple and doesn't require any specific input. Let's assume  that the executable file produced by compiling and linking is **``test``**. This file can be run in the terminal the following way.

**An example of running the compiled file (Terminal):**  
![Test_Running](https://user-images.githubusercontent.com/54407312/67162027-91339e80-f360-11e9-948c-8c99f60bb6ee.png)

**Result from terminal:**  
> ====================================================  
> All tests passed (9 assertions in 2 test cases)

___

 
# Python scripts:
Necessary layout for the directories is a prerequisite for the Python file to work properly. <img align ="right" width="205" height="171" src="https://user-images.githubusercontent.com/54407312/65968110-f9c6e400-e462-11e9-99b4-a0e219a32f85.png"> The layout is shown to the right, where the **``Read_File_Project_2.py``** file is placed outside all the directories. Folder called **":file_folder:Results"** must contain subfolders  **":file_folder:Buckling_beam"**,   
**":file_folder:Qdot1"** and **":file_folder:Qdot2"** where the results from running the C++ scripts have to be placed. Reasoning behind this is due to **``Read_File_Project_2.py``** file going inside these directories and then searching for files with that desired name based on method. If the mentioned directory layout is present then the only thing left is to actually run the Python script. Running the script will create a new folder called **":file_folder:Figures"** where the figures will be saved:floppy_disk:.

> :exclamation: **Note:** In order to reproduce the figures seen [here](https://github.com/patrykpk/FYS4150/tree/master/Project_2/Figures), all of the content in **":file_folder:Results"** on this Github including the folder itself have to be downloaded or generated by running the C++ scripts. Otherwise the formatting for plotting has to be adjusted according to the files.

