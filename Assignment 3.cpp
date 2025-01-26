#include <iostream>
using namespace std;
class LinkedList{
    public:
        int row;
        int column;
        int value;
        LinkedList* nextList;
    
    LinkedList(int row, int column, int value, LinkedList* nextList)
    {
        this-> row = row;
        this-> column = column;
        this-> value = value;
        this-> nextList = nextList;
    }
};
int searchList(LinkedList* list, int targetRow, int targetColumn)
{
    if(targetRow == list->row)
    {
        if(targetColumn == list->column){
                return list->value;
        }
        else
        {
            if(list->nextList == nullptr)
            {
                return 0; 
            }
        }
    }
    else
    {
        if(list->nextList == nullptr)
        {
            return 0;
        }
    }
    return searchList(list->nextList, targetRow, targetColumn);
}

int getValidRow(int validNumber)
{
    int input;
    cout << "Input the row of the item: " << endl;
    cin >> input;
    if(-1 < input && input <= validNumber)
    {
        return input;
    }
    else
    {
        cout << "Invalid input" << endl;
        getValidRow(validNumber);
    }
    return 0;
}

int getValidColumn(int validNumber)
{
    int input;
    cout << "Input the column of the item: " << endl;
    cin >> input;
    if(-1 < input && input <= validNumber)
    {
        return input;
    }
    else
    {
        cout << "Invalid input" << endl;
        getValidColumn(validNumber);
    }
    return 0;
}

LinkedList* makeList(int row, int column, int items)
{
    int listRow;
    int listColumn;
    int listValue;
    bool first = true;
    LinkedList* list = nullptr;
    for(int i = 0; i < items; i++)
    {
        cout << "Input value for item: " << endl;
        cin >> listValue;
        listRow = getValidRow(row);
        listColumn = getValidColumn(column);
        if(first == true)
        {
            LinkedList* list1 = new LinkedList(listRow, listColumn, listValue, nullptr);
            LinkedList* list = new LinkedList(listRow, listColumn, listValue, list1);
            first = false;
        }
            LinkedList* item = new LinkedList(listRow, listColumn, listValue, list);
            list = item;
    }
    return list;
}

int main()
{
    int row;
    int column;
    int items;
    
    cout << "Enter number of rows: " << endl;
    cin >> row;
    cout << "Enter number of colums: " << endl;
    cin >> column;
    cout << "Enter number of items: " << endl;
    cin >> items;
    
    LinkedList* listHead = makeList(row, column, items);

    for(int i = 0; i < row; i++)
    {
        cout << "{";
        for(int j = 0; j < column; j++)
        {
            if(column != j + 1){
                int result = searchList(listHead, i, j);
                cout << result << ", ";
            }
            else{
                int result = searchList(listHead, i, j);
                cout << result << "}" << endl;
            }
        }
    }
    return 0;
}

