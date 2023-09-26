#include <iostream>
#include <cmath>
#include "ChildrensGame.hpp"

//Defining a constructor for Child class and initializing x and y coordinates
/*
    CITATION:
    ChatGPT helped me with the syntax - line 11
    Referred ECE 150 course notes

*/
Child::Child(double x, double y) : x(x), y(y) {} 

//Defining a function within Child class, returns x coordinate
double Child::getX() const {
    return x;
}

//Defining a function within Child class, returns y coordinate
double Child::getY() const {
    return y;
}

//Defining a function within Child class, calculates distance of the child from the origin
double Child::distanceToWolf() const {
    return sqrt(x * x + y * y);
}

//Defining the constructor for the Node class, used in LinkedList class
/*
    CITATION:
    ChatGPT helped me with the syntax - line 29

*/
LinkedList::Node::Node(Child child) : child(child), next(nullptr) {}

//Defining the constructor for the LinkedList class
LinkedList::LinkedList() : head(nullptr) {}

//function to check if linked list is empty
bool LinkedList::isEmpty() const {
    return head == nullptr;
}

//function that pushes/adds a child to the front of the linked list
void LinkedList::push_front(Child child) {
    Node* newNode = new Node(child);
    newNode->next = head;
    head = newNode;
}



//function to delete node from linked list.
/*
    CITATION:
    ChatGPT helped me fix a bug in this segment of code

*/
void LinkedList::removeNode(Node* target) {
    if (!isEmpty() && head == target) {
        head = head->next;
        delete target;                      
        return;
    }
    Node* curr = head;
    while (curr != nullptr && curr->next != target) {
        curr = curr->next;
    }

    if (curr != nullptr) {
        curr->next = target->next;
        delete target;
    }
}

//Defining a function to return the head of linked list
LinkedList::Node* LinkedList::getHead() const {
    return head;
}

//Defining destructor for LinkedList class
/*
    CITATION:
    ChatGPT helped me with the syntax for destructor
*/
LinkedList::~LinkedList() {
    while (!isEmpty()) {
        removeFront();
    }
}

//function to delete/remove front node from linked list
void LinkedList::removeFront() {
    if (!isEmpty()) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

//function that returns the child at front of the linked list
Child LinkedList::getFront() const {
    if (!isEmpty()) {
        return head->child;
    }
    // Return a dummy Child object when the list is empty
    /*
    CITATION:
    ChatGPT helped me with line 103

    */
    return Child(-1, -1);                               
}

//function within ChildrenGame class that spawns a child in the first quadrant
bool ChildrenGame::spawnChild(double x, double y) {
    if (x > 0 && y > 0) {
        children.push_front(Child(x, y));
        return true;
    }
    return false;
}

// this function moves children according to the time parameter
/*
    CITATION:
    ChatGPT helped me troubleshoot a few errors in this segment of code
    TA in the lab suggested me steps to fix memory leak in this segment

*/
void ChildrenGame::moveChildren(double t) {
    LinkedList::Node* curr = children.getHead();
    LinkedList::Node* prev = nullptr; //pointer that keeps track of the previous node
    LinkedList::Node* newHead = nullptr;  //pointer that points to the new head of linked list

    if (t >= 0) {
        while (curr != nullptr) {
            /*
                CITATION:
                ChatGPT helped me with the syntax - line 142
                Referred ECE-150 course notes 
            */
            Child& child = curr->child; // this line gets a reference of the child store in current node

            //calculates new coordinates according to the child's current position and time parameters
            double newX = child.getX() - t * std::cos(std::atan2(child.getY(), child.getX()));
            double newY = child.getY() - t * std::sin(std::atan2(child.getY(), child.getX()));

            if (newX > 0 && newY > 0) {
                child = Child(newX, newY); //updating child's new position
                prev = curr; 
                curr = curr->next;
                if (newHead == nullptr) {
                    newHead = prev;
                }
            } else {
                LinkedList::Node* temp = curr; //storing current node in a temp pointer
                curr = curr->next; 
                children.removeNode(temp); //removing current node from linked list

                if (temp == children.getHead()) {
                    // Updating the head if the first node is removed
                    children.removeFront();
                }

            }
        }
    } else { //case when time parameter is negative
        while (curr != nullptr) {
            Child& child = curr->child; //gets reference to child stored in current node

            if (child.distanceToWolf() < 1.0) { //checking if child is within 1 meter of wolf
                LinkedList::Node* temp = curr;
                curr = curr->next;
                children.removeNode(temp); //removimg current node from linked list

                if (temp == children.getHead()) {
                    // Updating the head if the first node is removed
                    children.removeFront();
                }
            } else {
                prev = curr;        // updating previous node pointer
                curr = curr->next;
                if (newHead == nullptr) {
                    newHead = prev; 
                }
            }
        }
    }

    // Set the new head of the linked list if it has changed
    if (newHead != nullptr && newHead != children.getHead()) {
        children.removeFront(); // Removes the old head
        children.push_front(newHead->child); // Adds the new head
    }
}

//this function counts number of children with positive coordinates
int ChildrenGame::countChildren() const {
    int count = 0;
    LinkedList::Node* curr = children.getHead();

    while (curr != nullptr) {
        if (curr->child.getX() > 0 && curr->child.getY() > 0) {
            count++;
        }
        curr = curr->next;
    }

    return count;
}

// function that prints a result based on game outcomes // boolean parameters
void ChildrenGame::printResult(bool success) const {
    if (success) {
        std::cout << "success" << std::endl;
    } else {
        std::cout << "failure" << std::endl;
    }
}

// prints number of children still playing
void ChildrenGame::printResult(int numChildren) const {
    std::cout << "number of children still playing: " << numChildren << std::endl;
}

//function used to print coordinates of children within a distance D from the wolf
void ChildrenGame::PRT(double D) const {
    LinkedList::Node* curr = children.getHead(); //pointer pointing to head of childrens' linked list
    bool foundChildren = false;  // boolean flag

    while (curr != nullptr) {
        Child& child = curr->child; // gets a reference to the child stores in current node

        if (child.distanceToWolf() < D) {
            std::cout << child.getX() << " " << child.getY() << " "; //prints coordinates of child after checking if child is withing a distance D from wolf
            foundChildren = true; //set flag to true
        }

        curr = curr->next; // moving to next node of linked list
    }

    if (!foundChildren) {
        std::cout << "no children within distance";
    }

    std::cout << std::endl;
}


