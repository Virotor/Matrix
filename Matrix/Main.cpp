#include <iostream>
#include <fstream>
#include <string>
#include <math.h>


using namespace std;

int** readMatFromFile(string fileName, int* row, int* col); 
bool writeToFile(int** matrix, int row, int col, string fileName);

int findIndexOfMaxCountOfAlternatingSignNumbers(int** matrix, int row, int col);

void swapMatrixRow(int** matrix, int lastRow, int col, int swapRow);

void printfMatrix(int** matrix, int row, int col);

int main(int argc, char* argv[]) {

    int** mat = nullptr;
    int row, col;
    string fileName;



    if (argc == 1) {
        cout << "Enter file name and path" << endl;
        cin >> fileName;
        mat = readMatFromFile(fileName, &row,&col);
    }
    else {
        fileName = argv[1];
        mat = readMatFromFile(argv[1], &row, &col);
    }

    if (mat == nullptr) {
        cout << "File open with errors"<<endl;
        exit(-1);
    }
    cout << "Matrix 1"<<endl;
    printfMatrix(mat, row, col);
    int indexForSwap = findIndexOfMaxCountOfAlternatingSignNumbers(mat, row, col);
    swapMatrixRow(mat, row - 1, col, indexForSwap);
    cout << "Matrix result"<<endl;
    printfMatrix(mat, row, col);
    writeToFile(mat, row, col, fileName);
    return 0;
}

int** readMatFromFile(string fileName, int* row, int* col) {
    ifstream file;
    file.open(fileName, ios_base::in);
    if (!file.is_open()) {
        return nullptr;
    }
    file >> *row >> *col;
    int** result = new int* [*row];
    for (int i = 0; i < *row; i++) {
        result[i] = new int[*col];
    }
    for (int i = 0; i < *row; i++) {
        for (int j = 0; j < *col; j++) {
            file >> result[i][j];
        }
    }
    file.close();
    return result;
}


bool writeToFile(int** matrix, int row, int col, string fileName) {
    ofstream file(fileName, ios_base::trunc | ios_base::out);
    //file.open();
    if (!file.is_open()) {
        return false;
    }
    file << row << " " << col;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            file << " " << matrix[i][j];
        }
    }
    file.close();
    return true;
}

int findIndexOfMaxCountOfAlternatingSignNumbers(int** matrix, int row, int col) {

    int index = row - 1;
    int count = 0;
    int countPref = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 1; j < col; j++) {
            count +=( (matrix[i][j - 1] < 0 && matrix[i][j] >= 0) || (matrix[i][j - 1] >= 0 && matrix[i][j] < 0)) ? j++, 1 : 0;
        }
        index = count > countPref ? countPref = count , i : index;
        count = 0;
    }

    return index;
}

void swapMatrixRow(int** matrix, int lastRow, int col, int swapRow) {

    if (lastRow == swapRow) {
        return;
    }

    int temp;

    for (int i = 0; i < col; i++) {
        temp = matrix[lastRow][i];
        matrix[lastRow][i] = matrix[swapRow][i];
        matrix[swapRow][i] = temp;
    }
}

void printfMatrix(int** matrix, int row, int col) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cout <<matrix[i][j] << " ";
        }
        cout << endl;
    }
}