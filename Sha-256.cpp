#include <iostream>
#include <cstring>
#include <vector>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

const unsigned int K[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

unsigned int rightRotate(unsigned int value, unsigned int rotation)
{
    unsigned int right_shifted = value >> rotation;
    unsigned int left_shifted = value << (32 - rotation);
    return right_shifted + left_shifted;
}


void processBlock(const unsigned char block[64], unsigned int H[8])
{
    unsigned int W[64];
    for(int i = 0; i < 16; ++i)
    {
        W[i] = (block[i * 4] << 24) | (block[i * 4 + 1] << 16) | (block[i * 4 + 2] << 8) | block[i * 4 + 3];
    }

    for(int i = 16; i < 64; ++i)
    {
        unsigned int s0 = rightRotate(W[i - 15], 7) ^ rightRotate(W[i - 15], 18) ^ (W[i - 15] >> 3);
        unsigned int s1 = rightRotate(W[i - 2], 17) ^ rightRotate(W[i - 2], 19) ^ (W[i - 2] >> 10);
        W[i] = W[i - 16] + s0 + W[i - 7] + s1;
    }

    unsigned int a = H[0];
    unsigned int b = H[1];
    unsigned int c = H[2];
    unsigned int d = H[3];
    unsigned int e = H[4];
    unsigned int f = H[5];
    unsigned int g = H[6];
    unsigned int h = H[7];
    
    for(int i = 0; i < 64; ++i)
    {
        unsigned int S1 = rightRotate(e, 6) ^ rightRotate(e, 11) ^ rightRotate(e, 25);
        unsigned int ch = (e & f) ^ (~e & g);
        unsigned int temp1 = h + S1 + ch + K[i] + W[i];
        unsigned int S0 = rightRotate(a, 2) ^ rightRotate(a, 13) ^ rightRotate(a, 22);
        unsigned int maj = (a & b) ^ (a & c) ^ (b & c);
        unsigned int temp2 = S0 + maj;

        h = g;
        g = f;
        f = e;
        e = d + temp1;
        d = c;
        c = b;
        b = a;
        a = temp1 + temp2;
    }

    H[0] = H[0] + a;
    H[1] = H[1] + b;
    H[2] = H[2] + c;
    H[3] = H[3] + d;
    H[4] = H[4] + e;
    H[5] = H[5] + f;
    H[6] = H[6] + g;
    H[7] = H[7] + h;
}

string sha256(string input)
{
    unsigned int H[8] = {
        0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
        0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
    };

    unsigned long long bitLen = input.size() * 8;
    cout << input.size() << endl;
    unsigned int bufferSize = ((input.size() + 72) / 64) * 64;
    vector<unsigned char> buffer(bufferSize, 0);

    memcpy(buffer.data(), input.data(), input.size());
    buffer[input.size()] = 0x80;
    for(int i = 7; i >= 0; --i)
    {
        buffer[bufferSize - 1 - i] = (bitLen >> (8 * i)) & 0xFF;
    }

    for(int i = 0; i < bufferSize; i = i + 64)
    {
        processBlock(buffer.data() + i, H);
    }

    stringstream result;

    for(int i = 0; i < 8; ++i)
    {
        result << hex << setw(8) << setfill('0') << H[i];
    }
    return result.str();
}

string getFileContent(string& filePath)
{
    ifstream file(filePath);
    if(!file.is_open())
    {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return "";
    }
    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

int main()
{
    string filePath = "Mark.txt";
    string fileContent = getFileContent(filePath);
    //string fileContent = "Hello, world!Hello, world!Hello, world!Hello, world!Hello, world!Hello, world!Hello, world!";
    string hash = sha256(fileContent);
    cout << "SHA-256 hash: " << hash << endl;
    return 0;
}
