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
<img align = "left" width="460" height="193" src="https://user-images.githubusercontent.com/54407312/69148288-3ebade80-0ad4-11ea-8e64-693c481454ba.gif">

<img align ="left" width="400" height="190" src="https://user-images.githubusercontent.com/54407312/68093720-ead7b500-fe98-11e9-92e7-bdcda8e2c079.gif">        

> :exclamation: **Note:** When compiling these files make sure that the Armadillo library is present, which again requires you having LAPACK and LBLAS. Compiling here was done on Linux, use **``-lomp``** instead of **``-fopenmp``** if you're using an OS X.
