#include <iostream>
using namespace std;

class Matrix{
    public:
    Matrix();
    Matrix(int row, int col);
    ~Matrix();
    void insert(int element, int wantedRow, int wantedCol);
    void addMatrix(Matrix &otherMatrix);
    void subtractMatrix(Matrix &otherMatrix);
    void multiplyMatrix(Matrix &otherMatrix);
    void scalarMultiplication(int scalar);
    void transposeMatrix();
    int getRows();
    int getCols();
    int** getMatrix();
    void dump();
    void print();

    //DATA MEMBERS 
    private:
    int rows;
    int cols;
    int** m_matrix;

};    

    //CONSTRUCTORS AND DESTRUCTORS
    /*Matrix:: Matrix(){
        int rows = 0;
        int cols = 0;
        int m_matrix[0][0]; 
    } */

    Matrix:: Matrix(int row, int col){
        //check that row & col > 0
        rows = row;
        cols = col;
        m_matrix = new int*[rows];
        for(int i = 0; i < rows; i++) {
            m_matrix[i] = new int[cols];
        }
    }

    Matrix:: ~Matrix(){
        if(rows != 0 && cols != 0){ 
            //go through each row and delete all the elements
            for(int i = 0; i < rows; i++){
                delete[] m_matrix[i];
            }
        }
        if(m_matrix != nullptr){
            delete[] m_matrix;
        }
        rows = 0;
        cols = 0;
    }



    //MEMBER FUNCTIONS
    void Matrix:: insert(int element, int wantedRow, int wantedCol){
        //inserts the element at the passed in row and column as long as it is within bounds (and not already full)
        if(wantedRow >= 0 && (wantedRow) < rows && (wantedCol) >= 0 && wantedCol < cols){ //within the bounds
            m_matrix[wantedRow][wantedCol] = element;
        }
    }

    void Matrix:: addMatrix(Matrix &otherMatrix) {
        //both matricies must have the same dimensions to be added
        if(rows == otherMatrix.getRows() && cols == otherMatrix.getCols()){
            for(int i = 0; i < rows; i++){ //go through each row and add all the elements
                for(int j = 0; j < cols; j++){
                    m_matrix[i][j] = m_matrix[i][j] + otherMatrix.m_matrix[i][j];
                } 
            }
        }
        else if(rows != otherMatrix.getRows() && cols != otherMatrix.getCols()){
            cout << "The matrices don't have the same dimensions, they cannot be added" << endl;
        }
    }

    void Matrix:: subtractMatrix(Matrix &otherMatrix){
        if(rows == otherMatrix.rows && cols == otherMatrix.cols){
            for(int i = 0; i < rows; i++){ //go through each row and add all the elements
                for(int j = 0; j < cols; j++){
                    m_matrix[i][j] = m_matrix[i][j] - otherMatrix.m_matrix[i][j];
                } 
            }
        }
    }

    void Matrix:: multiplyMatrix(Matrix &otherMatrix){
        if(m_matrix != nullptr && otherMatrix.m_matrix != nullptr){ //both objects have matrices
            if(cols != otherMatrix.rows){
                cout << "Can't multiply these matrices because the dimensions don't match (columns to rows)" << endl;   
            }

            //since the result of this operation will be a matrix with (most likely) different dimensions (m x p)
            //we build a new matrix/2D array to replace it
            int** result = new int*[rows];
            for(int i = 0; i < rows; i++){ //result has this matrix's number of rows: 'm'
                result[i] = new int[otherMatrix.cols];
                //cout << "Row #" << i << endl;
                for(int j = 0; j < otherMatrix.cols; j++){ //result has otherMatrix's number of columns: 'p'
                    result[i][j] = 0;
                    //cout << "Column #" << j << endl;
                    for(int k = 0; k < cols; k++){ //dot product: multiply each row of this matrix by all columns of otherMatrix
                        result[i][j] += m_matrix[i][k] * otherMatrix.m_matrix[k][j];
                        //cout << m_matrix[i][k] << " * " << otherMatrix.m_matrix[k][j] << " = " << result[i][j] << endl;
                    }
                }
            }
            for(int i = 0; i < rows; i++){ //delete the old matrix to prevent memory leaks
                delete[] m_matrix[i];
            }
            delete[] m_matrix;

            //now that the old matrix has been deleted, make m_matrix the result of the matrix multiplication
            m_matrix = result;
            cols = otherMatrix.cols; //update the number of columns (rows don't change, so don't need to update)
        } 
            //result will be a m x p matrix
    }

    void Matrix:: scalarMultiplication(int scalar){
        for(int i = 0; i < rows; i++){ //go through each row and multiply all the elements by the scalar
            for(int j = 0; j < cols; j++){
                m_matrix[i][j] = scalar * m_matrix[i][j];
            } 
        }
    }

    void Matrix:: transposeMatrix(){
        int** transposeMatrix = new int*[rows]; //create the transpose matrix
        for(int k = 0; k < cols; k++){
            transposeMatrix[k] = new int[cols];
        }
        for(int i = 0; i < cols; i++){ //go through each row and turn the rows into columns for the transpose
            for(int j = 0; j < rows; j++){
                transposeMatrix[i][j] = m_matrix[j][i];
            } 
        }
        for(int i = 0; i < rows; i++){ //delete the old matrix
            delete[] m_matrix[i];
        }
        delete[] m_matrix;

        //make the transpose Matrix the new m_matrix
        m_matrix = transposeMatrix;
        //swap the rows and columns
        int temp = cols;
        cols = rows;
        rows = temp;
    }

    int** Matrix:: getMatrix(){
        return m_matrix;
    }
    int Matrix:: getRows(){
        return rows;
    }
    int Matrix:: getCols(){
        return cols;
    }

    void Matrix:: dump(){ //used for debugging
        if(rows == 0 || cols == 0){
            cout << "The matrix is empty" << endl;
        }
        else{
            for(int i = 0; i < rows; i ++){
                for(int j = 0; j < cols; j++){
                    cout << "Element row# " << i << " & col# " << j << " is " << m_matrix[i][j] << endl;
                }
            }
        }
    }

    void Matrix:: print(){
        if(rows == 0 || cols == 0){
            cout << "The matrix is empty" << endl;
        }
        else{
            for(int i = 0; i < rows; i ++){
                cout << "|";
                for(int j = 0; j < cols; j++){
                    cout << m_matrix[i][j] << " ";
                }
                cout << "|" << endl;
            }
        }
    }



int main(){ //rows and columns start at index 0

    Matrix A(2,2);
    A.insert(6, 0, 0);
    A.insert(4, 0, 1);
    A.insert(8, 1, 0);
    A.insert(3, 1, 1);
    cout << "Matrix A: " << endl;
    A.print();
    
    Matrix B(2, 3);
    B.insert(1, 0, 0);
    B.insert(2, 0, 1);
    B.insert(3, 0, 2);
    B.insert(4, 1, 0);
    B.insert(5, 1, 1);
    B.insert(6, 1, 2);
    cout << "Matrix B: " << endl;
    B.print();

    
    Matrix C(2, 3);
    C.insert(2, 0, 0);
    C.insert(4, 0, 1);
    C.insert(6, 0, 2);
    C.insert(1, 1, 0);
    C.insert(3, 1, 1);
    C.insert(5, 1, 2);
    cout << "Matrix C: " << endl;
    C.print(); 

    cout << "Transpose C: " << endl;
    C.transposeMatrix();
    C.print();

    cout << endl;
    cout << "Equation: A + (3 * B) x C^T" << endl;
    
    cout << "(3 * B)" << endl;
    cout << "Scale B by 3: (3*B): " << endl;
    B.scalarMultiplication(3);
    B.print();

    cout << "Matrix multiplication (3B x C^T)" << endl;
    B.multiplyMatrix(C);
    B.print();

    cout << "Add A and (3B x C^T): " << endl;;
    A.addMatrix(B);
    A.print();
    cout << endl;
    cout << "Result: " << endl;
    A.print();

    return 0;
}