#include <iostream>
using namespace std;

int findData (int matrixRow[], int matrixColumn[], int matrixValue[], int row, int targetRow, int column, int targetColumn)
{
    for(int i = 0; i < row; i++)
    {
        if(matrixRow[i] == targetRow)
        {
            for(int j = 0; j < column; j++)
            {
                if(matrixColumn[j] == targetColumn)
                {
                    if(i == j)
                    {
                        return matrixValue[j];
                    }
                }
            }
        }
    }
    return 0;
}

void printMatrix(int matrixRow[], int matrixColumn[], int matrixValue[], int row, int column)
{
    for(int i = 0; i < row; i++)
    {
        cout << "{";
        for(int j = 0; j < column; j++)
        {
            if(column != j + 1){
                int result = findData(matrixRow, matrixColumn, matrixValue, row, i, column, j);
                cout << result << ", ";
            }
            else{
                int result = findData(matrixRow, matrixColumn, matrixValue, row, i, column, j);
                cout << result << "}" << endl;
            }
        }
    }
}
int main()
{
    cout<<"Hello World" << endl;
    int matrixRow[] = {0, 1, 2};
    int matrixColumn[] = {2, 2, 1};
    int matrixValue[] = {76, 34, 23};
    int row = 5;
    int column = 4;
    
    printMatrix(matrixRow, matrixColumn, matrixValue, row, column);
    return 0;
}

