#include <iostream>
#include <fstream>
#include <vector>
#include <forward_list>
#include <unordered_map>
#include "Vertex.h"
using namespace std;


int main(int argc, char const *argv[]) {
	ifstream infile(argv[1]);
	int V;
	infile >> V;

	int E = 0;
	vector<Vertex> graph;
	for (int i = 0; i < V; i++) {
		graph.push_back(Vertex(i));
	}

	vector<int> indegrees(V);
	for (int i = 0; i < V; i++) {
		int vertexID, outdegree;
		infile >> vertexID >> outdegree;
		for (int i = 0; i < outdegree; i++) {
			int to;
			infile >> to;
			graph[vertexID].addEdge(to);
			E++;
			indegrees[to]++;
		}
	}

	ofstream outfile(argv[2]);
	for (int vID = 0; vID < V; vID++) {
		if (graph[vID].nRemainingEdges != indegrees[vID]) {
			outfile << "no path";
			outfile.close();
			return 0;
		}

	}

	int startingVertexID;
	infile >> startingVertexID;
	infile.close();


	forward_list<Vertex*> circuit;
	Vertex* v = &(graph[startingVertexID]);
	auto circuitIt = circuit.before_begin();

	int circuitSize = 1;
	circuitIt = circuit.insert_after(circuitIt, v);
	while (circuitSize < E ) {
		forward_list<Vertex*> tour;
		auto tourIt = tour.before_begin();
		while (v->nRemainingEdges > 0) {
			int nextVertexID = v->adjacencyList.front();
			v->adjacencyList.pop();
			v->nRemainingEdges--;
			v = &(graph[nextVertexID]);
			tourIt = tour.insert_after(tourIt, v);
			circuitSize++;
		}

		auto insertionPoint = circuitIt;
		circuit.splice_after(insertionPoint, tour);
		
		while (circuitSize < E + 1  && (*circuitIt)->nRemainingEdges == 0) {
			circuitIt++;
		}
		v = *circuitIt;
	}

	
	for (auto vp : circuit) {
		outfile << vp->ID << " ";
	}
	outfile.close();

	return 0;
}