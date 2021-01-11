#include "Vertex.h"

Vertex::Vertex(int ID) {
	this->ID = ID;
	this->nRemainingEdges = 0;
}

void Vertex::addEdge(int vID) {
		this->adjacencyList.push(vID);
		this->nRemainingEdges++;
}	