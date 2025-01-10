#include <iostream>
#include <vector>
using namespace std;
int findAdd(int number, vector<int> array, int arraySize);
int checkAmount();
int checkTarget();
int main()
{
    
    
    vector<int> array;
    int amount = checkAmount();
    int number;
    cout << "Type the numbers in the array" << endl;
    for(int i = 0; i < amount; i++)
    {
        cin >> number;
        if(number <= -110 || 110 <= number)
        {
            cout << "Invalid number" << endl;
            i--;
        }
        else
        {
            array.push_back(number);  
        }

    }
    int target = checkTarget();
    
    
    findAdd(target, array, sizeof(array)/sizeof(array[0]));
    return 0;
}
int checkTarget()
{
    int target;
    cout << "Type a target number: ";
    cin >> target;
    if(target <= -110 || 110 <= target)
    {
        cout << "Invalid number" << endl;
        return checkTarget();
    }
    else
    {
        return target;
    }
}
int checkAmount()
{
    int amount;
    cout << "Type the amount of numbers in the array: ";
    cin >> amount;
    if(amount <= 1 || 105 <= amount)
    {
        cout << "Invalid number" << endl;
        return checkAmount();
    }
    return amount;
}
int findAdd(int number, vector<int> array, int arraySize)
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