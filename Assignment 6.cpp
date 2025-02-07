#include <iostream>
#include <vector>
using namespace std;

struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;
    
    Node()
    {
        ch = '/';
        freq = 0;
        left = nullptr;
        right = nullptr;
    }
    Node(char ch, int freq, Node* left, Node* right)
    {
        this->ch = ch;
        this->freq = freq;
        this->left = left;
        this->right = right;
    }
};

int findMin(vector<Node*>& nodes) {
    int lowestNumber = nodes[0]->freq + 1;
    int lowestIndex;
    for(int i = 0; i < nodes.size(); i++)
    {
        if(nodes[i]->freq < lowestNumber)
        {
            lowestNumber = nodes[i]->freq;
            lowestIndex = i;
        }
    }
    return lowestIndex;
}

Node* buildHuffmanTree(vector<char>& chars, vector<int>& freqs) {
    vector<Node*> nodes;
    for(int i = 0; i < chars.size(); ++i)
    {
        nodes.push_back(new Node(chars[i], freqs[i], nullptr, nullptr));
    }

    while(nodes.size() > 1)
    {
        int minIndex1 = findMin(nodes);
        Node* minNode1 = nodes[minIndex1];
        nodes.erase(nodes.begin() + minIndex1);

        int minIndex2 = findMin(nodes);
        Node* minNode2 = nodes[minIndex2];
        nodes.erase(nodes.begin() + minIndex2);

        Node* top = new Node('/', minNode1->freq + minNode2->freq, minNode1, minNode2);
        nodes.push_back(top);
    }
    return nodes[0];
}

void printTree(Node* node, string code)
{
    if(node->left != nullptr)
    {
        printTree(node->left, code + "0");
    }
    if(node->right != nullptr)
    {
        printTree(node->right, code + "1");
    }
    if(node->left == nullptr && node->right == nullptr)
    {
        cout << node->ch << ": " << code << endl;
    }
}

string getInputLetter()
{
    string input;
    cout << "Input the letter being compressed: ";
    cin >> input;
    if(input.size() != 1)
    {
        cout << "Incorrect length";
        getInputLetter();
    }
    return input;
}

int frequenceOfLetter()
{
    int input;
    cout << "Input the frequence of letter: ";
    cin >> input;
    if(input <= 0)
    {
        cout << "Invalid input" << endl;
        frequenceOfLetter();
    }
    return input;
}

int main() {
    
    int numOfLetters;
    cout << "Input the number of letters: ";
    cin >> numOfLetters;
    string S = "";
    string tempLet;
    int tempNum;
    int f[numOfLetters-1];
    for(int i = 0; i < numOfLetters; i++)
    {
        S = S + getInputLetter();
        f[i] = frequenceOfLetter();
    }
    //string S = "abcdef";
    //int f[] = {5, 9, 12, 13, 16, 45};
    
    vector<char> chars(S.begin(), S.end());
    vector<int> freqs(f, f + numOfLetters);

    Node* root = buildHuffmanTree(chars, freqs);
    printTree(root, "");
    
    return 0;
}