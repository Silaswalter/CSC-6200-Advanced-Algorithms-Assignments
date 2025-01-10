#include <iostream>
using namespace std;
int findAdd(int number, int array[], int arraySize);
int main()
{
    
    int number;
    cout << "Type a number: ";
    cin >> number;
    int array[] = {11, 15, 2, 7};
    findAdd(number, array, sizeof(array)/sizeof(array[0]));
    return 0;
}

int findAdd(int number, int array[], int arraySize)
{
    if(arraySize > 104 || arraySize < 2)
    {
        cout << "Invalid array input length." << endl;
    }
    for(int i = 0; i < arraySize; i++)
    {
        for(int j = 1 + i; j < arraySize; j++)
        {
            if(array[i] + array[j] == number)
            {
                cout << "[" << i << ", " << j << "]" << endl;
                int result[] = {i, j};
                return 0;
            }
        }
    }
    cout << "No solution found :(" << endl;
    return 0;
}