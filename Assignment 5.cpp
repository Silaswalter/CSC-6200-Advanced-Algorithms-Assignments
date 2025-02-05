#include <iostream>
#include <vector>
using namespace std;
int main()
{
    string a = "ABABC";
    string b = "BABAC";
    //bool streak = false;
    string longest = "";
    int maxChain = 0;
    int map[b.size()+1][a.size()+1];

    cout << " ";
    for(int i = 0; i < a.size(); i++){
        cout << " " << a[i];
    }
    //cout << endl;
    for(int i = 0; i < a.size() + 1; i++){
        map[0][i] = 0;
    }
    for(int i = 0; i < b.size() + 1; i++){
        map[i][0] = 0;
    }
    /*for(int i = 0; i < a.size() + 1; i++){
        cout << " " << map[0][i];
    }*/
    cout << endl;
    
    
    
    for(int j = 1; j < b.size() + 1; j++)
    {
        cout << b[j - 1] /*<< map[j][*/ << "{";
        for(int i = 1; i < a.size() + 1; i++)
        {
            if(b[j-1] == a[i-1])
            {
                if(map[j-1][i-1] != 0)
                {
                    map[j][i] = map[j-1][i-1] + 1;
                    if(maxChain < map[j][i])
                    {
                        maxChain = map[j][i];
                        int k = j;
                        int o = i;
                        longest = "";
                        while(map[k][o] > 0)
                        {
                            longest += b[k];
                            k --;
                            o --;
                        }
                    }
                    
                }
                else
                {
                    map[j][i] = 1;                    
                }
            }
            else
            {
                map[j][i] = 0;                
            }

            cout << map[j][i] << " ";
        }
        cout << "}" << endl;
    }
    
    cout << "Longest common string: " << longest << endl;
    cout << "With a Length of: " << maxChain << endl;
    
    

    return 0;
}