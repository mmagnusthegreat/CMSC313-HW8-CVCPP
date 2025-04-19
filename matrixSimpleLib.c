#include <stdio.h>
#include <stdlib.h>

void matrixMultiplication(int m, int n, int p, int** mxn_matrix, int** nxp_matrix, int** result){
    // m x n multiplied by n x p = m x p

    for(int i = 0; i < m; i++){ //itarating though rows
        for(int j = 0; j < p; j++){ //iterating through columns
            result[i][j] = 0;  //initialization of an elemenent
            for(int k = 0; k < n; k++){
                result[i][j] += mxn_matrix[i][k] * nxp_matrix[k][j]; //sum of products
            }
        }
    }
}

void transposeMatrix(int rows, int cols, int** normalMat, int** transposeMat){ //creates a transpose matrix of mat1 
    //both matrices must be initialized in advance - normalMat rows x cols - transposeMat cols x rows
    //(rows and cols are the bounds of the normmatrix, not the bounds of the transposeMatrix)
    //if you put in the improper/invalid bounds the function will not work
    for(int i = 0; i < cols; i++){ //go through each row and turn the rows into columns for the transpose
        for(int j = 0; j < rows; j++){
            transposeMat[i][j] = normalMat[j][i];
        } 
    }       
}

void matrixAddition(int rows, int cols, int** mat1, int** mat2){ //the matrices must have the same dimensions to be added together
    for(int i = 0; i < rows; i ++){
        for(int j = 0; j < cols; j++){
            mat1[i][j] += mat2[i][j];   
        }
    }
}

void matrixSubtraction(int rows, int cols, int** mat1, int** mat2){ //the matrices must have the same dimensions to be added together
    for(int i = 0; i < rows; i ++){
        for(int j = 0; j < cols; j++){
            mat1[i][j] -= mat2[i][j];   
        }
    }
}

void matrixScalarMult(int rows, int cols, int** matrix, int scalar){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            matrix[i][j] = matrix[i][j] * scalar;
        }
    }
}

void dump(int rows, int cols, int** matrix){ //used for debugging
    if(matrix == NULL){
        printf("Matrix is null\n");
        return;
    }    
    else{
        for(int i = 0; i < rows; i ++){
            printf("|"); 
            for(int j = 0; j < cols; j++){
                printf("%d ", matrix[i][j]);
            }
            printf("|\n"); 
        }
    }
    //printf("\n");
}


int main(){ //gcc -std=c99 -m32 -O0 myprogram.c -o simpleMatrix
    int m = 2, n = 3, p = 2;
    
    //mxm matrix: A 2x2
    int** A = (int**)malloc(m * sizeof(int*));
    for(int i = 0; i < m; i++){
        A[i] = (int*)malloc(m * sizeof(int));
    }
    //fill A with the appropiate data
    A[0][0] = 6;
    A[0][1] = 4;
    A[1][0] = 8;
    A[1][1] = 3;

    printf("Matrix A: \n");
    dump(m, m, A);

    //nxp matrix: B 2x3
    int** B = (int**)malloc(m * sizeof(int*));
    for(int i = 0; i < n; i++){
        B[i] = (int*)malloc(n * sizeof(int));
    }
    //fill B with the appropiate data
    B[0][0] = 1;
    B[0][1] = 2;
    B[0][2] = 3;
    B[1][0] = 4;
    B[1][1] = 5;
    B[1][2] = 6;

    //print the matrix
    printf("Matrix B: \n");
    dump(m, n, B);


    //mxn matrix: C 2x3
    int** C = (int**)malloc(m * sizeof(int*));
    for(int i = 0; i < m; i++){
        C[i] = (int*)malloc(n * sizeof(int));
    }
    //fill C with the appropiate data
    C[0][0] = 2;
    C[0][1] = 4;
    C[0][2] = 6;
    C[1][0] = 1;
    C[1][1] = 3;
    C[1][2] = 5;

    //print the matrix
    printf("Matrix C: \n");
    dump(m, n, C);

    //nxp matrix: Ctranspose 3x2
    int** Ctranspose = (int**)malloc(n * sizeof(int*));
    for(int i = 0; i < n; i++){
        Ctranspose[i] = (int*)malloc(m * sizeof(int));
    }
    transposeMatrix(m, n, C, Ctranspose);

    //mxp matrix: result
    int** result = (int**)malloc(m * sizeof(int*));
    for(int i = 0; i < m; i++){
        result[i] = (int*)malloc(p * sizeof(int));
    }
    



    //Equation
    printf("\n EQUATION: A + (3 * B) x C^T = ...\n");
    printf("\n");

    printf("(3 * B) \n");
    printf(" ||| \n");
    matrixScalarMult(m, n, B, 3); 
    dump(m, n, B);

    printf("C^T\n");
    printf(" ||| \n");
    dump(n, m, Ctranspose);

    printf("(3B) * C^T\n");
    printf(" ||| \n");
    //multiply B (3B now that it has been scaled) with CTranspose to create result
    matrixMultiplication(m, n, p, B, Ctranspose, result);
    dump(m, p, result);
    printf("This matrix is called 'result' \n");

    printf("A + result = \n");
    //add A and result
    matrixAddition(m, p, A, result);
    dump(m, p, A);

    printf("\n");
    printf("Final result: \n");
    dump(m, p, A);


    //free up the memory
    //iterate through each matrix and delete the allocated memory
    for(int i = 0; i < m; i++){ 
        free(A[i]); 
    }
    for(int j = 0; j < n; j++){ 
        free(B[j]); 
    }
    for(int k = 0; k < n; k++){
        free(C[k]);
    }
    for(int l = 0; l < n; l++){
        free(Ctranspose[l]);
    }
    for(int z =0; z < m; z++){
        free(result[z]);
    }
    free(A); 
    free(B); 
    free(C);
    free(Ctranspose);
    free(result);
    
    return 0;
}