#include "graph.hpp"
/*
CITATION:

ChatGPT helped me comment certain sections of this code.
*/
// Implementations for Edge class
//constructor
Edge::Edge() : destination(0), distance(0.0), speedLimit(0.0), adjF(1) {}

Edge::Edge(int dest, double dist, double speed) : destination(dest), distance(dist), speedLimit(speed), adjF(1){}

// Implementations for Vertex class
//constructor
Vertex::Vertex() : id(0), edges(nullptr), numEdges(0) {}

Vertex::Vertex(int vertexId) : id(vertexId), edges(nullptr), numEdges(0) {}

//destructor
Vertex::~Vertex() {
    delete[] edges;
}
/*
CITATION:

Referred Lab-0 code for my resizableArray class implementation
*/

// Implementations for resizableArray class

//constructor
resizableArray::resizableArray(int initCap) : currentCapacity(initCap), size(0) {
    array = new Vertex[initCap];
}

//destructor
resizableArray::~resizableArray() {
    delete[] array;
}

int resizableArray::getSize() {
    return size;
}

int resizableArray::getCapacity() {
    return currentCapacity;
}

Vertex& resizableArray::getAt(int indx) {
    if (indx < 0 || indx >= size) {
        std::cerr << "Index out of bounds." << std::endl;
    }
    return array[indx];
}

bool resizableArray::push(Vertex val) {
    if (size == currentCapacity - 1) {
        Vertex* newArray = new Vertex[currentCapacity * 2];
        for (int i = 0; i < size; i++)
            newArray[i] = array[i];
        currentCapacity *= 2;
        delete[] array;
        array = newArray;
    }

    array[size] = val;
    size++;
    return true;
}

void resizableArray::resize(int newSize) {
    if (newSize <= 0) {
        return;
    }

    if (newSize < currentCapacity) {
        if (newSize >= size) {
            Vertex* newArray = new Vertex[newSize];
            for (int i = 0; i < size; i++)
                newArray[i] = array[i];
            currentCapacity = newSize;
            delete[] array;
            array = newArray;
        }
    } else if (newSize > currentCapacity) {
        Vertex* newArray = new Vertex[newSize];
        for (int i = 0; i < size; i++)
            newArray[i] = array[i];
        currentCapacity = newSize;
        delete[] array;
        array = newArray;
    }
}

// Implementations for Graph class

//constructor
Graph::Graph(int initCapacity) : vertices(new resizableArray(initCapacity)) {}

Vertex& Graph::getVertexById(int id) {
    for (int i = 0; i < vertices->getSize(); ++i) {
        Vertex& vertex = vertices->getAt(i);
        if (vertex.id == id) {
            return vertex;
        }
    }

    vertices->push(Vertex(id));
    return vertices->getAt(vertices->getSize() - 1);
}

bool Graph::edgeExists(int from, int to) {
    auto& vertex = getVertexById(from);
    for (int i = 0; i < vertex.numEdges; ++i) {
        if (vertex.edges[i].destination == to) {
            return true;
        }
    }
    return false;
}

void Graph::addEdge(Vertex& vertexA, Vertex& vertexB, double d, double s) {
    Edge newEdgeToB(vertexB.id, d, s);
    Edge newEdgeToA(vertexA.id, d, s);

    Edge* tempEdgesA = new Edge[vertexA.numEdges + 1];
    for (int i = 0; i < vertexA.numEdges; ++i) {
        tempEdgesA[i] = vertexA.edges[i];
    }

    Edge* tempEdgesB = new Edge[vertexB.numEdges + 1];
    for (int i = 0; i < vertexB.numEdges; ++i) {
        tempEdgesB[i] = vertexB.edges[i];
    }

    tempEdgesA[vertexA.numEdges] = newEdgeToB;
    tempEdgesB[vertexB.numEdges] = newEdgeToA;

    delete[] vertexA.edges;
    delete[] vertexB.edges;

    vertexA.edges = tempEdgesA;
    vertexA.numEdges++;

    vertexB.edges = tempEdgesB;
    vertexB.numEdges++;
}


//INSERT FUNCTION
void Graph::insert(int a, int b, double d, double s) {
    if (a <= 0 || b <= 0 || a > 500000 || b > 500000 || d <= 0 || s <= 0) {
        throw illegal_exception();
    }

    Vertex& vertexA = getVertexById(a);
    Vertex& vertexB = getVertexById(b);

    if (edgeExists(a, b)) {
        for (int i = 0; i < vertexA.numEdges; ++i) {
            if (vertexA.edges[i].destination == b) {
                vertexA.edges[i].distance = d;
                vertexA.edges[i].speedLimit = s;
                break;
            }
        }
        for (int i = 0; i < vertexB.numEdges; ++i) {
            if (vertexB.edges[i].destination == a) {
                vertexB.edges[i].distance = d;
                vertexB.edges[i].speedLimit = s;
                break;
            }
        }


    } else {
        addEdge(vertexA, vertexB, d, s);
    }
}

//PRINT FUNCTION
void Graph::print(int a) {
    if (a <= 0 || a > 500000) {
        throw illegal_exception();
    }

    bool found = false;

    for (int i = 0; i < vertices->getSize(); ++i) {
        Vertex& vertexA = vertices->getAt(i);

        if (vertexA.id == a) {
            found = true;

            if (vertexA.numEdges == 0) {
                std::cout << std::endl;
            } else {
                for (int j = 0; j < vertexA.numEdges; ++j) {
                    std::cout << vertexA.edges[j].destination << " ";

                }
                std::cout << std::endl;
            }

            break;
        }
    }

    if (!found) {
        std::cout << "failure" << std::endl;
    }
}

//DELETE FUNCTION
void Graph::deleteVertex(int a) {
    if (a <= 0 || a > 500000) {
        throw illegal_exception();
    }

    bool found = false;
    int indexToDelete = -1;

    for (int i = 0; i < vertices->getSize(); ++i) {
        Vertex& currentVertex = vertices->getAt(i);

        if (currentVertex.id == a) {
            found = true;
            indexToDelete = i;

            delete[] currentVertex.edges;

            break;
        }
    }

    if (found) {
        for (int j = 0; j < vertices->getSize(); ++j) {
            if (j != indexToDelete) {
                Vertex& otherVertex = vertices->getAt(j);

                for (int k = 0; k < otherVertex.numEdges; ++k) {
                    if (otherVertex.edges[k].destination == a) {
                        for (int l = k; l < otherVertex.numEdges - 1; ++l) {
                            otherVertex.edges[l] = otherVertex.edges[l + 1];
                        }
                        --otherVertex.numEdges;

                        Edge* newEdges = new Edge[otherVertex.numEdges];
                        for (int l = 0; l < otherVertex.numEdges; ++l) {
                            newEdges[l] = otherVertex.edges[l];
                        }
                        delete[] otherVertex.edges;
                        otherVertex.edges = newEdges;
                        break;
                    }
                }
            }
        }

        for (int j = indexToDelete; j < vertices->getSize() - 1; ++j) {
            vertices->getAt(j) = vertices->getAt(j + 1);
        }

        vertices->resize(vertices->getSize() - 1);

        std::cout << "success" << std::endl;
    } else {
        std::cout << "failure" << std::endl;
    }
}

/*
CITATION:

ChatGPT helped me debug issues in TRAFFIC function, thereby changing small components of it.
*/

//TRAFFIC FUNCTION
bool Graph::traffic(int a, int b, double A) {
    if (a <= 0 || b <= 0 || a > 500000 || b > 500000) {
        throw illegal_exception();
    }

    Vertex& vertexA = getVertexById(a);
    Vertex& vertexB = getVertexById(b);

    bool edgeFound = false;
    bool change = false;
    bool changeB = false;
    if (A>=0 && A<=1){
        for (int i = 0; i < vertexA.numEdges; ++i) {
            if (vertexA.edges[i].destination == b) {
                //Update the adjustment factor
                //vertexA.edges[i].speedLimit *= (A >= 0 && A <= 1) ? A : 0;
                vertexA.edges[i].adjF = A;

                edgeFound = true;
                change = true;
            }
        }

        if (!edgeFound) {
            return false;
        }
    } else {
        return false;
    }if (A>=0 && A<=1){
        for (int i = 0; i < vertexB.numEdges; ++i) {
            if (vertexB.edges[i].destination == a) {
                //Update the adjustment factor
                //vertexA.edges[i].speedLimit *= (A >= 0 && A <= 1) ? A : 0;
                vertexB.edges[i].adjF *= A;

                edgeFound = true;
                changeB = true;
            }
        }

        if (!edgeFound) {
            return false;
        }
    } else {
        return false;
    }

    if(change && changeB){
    return true;
    }

    return false; 
    
}

//UPDATE function
bool Graph::update(const std::string& filename) {
    std::ifstream file(filename);
    int a, b;
    double A;

    bool c = false;

    while (file >> a >> b >> A) {
        if (traffic(a, b, A)) {
            c = true;
        }
    }

    if (c) {
        std::cout << "success" << std::endl;
    } else {
        std::cout << "failure" << std::endl;
    }

    return c;
}

/*
//ADJUSTMENT_FACTOR **FOR DEBUGGING PURPOSES ONLY**

double Graph::getAF(int a, int b){
    if (a <= 0 || b <= 0 || a > 500000 || b > 500000) {
        throw illegal_exception();
    }   

    Vertex& vertexA = getVertexById(a);

    for (int i = 0; i < vertexA.numEdges; ++i) {
        if (vertexA.edges[i].destination == b) {
            return vertexA.edges[i].speedLimit;
        }
    }

    throw std::runtime_error("Edge not found");
}

//END OF ADJUSTMENT_FACTOR **FOR DEBUGGING PURPOSES ONLY, comment it out later

*/

/*
CITATION:

ChatGPT helped me fix my memory leak issue by adding vertices = nullptr; in my Graph destructor
*/

//destructor
Graph::~Graph() {
    delete vertices;
    vertices = nullptr;
}


// DIJKSTRA FOR PATH


/*
CITATION:

Referred https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-priority_queue-stl/ for implementing 
DIJKSTRA's Algorithm
*/

// Implementing rsAI class

/*
CITATION:

Refered Lab-0 code for rsAI class and its implementation.
*/

//constructor
rsAI::rsAI() : size(0), capacity(2) {
    data = new int[capacity];
}

//destructor
rsAI::~rsAI() {
    delete[] data;
}

//Implementations of rsAI class
void rsAI::push_back(int value) {
    if (size == capacity) {
        // Resize the array by doubling its capacity
        int* newData = new int[capacity * 2];
        for (int i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity *= 2;
    }
    data[size++] = value;
}


int* rsAI::get_data() const {
    return data;
}

int rsAI::get_size() const {
    return size;
}

//constructor
PriorityQueue::PriorityQueue(int capacity) : size(0), capacity(capacity) {
    distances = new double[capacity];
    vertices = new int[capacity];
}

//destructor
PriorityQueue::~PriorityQueue() {
    delete[] distances;
    delete[] vertices;
}

// Implementations for PriorityQueue class

/*
CITATION:

Referred https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-priority_queue-stl/ for implementing 
the PriorityQueue.
ChatGPT helped me fix some errors in this class.
*/

bool PriorityQueue::empty() const {
    return size == 0;
}

void PriorityQueue::push(int vertex, double distance) {
    distances[size] = distance;
    vertices[size] = vertex;
    heapifyUp(size);
    size++;
}

int PriorityQueue::top() const {
    return vertices[0];
}

void PriorityQueue::pop() {
    if (size > 0) {
        size--;
        distances[0] = distances[size];
        vertices[0] = vertices[size];
        heapifyDown(0);
    }
}

void PriorityQueue::heapifyUp(int i) {
    while (i > 0 && distances[parent(i)] > distances[i]) {
        swap(i, parent(i));
        i = parent(i);
    }
}

void PriorityQueue::heapifyDown(int i) {
    int minIndex = i;
    int left = leftChild(i);
    int right = rightChild(i);

    if (left < size && distances[left] < distances[minIndex]) {
        minIndex = left;
    }

    if (right < size && distances[right] < distances[minIndex]) {
        minIndex = right;
    }

    if (i != minIndex) {
        swap(i, minIndex);
        heapifyDown(minIndex);
    }
}

void PriorityQueue::swap(int i, int j) {
    double tempDistance = distances[i];
    int tempVertex = vertices[i];

    distances[i] = distances[j];
    vertices[i] = vertices[j];

    distances[j] = tempDistance;
    vertices[j] = tempVertex;
}

int PriorityQueue::parent(int i) const {
    return (i - 1) / 2;
}

int PriorityQueue::leftChild(int i) const {
    return 2 * i + 1;
}

int PriorityQueue::rightChild(int i) const {
    return 2 * i + 2;
}

/*
CITATION:

ChatGPT helped me fix some errors in the PATH function, thereby changing parts of it.
*/
//PATH FUNCTION
void Graph::path(int sourceVertexId, int destinationVertexId) {
    if (sourceVertexId <= 0 || destinationVertexId <= 0 || sourceVertexId > 500000 || destinationVertexId > 500000) {
        throw illegal_exception();
    }

    int size = 500000;

    // Initialize distances and parents
    double* distances = new double[size];
    int* parents = new int[size];

    for (int i = 0; i < size; ++i) {
        distances[i] = 1.0 / 0.0;
        parents[i] = -1;  // Initialize all parents to -1
    }

    distances[sourceVertexId - 1] = 0;

    // Priority queue to store vertices with their distances
    PriorityQueue pq(size);
    pq.push(sourceVertexId, 0.0);

    while (!pq.empty()) {
        int currentVertexId = pq.top();
        pq.pop();

        // Update distances for adjacent vertices
        Vertex& currentVertex = getVertexById(currentVertexId);

        for (int i = 0; i < currentVertex.numEdges; ++i) {
            Edge& edge = currentVertex.edges[i];
            int neighborId = edge.destination;

            double newWeight = distances[currentVertexId - 1] + edge.distance / (edge.speedLimit * edge.adjF);

            // Consider the weight of the edge
            if (newWeight < distances[neighborId - 1]) {
                distances[neighborId - 1] = newWeight;
                parents[neighborId - 1] = currentVertexId;  // Update the parent
                pq.push(neighborId, newWeight);
            }
        }
    }

    // Reconstruct the path from destination to source
    rsAI path;
    int current = destinationVertexId;

    while (current != -1) {
        path.push_back(current);
        current = parents[current - 1];
    }

    // Print the path and the distance to the destination vertex
    double distanceToDestination = distances[destinationVertexId - 1];
    if (std::isinf(distanceToDestination)) {
        std::cout << "failure" << std::endl;
    } else {
        for (int i = path.get_size() - 1; i >= 0; --i) {
            std::cout << path.get_data()[i] << " ";
        }
        std::cout << std::endl;
    }

    delete[] distances;
    delete[] parents;
}

//LOWEST FUNCTION
void Graph::lowest(int sourceVertexId, int destinationVertexId) {
    if (sourceVertexId <= 0 || destinationVertexId <= 0 || sourceVertexId > 500000 || destinationVertexId > 500000) {
        throw illegal_exception();
    }

    int size = 500000;

    // Initialize distances
    double* distances = new double[size];
    for (int i = 0; i < size; ++i) {
        distances[i] = 1.0 / 0.0;
    }
    distances[sourceVertexId - 1] = 0;

    // Priority queue to store vertices with their distances
    PriorityQueue pq(size);
    pq.push(sourceVertexId, 0.0);

    while (!pq.empty()) {
        int currentVertexId = pq.top();
        pq.pop();

        // Update distances for adjacent vertices
        Vertex& currentVertex = getVertexById(currentVertexId);

        for (int i = 0; i < currentVertex.numEdges; ++i) {
            Edge& edge = currentVertex.edges[i];
            int neighborId = edge.destination;

            double newWeight = distances[currentVertexId - 1] + edge.distance / (edge.speedLimit * edge.adjF);

            // Consider the weight of the edge
            if (newWeight < distances[neighborId - 1]) {
                distances[neighborId - 1] = newWeight;
                pq.push(neighborId, newWeight);
            }
        }
    }

    // Print the distance to the destination vertex
    double distanceToDestination = distances[destinationVertexId - 1];
    if (std::isinf(distanceToDestination)) {
        std::cout << "failure" << std::endl;
    } else {
        std::cout << "lowest is " << distanceToDestination << std::endl;
    }

    delete[] distances;
}