#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

struct Node {
    char ch;
    int freq;
    Node *left, *right;

    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

void generateCodes(Node* root, string code, unordered_map<char, string> &huffmanCode) {
    if (!root) return;
    if (!root->left && !root->right) {
        huffmanCode[root->ch] = code;
    }
    generateCodes(root->left, code + "0", huffmanCode);
    generateCodes(root->right, code + "1", huffmanCode);
}

Node* buildHuffmanTree(const string &text, unordered_map<char, string> &huffmanCode) {
    unordered_map<char, int> freq;
    for (char ch : text)
        freq[ch]++;

    priority_queue<Node*, vector<Node*>, Compare> pq;
    for (auto &pair : freq)
        pq.push(new Node(pair.first, pair.second));

    while (pq.size() > 1) {
        Node *left = pq.top(); pq.pop();
        Node *right = pq.top(); pq.pop();

        Node* newNode = new Node('\0', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;
        pq.push(newNode);
    }

    Node* root = pq.top();
    generateCodes(root, "", huffmanCode);
    return root;
}

string encode(const string &text, unordered_map<char, string> &huffmanCode) {
    string encoded = "";
    for (char ch : text)
        encoded += huffmanCode[ch];
    return encoded;
}

string decode(Node* root, const string &encodedStr) {
    string decoded = "";
    Node* current = root;

    for (char bit : encodedStr) {
        current = (bit == '0') ? current->left : current->right;
        if (!current->left && !current->right) {
            decoded += current->ch;
            current = root;
        }
    }

    return decoded;
}

int main() {
    ifstream inFile("input.txt");
    ofstream encodedFile("encoded.txt");
    ofstream codeFile("codes.txt");
    ofstream outFile("decoded.txt");

    if (!inFile.is_open()) {
        cerr << "Error: input.txt not found.\n";
        return 1;
    }

    string text((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
    unordered_map<char, string> huffmanCode;
    Node* root = buildHuffmanTree(text, huffmanCode);

    // Save Huffman Codes
    for (auto &pair : huffmanCode) {
        if (pair.first == '\n') codeFile << "\\n " << pair.second << '\n';
        else if (pair.first == ' ') codeFile << "' ' " << pair.second << '\n';
        else codeFile << pair.first << ' ' << pair.second << '\n';
    }

    // Encode and Save to File
    string encodedStr = encode(text, huffmanCode);
    encodedFile << encodedStr;

    // Decode and Save to File
    string decodedStr = decode(root, encodedStr);
    outFile << decodedStr;

    // Close all files
    inFile.close();
    encodedFile.close();
    codeFile.close();
    outFile.close();

    cout << "Compression completed successfully.\n";
    cout << "Check encoded.txt, codes.txt, and decoded.txt\n";

    return 0;
}
