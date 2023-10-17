#include <iostream>
#include "resizeArray.hpp"

/*
    CITATION:

    Referenced Lab - 0 code for this file
*/

// Constructor
resizableArray::resizableArray(int initCap) {
    initCapacity = initCap;
    currentCapacity = initCap;
    size = 0;
    array = new std::string[initCap];
}

// Destructor
resizableArray::~resizableArray() {
    delete[] array;
}

// Get the size
int resizableArray::getSize() {
    return size;
}

// Get the capacity
int resizableArray::getCapacity() {
    return currentCapacity;
}

// Push adds an element to the start of the array, moving everything down, resizing if needed
bool resizableArray::push(std::string val) {
    if (size == currentCapacity - 1) {
        std::string* newAr = new std::string[currentCapacity * 2];
        for (int i = 0; i < size; i++)
            newAr[i] = array[i];
        currentCapacity = currentCapacity * 2;
        delete[] array;
        array = newAr;
    }

    // Put it at the front
   

    array[size] = val;
    size++;
    return true;
}

void resizableArray::resize(int newSize) {
    // Check if the requested new size is valid
    if (newSize <= 0) {
        return;
    }

    if (newSize < currentCapacity) {
        // If the newSize is smaller than the current capacity, we consider whether to shrink.
        if (newSize >= size) {
             // If newSize is greater than or equal to the current size, it's safe to shrink.
            std::string* newAr = new std::string[newSize];
            for (int i = 0; i < size; i++)
                newAr[i] = array[i];
            currentCapacity = newSize;
            delete[] array;
            array = newAr;
        }
    } else if (newSize > currentCapacity) {
        // If newSize is larger than the currentCapacity, expand the array.
        std::string* newAr = new std::string[newSize];
        for (int i = 0; i < size; i++)
            newAr[i] = array[i];
        currentCapacity = newSize;
        delete[] array;
        array = newAr; // Update the array reference to the new array.
    }
}


// Get the element at the given index
std::string resizableArray::getAt(int indx) {
    if (indx < 0 || indx >= size)
        return 0; // Return 0 if the index is out of bounds

    return array[indx];
}

