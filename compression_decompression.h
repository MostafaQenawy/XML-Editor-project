#ifndef compression_decompression
#define compression_decompression

#include <iostream>
#include <unordered_map>
#include <fstream>
#include <queue>
#include <string>
#include <sstream>
#include <bitset>

using namespace std;

// Node structure for Huffman tree
struct Node {
    char data;
    unsigned frequency;
    Node* left, * right;

    Node(char data, unsigned frequency) : data(data), frequency(frequency), left(nullptr), right(nullptr) {}
};

// Comparison function for priority queue
struct Compare {
    bool operator()(Node* left, Node* right){
        return left->frequency > right->frequency;
    }
};

Node* buildHuffmanTree(const string& text);
void printCodes(Node* root, string code, unordered_map<char, string>& codes);
string binaryStringToChars(const string& binaryString);
string Compress(const string& text);
string charsToBinaryString(const string& inputString);
void deleteTree(Node* root);
string decode(const string& result);

#endif // compression_decompression
