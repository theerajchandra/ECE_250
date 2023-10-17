/*
    CITATION:
    
    ChatGPT helped me generate the header file

*/
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <fstream>
#include "resizeArray.hpp"

class HashNode {
public:
    HashNode(const std::string& w, int t, HashNode *const p_next_node);
    std::string word;
    int token;
    HashNode* next;
};

class Hashtable {
public:
    Hashtable(int size);
    ~Hashtable();
    int hash(const std::string& key);
    bool lookup(const std::string& key, int& index);
    bool insert(const std::string& word);
    bool tokenizeFile(std::ifstream& fin);  // Updated parameter type
    int tokenizeWord(const std::string& word);
    void tokenizeString(); // for STOK
    void printChain(int k);
    std::string retrieveWord(int token);
    std::string tokensToString(); //for TOKS
    
    int getTableSize() {
        return tableSize;
    }

    HashNode** getTable() {
        return table;
    }



private:
    const double LOAD_FACTOR_THRESHOLD;
    HashNode** table;
    int tableSize;
    int numKeys;
    resizableArray array;
};

#endif
