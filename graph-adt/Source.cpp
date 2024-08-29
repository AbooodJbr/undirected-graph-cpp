#include <iostream>
#include <list>
#include <set>
using namespace std;

class Node {
    int val;
    list<Node*> adjacent;
public :
    friend class Graph;
    Node(int num) : val(num) {}
    void removeAdjacent(Node* temp) {
        adjacent.remove(temp);
    }
    bool isAdjacent(int num) {
        for (auto node : adjacent) {
            if (node->val == num) {
                return true;
            }
        }
        return false;
    }
};

class Graph {
private :
    list<Node*> nodeList;
    set<int> vertices;
    int vertexCount;

public :
    Graph() : vertexCount(0) {}

    ~Graph() {
        for (auto node : nodeList) {
            delete node;
        }
    }
    Node* insertVertex(int num) {
        if (vertices.find(num) == vertices.end()) {
            vertices.insert(num);
            Node* newNode = new Node(num);
            nodeList.push_back(newNode);
            vertexCount++;
            return nodeList.back();
        }
        return NULL;
    }
    Node* findVertex(int num) {
        for (auto vertex : nodeList) {
            if (vertex->val == num) return vertex;
        }
        return NULL;
    }

    bool removeVertex(int num) {
        Node* target = findVertex(num);
        if (!target) return false;
        else {
            for (auto vertex : nodeList) {
                vertex->removeAdjacent(target);
            }
            nodeList.remove(target);
            vertices.erase(num);
            vertexCount--;
            delete target;
            return true;
        }
        return false;
    }

    void insertEdge(int u, int v) {
        Node* src = findVertex(u);
        if (!src) {
            src = insertVertex(u);
        }
        if (u == v) {
            if (src && !src->isAdjacent(u)) {
                src->adjacent.push_back(src);
            }
        }
        else {
            Node* dest = findVertex(v);
            if (!src) {
                src = insertVertex(u);
            }
            if (!dest) {
                dest = insertVertex(v);
            }

            if (src && !src->isAdjacent(v)) {
                src->adjacent.push_back(dest);
            }
            if (dest && !dest->isAdjacent(u)) {
                dest->adjacent.push_back(src);
            }
        }
    }

    bool removeEdge(int u, int v) {
        Node* src = findVertex(u);
        Node* dest = findVertex(v);
        if (src && dest) {
            src->removeAdjacent(dest);
            dest->removeAdjacent(src);  
            return true;
        }
        return false;
    }
    
    void printGraph() const {
        cout << "\nthis graph has " << vertexCount << " vertices " << endl;
        for (const auto& vertex : nodeList) {
            cout << "vertex " << vertex->val;
            for (auto adj : vertex->adjacent) {
                if (adj == vertex->adjacent.front()) {
                    cout << " -> [ ";
                }
                if (adj != vertex->adjacent.back()) {
                    cout << adj->val << " , ";
                } else {
                    cout << adj->val << " ]";
                }
            }
            cout << endl;
        }
    }
};

int main() {
    Graph graph;

    // insert vertices
    graph.insertVertex(1);
    graph.insertVertex(2);
    graph.insertVertex(3);

    // to make sure that it doesnt add the same node twice
    graph.insertVertex(3);

    // insert edges
    graph.insertEdge(1, 2);
    graph.insertEdge(2, 3);
    graph.insertEdge(2, 5);
    graph.insertEdge(2, 4);
    graph.insertEdge(6, 3);
    graph.insertEdge(7, 8);

    // to make sure that it doesnt add the same edge twice
    graph.insertEdge(7, 8);

    // removing an edge
    graph.removeEdge(2, 3);

    // removing a vertex
    graph.removeVertex(7);

    // print graph
    graph.printGraph();

    return 0;
}

