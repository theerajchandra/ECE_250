#include "hashtable.hpp"
#include "resizeArray.hpp"
#include <cmath>

//Defining a constructor for HashNode class
/*
    CITATION:

    ChatGPT helped me with the syntax for constructor - line 11
    Referred ECE 150 course notes
*/
HashNode::HashNode(const std::string& w, int t, HashNode *const p_next_node): word(w), token(t), next(p_next_node) {}

//Defining a constructor for Hashtable class
/*
    CITATION:

    ChatGPT helped me with the generating this constructor - line 19
    Referred ECE 150 course notes for syntax
*/
Hashtable::Hashtable(int size) : LOAD_FACTOR_THRESHOLD(0.7), tableSize(size), numKeys(0), array (size) {
    table = new HashNode*[tableSize]();
}

// Destructor for Hashtable class.

Hashtable::~Hashtable() {
    for (int i = 0; i < tableSize; i++) {
        HashNode* current = table[i];
        while (current) {
            HashNode* temp = current;
            current = current->next;
            delete temp; // Deallocate the memory for HashNode objects.
        }
    }
    delete[] table; // Deallocate the memory for the HashNode* array.
}


// Hash function to calculate the index for a given key.
int Hashtable::hash(const std::string& key) {
    int hashValue = 0;
    for (char c : key) {
        hashValue += int(c);
    }
    return hashValue % tableSize;
}

// Lookup function to check if a key exists in the hash table and return its index.
bool Hashtable::lookup(const std::string& key, int& index) {
    int hashValue = hash(key);
    index = hashValue ;

    HashNode* current = table[index];
    while (current) {
        if (current->word == key) {
            return true;
        }
        current = current->next;
    }

    return false;
}

// Insert a new word into the hash table.

/*
CITATION:
    ChatGPT helped me troubleshoot a few errors in this segment of code.
    ChatGPT helped me verify the Runtime complexity for this segment.
*/


bool Hashtable::insert(const std::string& word) {
    // Check if the word is already in the dictionary
    int index;
    if (lookup(word, index)) {
        return false;  // Word already exists in the dictionary
    }

    // Insert the word into the dictionary
    HashNode* newNode = new HashNode(word, numKeys + 1, table[index]);
    table[index] = newNode;
    array.push(word);
    numKeys++;
    
    return true;
}

// Tokenize words from an input file and add them to the hash table.
/*
    CITATION:

    ChatGPT helped me troubleshoot a few errors in this segment of code.
*/

bool Hashtable::tokenizeFile(std::ifstream& fin) {
    std::string toRead;
    bool atLeastOneWordAdded = false;

    while (fin >> toRead) {
        bool isAlphaWord = true;
        for (char c : toRead) {
            if (!isalpha(c)) {
                isAlphaWord = false;
                break;
            }
        }

        if (isAlphaWord) {
            int index;
            if (!lookup(toRead, index)) {
                index = insert(toRead) ? index : 0;
                atLeastOneWordAdded = true;
            }
        }
    }

    return atLeastOneWordAdded;
}

// Tokenize a word and return its token (or 0 if not found).
int Hashtable::tokenizeWord(const std::string& word) {
    int index = hash(word);

    HashNode* current = table[index];
    while (current != nullptr) {
        if (current->word == word) {
            return current->token; // Return the token for known words
        }
        current = current->next;
    }

    return 0; // Return 0 to indicate that the word is not in the dictionary
}

// Retrieve a word based on its token.
std::string Hashtable::retrieveWord(int token) {
    if (token < 1 || token > numKeys) {
        return "UNKNOWN";  // Token is out of bounds
    }

    // Retrieve and return the word corresponding to the token
    return array.getAt(token - 1);  // Adjust for 0-based array indexing
}


// Retrieve a word based on its token.
void Hashtable::tokenizeString() {
    std::string word;
    while (std::cin >> word) {
        if (word == "_DONE_") {
            break;  // Exit the loop when "DONE" is encountered
        }

        int token = tokenizeWord(word);
        std::cout << token << ' ';
    }

    std::cout << std::endl; // Output a newline after all tokens
}


// This is a helper function to calculate the hash value based on ASCII values of characters in a string.
int hashASCII(std::string key){int hashValue = 0;
    for (char c : key) {
        hashValue += int(c);
    }return hashValue;} 


// Convert tokens to corresponding words and print them.
std::string Hashtable::tokensToString() {
  int index;
    while (std::cin >> index) {
        if (index == -1) {
            break;  // Exit the loop when "DONE" is encountered
        }

        std::string token = retrieveWord(index);
        std::cout << token << ' ';
    }

    std::cout << std::endl; 
    return "";
}

// Print the linked list at a specified position in the hash table.
void Hashtable::printChain(int k) {
    if (k < 0 || k >= getTableSize()) {
        std::cout << "Invalid position" << std::endl;
        return;
    }

    HashNode* current = table[k];
    if (!current) {
        std::cout << "chain is empty" << std::endl;
        return;
    }

    while (current) {
        std::cout << hashASCII(current->word )<< ' ';
        current = current->next;
    }

    std::cout << std::endl;
}
