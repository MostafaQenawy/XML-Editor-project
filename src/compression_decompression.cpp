#include "compression_decompression.h"

using namespace std;

Node *root;

// Build Huffman tree and return the root
Node* buildHuffmanTree(const string& text) {
    // Count frequency of each character
    unordered_map<char, unsigned> freq;
    for (char c : text) {
        freq[c]++;
    }

    // Create a priority queue to store nodes
    priority_queue<Node*, vector<Node*>, Compare> pq;

    // Create a leaf node for each character and add it to the priority queue
    for (const auto& pair : freq) {
        pq.push(new Node(pair.first, pair.second));
    }

    // Build Huffman tree
    while (pq.size() > 1) {
        Node* left = pq.top();
        pq.pop();

        Node* right = pq.top();
        pq.pop();

        Node* internalNode = new Node('$', left->frequency + right->frequency);
        internalNode->left = left;
        internalNode->right = right;

        pq.push(internalNode);
    }

    // The root of the Huffman tree is the final node in the priority queue
    return pq.top();
}

void printCodes(Node* root, string code, unordered_map<char, string>& codes) {
    if (root == nullptr) {
        return;
    }

    if (root->data != '$') {
        codes[root->data] = code;
    }

    printCodes(root->left, code + "0", codes);
    printCodes(root->right, code + "1", codes);
}


string binaryStringToChars(const string& binaryString) {
    string result;

    // Ensure the binary string length is a multiple of 8
    size_t len = binaryString.length();

    // Iterate through the binary string in groups of 8 bits
    size_t i;
    for ( i = 0; i < len; i += 8) {
        if(i+7 >= len)
            break;
        string byteStr = binaryString.substr(i, 8);
        char character = 0;

        // Convert the 8-bit substring to a char
        for (size_t j = 0; j < 8; ++j) {
            character = (character << 1) | (byteStr[j] - '0');
        }

        // Append the char to the result string
        result.push_back(character);

    }
    if(i < len )
    {
        int count =0 ;
        for(int z = i ; z < len ; z++){
            result.push_back(binaryString[z]);
            count++;
        }
        result.push_back(count+'0');
    }

    return result;
}


string Compress(const string& text) {
    // convert into string


    // Build Huffman tree
    root = buildHuffmanTree(text);
    // Build Huffman tree and return the root
    auto buildHuffmanTree = [](const string& text) -> Node* {
        // Count frequency of each character
        unordered_map<char, unsigned> freq;
        for (char c : text) {
            freq[c]++;
        }

        // Create a priority queue to store nodes
        priority_queue<Node*, vector<Node*>, Compare> pq;

        // Create a leaf node for each character and add it to the priority queue
        for (const auto& pair : freq) {
            pq.push(new Node(pair.first, pair.second));
        }

        // Build Huffman tree
        while (pq.size() > 1) {
            Node* left = pq.top();
            pq.pop();

            Node* right = pq.top();
            pq.pop();

            Node* internalNode = new Node('$', left->frequency + right->frequency);
            internalNode->left = left;
            internalNode->right = right;

            pq.push(internalNode);
        }

        // The root of the Huffman tree is the final node in the priority queue
        return pq.top();
    };

    // Encode the input text using Huffman codes
    auto encode = [](const string& text, unordered_map<char, string>& codes) -> string {
        string encodedText;
        for (char c : text) {
            encodedText += codes[c];
        }
        return encodedText;
    };

    // Build Huffman tree
    Node* root = buildHuffmanTree(text);

    // Traverse the tree and get Huffman codes
    unordered_map<char, string> codes;
    printCodes(root, "", codes);

    // Encode the input text
    string encodedText = encode(text, codes);


    string result = binaryStringToChars(encodedText);

    ofstream comp("compressed_file.txt");
    comp << result;
    comp.close();
    // Print the encoded text


    return result;
}

string charsToBinaryString(const string& inputString) {
    string result;
    int z =0;
    size_t len = inputString.length();
    if (inputString[len-1] >='1' && inputString[len-1] <='7'){
        z  = inputString[len-1] -'0';
        for(int i = 0 ;i < len-z-1; i++) {
            // Convert each character to its binary representation (8 bits)
            result += bitset<8>(inputString[i]).to_string();
        }
        for(int i = len-z-1 ;i < len-1; i++) {
            // Convert each character to its binary representation (8 bits)
            result += inputString[i];
        }
    }
    else
    {
        for (int i = 0 ;i < len; i++) {
            // Convert each character to its binary representation (8 bits)
            result += bitset<8>(inputString[i]).to_string();
        }
    }
    return result;
}

// Release memory allocated for the Huffman tree nodes
void deleteTree(Node* root) {
    if (root == nullptr) {
        return;
    }

    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

// Decode the encoded text using Huffman tree
string decode(const string& result){
    string str = charsToBinaryString(result);
    string decodedText ;
    Node* current = root;

    for (char bit :str) {
        if (bit == '0') {
            current = current->left;
        } else if (bit == '1') {
            current = current->right;
        }

        if (current->left == nullptr && current->right == nullptr) {
            decodedText += current->data;
            current = root;
        }
    }
    ofstream decomp("Original_file.xml");
    decomp << decodedText;
    decomp.close();
    deleteTree(root);
    return decodedText;
}


