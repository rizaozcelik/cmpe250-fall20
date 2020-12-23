//
// Created by cmpe250student on 21.12.2020.
//

#ifndef SEARCHALGO_GRAPHDJ_H
#define SEARCHALGO_GRAPHDJ_H
#include<set>
#include<list>
#include<vector>
#include<iostream>
#include<limits>

using namespace std;
const int INF = numeric_limits<int>::max();

class GraphDj {

private:
    int numberOfVertices; // No. of vertices
// Pointer to an array containing adjacency lists
    list< pair<int, int> > *adjacencyList;

public:
    GraphDj(int numberOfVertices);
    ~GraphDj();

    void addEdge(int u, int v, int w);

    void shortestPath(int src);

};


#endif //SEARCHALGO_GRAPHDJ_H
