#include <iostream>     // cout
#include <fstream>      // ofstream/ifstream - input/output files
#include <vector>       // vector
#include <algorithm>    // sort file names in a-z order
#include <string>       // string
#include <dirent.h>     // dirent - folder/files
#include <string.h>     // strlen/strcmp

// Alphabet size (# of symbols)
#define ALPHABET_SIZE (26)
// Converts key current character into index
// use only 'a' through 'z' and lower case
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

class TrieNode {
public:
    // Initialize the data structure here.
    TrieNode() {
        value = 0;
        for (int i = 0; i < ALPHABET_SIZE; i++)	{
            children[i] = NULL;
        }
    }
    int value;
    TrieNode *children[ALPHABET_SIZE];
};

// Key idea of a prefix tree for words: every node has 26 children
class Trie {
public:
    Trie() {
        root = new TrieNode();
        count = 0;
    }

    // Inserts a word into the trie.
    void insert(std::string& s) {
        int length = s.length();
        int index;
        TrieNode *pCrawl = root;
        count++;
        for (int level = 0; level < length; ++level) {
            index = CHAR_TO_INDEX(s[level]);
            if (index >= 0 && index < ALPHABET_SIZE) {
                if (!pCrawl->children[index]) {
                    pCrawl->children[index] = new TrieNode();
                }
                pCrawl = pCrawl->children[index];
            }
        }
        // mark last node as leaf (increase our counter here)
        if (pCrawl != root)
            ++pCrawl->value;    // if value is 0, the word doesn't end here
    }
    
    // traverse and print all the words with their freq
    void traverse(std::ofstream& outFile) {
        TrieNode *n = root;
        std::string word = "";
        traverse_helper(word, n, outFile);
    }
    
    void traverse_helper(std::string& word, TrieNode *n, std::ofstream& outFile) {
        if (n->value != 0) {
            outFile << word << "\t" << n->value << std::endl;
            //std::cout << word << "\t" << n->value << std::endl;
        }
        for (int i = 0; i < ALPHABET_SIZE; ++i) {
            if (n->children[i] != NULL) {
                word.push_back('a' + i);
                traverse_helper(word, n->children[i], outFile);
                word.pop_back();
            }
        }
    }

private:
    TrieNode* root;
    int count;  // # of words in the trie
};

class Counter {
    Trie trie;
public:
    void countWordsInTxts() {
        std::string inputDir = "wc_input";
        std::string outputPath = "wc_output/wc_result.txt";
        std::ofstream outFile;
        outFile.open(outputPath, std::ofstream::out);
        if (!outFile.is_open()) {
            std::cout << "Error opening file for output!";
            return;
        }
        std::vector<std::string> files = getAllTxts(inputDir);
        std::sort(files.begin(), files.end());
        std::cout << "Processing txt files: " << std::endl;
        for (std::string file : files) {
            std::ifstream inFile;
            std::cout << "    " << file << std::endl;
            inFile.open(inputDir + "/" + file, std::ios::in);
            std::string word;
            if (!inFile) return;
            while ( inFile >> word ) {  // get each word in each file
                //std::cout << word << " ";
                toLower(word);
                trie.insert(word);
            }
            inFile.close();
        }
        trie.traverse(outFile);
        outFile.close();
        std::cout << "Done!" << std::endl;
    }
    
    void toLower(std::string& word) {
        for (char& c : word)
            if (c >= 'A' && c <= 'Z')
                c += 32;
    }

    std::vector<std::string> getAllTxts(std::string path = ".") {
        DIR*    dir;
        struct dirent* pdir;
        std::vector<std::string> files;

        dir = opendir(path.c_str());

        while (pdir = readdir(dir)) {
            int pos = strlen(pdir->d_name) - 4;
            if (pdir->d_type == DT_REG && !strcmp(&pdir->d_name[pos], ".txt"))  // check if it's a file or folder and the extension
                files.push_back(pdir->d_name);
        }

        return files;
    }
};

int main(void) {

    Counter counter;

    counter.countWordsInTxts();

    return 0;
}

