/*
    CITATION:
    ChatGPT helped me generate the header file

*/

#include <iostream>
#include <cmath>

class Child {
private:
    double x, y;

public:
    Child(double x, double y);
    double getX() const;
    double getY() const;
    double distanceToWolf() const;
};

/*
    CITATION:
    ChatGPT helped me with the formatting of nested Node class within LinkedList class
*/
class LinkedList {
public:
    class Node {
    public:
        Child child;
        Node* next;

        Node(Child child);
    };

private:
    Node* head;

public:
    LinkedList();
    bool isEmpty() const;
    void push_front(Child child);
    void removeNode(Node* target);
    Node* getHead() const;
    ~LinkedList();
    void removeFront();
    Child getFront() const;
};

class ChildrenGame {
private:
    LinkedList children;

public:
    bool spawnChild(double x, double y);
    void moveChildren(double t);
    int countChildren() const;
    void printResult(bool success) const;
    void printResult(int numChildren) const;
    void PRT(double D) const;
};