#CMSC313-HW8-CVCPP
This README file is for the matrixSimpleLib.C file.

Author: Max Monson   UMBC CMSC313 M/W 10 - 11:15

Purpose:
This basic C program, "matrixSimpleLib.C", contains functions which compute simple matrix operations.
This can be used and modified in many different ways.
This program can be used to solve simplistic matrix operations and equations.

Build:
I built this file using the gcc compiler. 
My exact gl command to compile this file was: "gcc -std=c99 -m32 -O0 matrixSimpleLib.c" (this can be seen in my submitted screenshot).

Testing:
Each function in this file was tested with a few general and edge cases so that they would be adequate for basic matrix operations.
This program is extremely user dependent. It requires the user to have read the function descriptions and understand the purpose and result of each one.

Each function has comments briefly describing the purpose of the function, lines of code, and variables (if the variable name is not self explanatory).
Many functions will have, and use, variables such as "m, n, and p" to represent the dimensions of the matrix.
The "main" file has the given equation's situation prepared and ready to be executed.

The given functions are as follows:
matrixMultiplication, transposeMatrix, matrixAddition, matrixSubtraction, and matrixScalarMult. 
Along with "dump" which is used for displaying the matrix and debugging.
