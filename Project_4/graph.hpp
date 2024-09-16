/*
CITATION:

This header file was generated by the assistance of chat.openai.com with the prompt: 
"can you split my code into graph.cpp with the implementations, graph.hpp the header file and main.cpp please?"
*/

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <cmath>
#include <fstream>

/*
CITATION:

Referred my own Lab-3 code for illegal_exception class
*/

class illegal_exception : public std::exception {
public:
    const char* what() const throw() {
        return "illegal argument";
    }
};

class Edge {
public:
    int destination;
    double distance;
    double speedLimit;
    double adjF;
    Edge();
    Edge(int dest, double dist, double speed);
};

class Vertex {
public:
    int id;
    Edge* edges;
    int numEdges;
    Vertex();
    Vertex(int vertexId);
    ~Vertex();
};

class resizableArray {
private:
    Vertex* array;
    int size;
    int currentCapacity;

public:
    resizableArray(int initCap);
    ~resizableArray();
    int getSize();
    int getCapacity();
    Vertex& getAt(int indx);
    bool push(Vertex val);
    void resize(int newSize);
};

class Graph {
private:
    resizableArray* vertices;    
    const double SUB_INFINITY = INFINITY;
    Vertex& getVertexById(int id);
    bool edgeExists(int from, int to);
    void addEdge(Vertex& vertexA, Vertex& vertexB, double d, double s);

public:
    Graph(int initCapacity = 500000);
    void insert(int a, int b, double d, double s);
    void print(int a);
    void deleteVertex(int a);
    bool traffic(int a, int b, double A);
    void path(int a, int b);
    bool update(const std::string& filename);
    void lowest(int sourceVertexId, int destinationVertexId);
    //double getAF(int a, int b); //**FOR DEBUGGING PURPOSES ONLY**
    ~Graph();
};

class rsAI {
public:
    rsAI();
    ~rsAI();
    void push_back(int value);
    int* get_data() const;
    int get_size() const;

private:
    int* data;
    int size;
    int capacity;
};

class PriorityQueue {
public:
    PriorityQueue(int capacity);
    ~PriorityQueue();
    bool empty() const;
    void push(int vertex, double distance);
    int top() const;
    void pop();

private:
    void heapifyUp(int i);
    void heapifyDown(int i);
    void swap(int i, int j);
    int parent(int i) const;
    int leftChild(int i) const;
    int rightChild(int i) const;

private:
    int size;
    int capacity;
    double* distances;
    int* vertices;
};

#endif