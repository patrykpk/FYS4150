# Reproducibility Guide :closed_book: <img align ="right" width="434" height="43" src="https://user-images.githubusercontent.com/54407312/68308291-e97ed600-00ac-11ea-829f-992cf0c9a1eb.gif">

## Project 4: Numerical analysis of 2D Ising model: Phase transition & Critical temperature

Reproducing the results found in this directory is essential and this file is supposed
to make it possible for another person to verify that these results are indeed correct.
This file contains a guide on how the programs should be run without any problems and/or errors occuring.

All of the C++ scripts are contained in the folder called **":file_folder:C++ Scripts"** and the Python scripts are contained in another directory **":file_folder:Python Scripts"**. These directories are found within  **":file_folder:Scripts"**

> :exclamation: **Note:** QtCreator creates seperate build folder after compiling the C++ files.   
> :exclamation: **Another Note:** One of the files used in this project isn't developed by us. That file is **``catch.hpp``**.

# C++ Scripts:
### Compiling :link:
Inside the folder **":file_folder:C++ Scripts"** there are two **``main``** files that have to be compiled separetely. One of them being 
**``main.cpp``** and the other one being **``test.cpp``**. Each of them is contained in their seperate directory **":file_folder:Main_Program"** and **":file_folder:Unit_Test"** with the required source and header files for compiling the scripts.

> :exclamation: **Note:** Many of the files inside these folders will be the same, but they were still put there in order to see what other files that are required during compilation.

In order to compile **``main.cpp``**, the other C++ files **``metropolis.cpp``** and **``inputoutput.cpp``** have to be included during compilation with their corresponding header files loacated in the same folder.

Compiling **``test.cpp``** requires **``metropolis.cpp``** and the corresponding header file in the same folder. In addition the **``catch.hpp``** header file has to be located in the same folder when compiling.

**An example of compiling and linking (Parallelized)**  
<img align = "left" width="598" height="251" src="https://user-images.githubusercontent.com/54407312/69148288-3ebade80-0ad4-11ea-8e64-693c481454ba.gif">  

> :exclamation: **Note:** When compiling these files make sure that the Armadillo library is present, which again requires you having LAPACK and LBLAS. Compiling here was done on Linux, use **``-lomp``** instead of &nbsp; **``-fopenmp``** if you're using an OS X.
<br/>
<br/>
<br/>
  
If you want to use the non-parallized version you'll have to comment out some parts of the code and instead compile with **``g++ -O3 -o NonParallelized main.cpp metropolis.cpp inputoutput.cpp``**.

___

### Running :computer:   
***Numerical analysis - (main.cpp)***  
Running the compiled and linked main.cpp file doesn't require any command line arguments in order to execute. Everything is done through the terminal where you simply choose what you want to do based on the choices you're given.  

Assuming that the executable file produced after compiling and linking is **``Parallelized``**, then this file could be run the following way.  

**An example of running the compiled file (Terminal):** 
<img align = "left" width="598" height="251" src="https://user-images.githubusercontent.com/54407312/69172668-8f473180-0afe-11ea-8230-a1477ba4d6e7.gif">  
<br/><br/><br/><br/><br/><br/><br/><br/><br/><br/>

Every choice gives an output in a form of a **``.txt``** file based on the method used.  

___

***Unit Tests - (test.cpp)***  
Running the compiled and linked **``test.cpp``** file is rather simple and doesn't require any specific input. Let's assume  that the executable file produced by compiling and linking is **``test``**. This file can be run in the terminal the following way.

**An example of running the compiled file (Terminal):**  
![Test_Running](https://user-images.githubusercontent.com/54407312/67162027-91339e80-f360-11e9-948c-8c99f60bb6ee.png)

**Result from terminal:**  
> ====================================================  
> All tests passed (9 assertions in 2 test cases)

___

# Python scripts:  
After acquiring the results from running C++ scripts the **``.txt``**  files must placed in the same directory as the Python scripts. There are in total 5 Python scripts generating figures found in this repository. What Python file to run after generating the data is explained below:  
**:page_facing_up:Temperature.py** uses the output by running method **[2]** in the C++ script.<br/> **:page_facing_up:Read_Probability_Energy.py** uses the output by running method **[3]** in the C++ script.<br/>
**:page_facing_up:Lattice_Visualization.py** uses the output by running method **[4]** in the C++ script.<br/>
**:page_facing_up:Accepted_Flips.py** uses the output by running method **[5]** in the C++ script.<br/>
**:page_facing_up:MonteCarloCycles.py** uses the output by running method **[6]** in the C++ script.<br/>

> :exclamation: **Note:** In order to reproduce the figures seen [here](https://github.com/patrykpk/FYS4150/tree/master/Project_4/Figures), the content in **":file_folder:Results"** on this Github have to be downloaded or generated by running the C++ scripts.
 
# Listing of files: 
### Developed by us:
* **``main.cpp``**
* **``test.cpp``**
* **``metropolis.cpp``**
* **``inputoutput.cpp``**
* **``Accepted_Flips.py``**
* **``Lattice_Visualization.py``**
* **``MonteCarloCycles.py``**
* **``Read_Probability_Eneregy.py``**
* **``Temperature.py``**

### Not developed by us:
* **``catch.hpp``**
