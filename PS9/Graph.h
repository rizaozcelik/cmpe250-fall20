//
// Created by cmpe250student on 20.12.2020.
//

#ifndef SEARCHALGO_GRAPH_H
#define SEARCHALGO_GRAPH_H
#include<iostream>
#include <list>
#include <queue>
#include <stack>

using namespace std;

class Graph {

private:

    int numberOfVertices; // No. of vertices

    // Pointer to an array containing adjacency lists
    list<int> *adjacencyList;
    void traverse(int v, bool visited[]);

public:
    Graph(int numberOfVertices);

    ~Graph();

    void addEdge(int v, int w) ;
    void breadthFirstSearch(int s);
    void depthFirstSearch(int v);
    void dfs(int v);
};


#endif //SEARCHALGO_GRAPH_H
