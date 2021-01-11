#include <queue>

using namespace std;

#ifndef Vertex_H
#define Vertex_H 

class Vertex {
public:
	queue<int> adjacencyList;
	int ID, nRemainingEdges;
	Vertex(int ID);
	void addEdge(int vID);
};

#endif
