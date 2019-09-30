# Reproducibility Guide :closed_book:


## Project 2: Jacobi's method for solving eigenvalue problems

Reproducing the results found in this directory is essential and this file is supposed
to make it possible for another person to verify that these results are indeed correct.
This file contains a guide on how the programs should be run without any problems and/or errors occuring.

> **Note:** QtCreator creates seperate build folder after compiling the C++ files.
```python
import os

if not os.path.exists("My_Folder"):
	os.makedirs("My_Folder")
else:
	print ("Folder already exists")
```
