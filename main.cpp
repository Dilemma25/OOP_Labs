#include<iostream>
#include<iomanip>
#include<stdexcept>
#include<limits>
#include<cmath>
#include<string>
#include<cstdlib>

using namespace std;


int toInt(string value) {
    int intValue = 0;
    
    for (int i = 0;  i < value.length(); ++i) {
        if (value[i] >= '0' && value[i] <= '9') {
            intValue += (value[i] - '0') * pow(10, value.length() - i - 1);
        } else {
            throw invalid_argument("Программа обрабатывает только целые числа!!");
        }
    }

    return intValue;
}

void printMatrix(int** matrix, int rows, int cols) {
    if (!matrix) {
        cout << "Матрица пустая" << '\n'; 
        return;
    }
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << setw(5) << matrix[i][j];
        }
        cout << '\n';
    }
}

void createMatrix(int**& matrix,int rows,int cols) {
    matrix = new int*[rows];
    
    for(int i = 0; i < rows; ++i){
        matrix[i] = new int[cols];
    }

    for(int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = rand() % 4;
        } 
    }
}

void inputErrorHandler(int& rows, int& cols) {
    
    string rowsInput, colsInput;
    int rowsTest, colsTest;

    try {
        cin >> rowsInput >> colsInput;

        rowsTest = toInt(rowsInput);
        colsTest = toInt(colsInput);

    } catch(invalid_argument e) {
        cerr << "\033[31m" << e.what() << "\033[0m" << '\n' << '\n';
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if (rowsTest > 0 && colsTest > 0) {
        rows = rowsTest;
        cols = colsTest;
    } else {
        cout << "\033[31m" << "Количество строк или столбцов не задано, матрица не может быть создана" << "\033[0m" <<'\n';
    }
}

int sumCol(int** matrix, int column, int rows, int exception){
    int sum = 0;
    bool chekException = false;
    for(int i = 0; i < rows; i++){
        
        if (matrix[i][column] == exception && !chekException) {
            chekException = true;
            continue;
        }

        sum += matrix[i][column];
    }

    return sum;
}

int* findMaxElemInCol(int** matrix, int column, int rows) {
    
    int max = 0;
    int position = 0;
    int* maxAndColPosition = new int[2];
    for(int i = 0; i < rows; i++){
       if (matrix[i][column] >= max) {
        max = matrix[i][column];
        position = i;
       }
    }
    maxAndColPosition[0] = max;
    maxAndColPosition[1] = position;
    return maxAndColPosition;

}

void findSpecialElements(int**& matrix,int rows,int cols){
    int sumInCol = 0;
    int* maxAndColPosition = new int[2];
    for(int i = 0; i < cols; ++i) {
        maxAndColPosition = findMaxElemInCol(matrix, i, rows);
        sumInCol = sumCol(matrix, i, rows, maxAndColPosition[0]);
        
        if (maxAndColPosition[0] > sumInCol) {
            cout << "Особый элемент: " << maxAndColPosition[0] << " координаты: " << i + 1 << ' ' << maxAndColPosition[1] + 1<< '\n';
        }

        delete[] maxAndColPosition;
    }
}

void deleteMatrix(int**& matrix, int rows) {
    for(int i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }

    delete[] matrix;
    matrix = nullptr;
}


int main() {
    srand(time(NULL));

    int rows = 0,cols = 0;
    int** matrix;
    int** specialElements;

    cout << "Введите количество строк, затем столбцов матрицы через пробел" <<'\n';
    inputErrorHandler(rows, cols);
    createMatrix(matrix, rows, cols);

    printMatrix(matrix, rows, cols);
    
    findSpecialElements(matrix, rows, cols);

    deleteMatrix(matrix, rows);

    printMatrix(matrix, rows, cols);
    
    return 0;
}
