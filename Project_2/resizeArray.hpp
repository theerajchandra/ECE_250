#include <iostream>
#ifndef RESIZE_ARRAY
#define RESIZE_ARRAY

/*
    CITATION:

    Referenced Lab - 0 code for this file
*/

class resizableArray {
private:
    int initCapacity;
    int currentCapacity;
    int size;
    std::string* array;

public:
    // Constructor
    resizableArray(int initCap);

    // Destructor
    ~resizableArray();

    // Get the size
    int getSize();

    //Get the capacity
    int getCapacity();

    // Push adds an element to the start of the array, moving everything down, resizing if needed
    bool push(std::string val);

    // Get the element at the index but do not remove it
    std::string getAt(int indx);

    // Resize the array to a new size
    void resize(int newSize);

};

#endif
