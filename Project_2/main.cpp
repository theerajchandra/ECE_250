#include <iostream>
#include "hashtable.hpp"

//This is the main file, accepts input from user and generates appropriate output
using namespace std;

int main() {
    Hashtable *hashtable;
    string command;

    while (cin >> command) {
        if (command == "M") {
            int size;
            cin >> size;
            hashtable = new Hashtable(size);
            cout << "success" << endl;
        } else if (command == "INSERT") {
            string word;
            cin >> word;
            if (hashtable->insert(word)) {
                cout << "success" << endl;
            } else {
                cout << "failure" << endl;
            }
        } else if (command == "READ") {
            string filename;
            cin >> filename;
            ifstream fin(filename);
            if (fin) {
                if (hashtable->tokenizeFile(fin)) {
                    cout << "success" << endl;
                } else {
                    cout << "failure" << endl;
                }
            } else {
                cout << "failure" << endl; // Failed to open the input file
            }
        } else if (command == "TOKENIZE") {
            string word;
            cin >> word;
            int token = hashtable->tokenizeWord(word);
            cout << token << endl;
        } else if (command == "RETRIEVE"){
            int token;
            cin >> token;
            string word = hashtable->retrieveWord(token);
            cout << word << endl;
        } else if (command == "PRINT") {
            int position; // The position (k) you want to print
            cin >> position;
            hashtable->printChain(position);

        }else if (command == "TOKS") {
            string words = hashtable->tokensToString();
        }else if (command == "STOK") {
            hashtable->tokenizeString();

        }else if (command == "EXIT"){
            break;
        }

    }

    delete hashtable;
    return 0;
}
