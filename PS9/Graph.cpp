//
// Created by cmpe250student on 20.12.2020.
//

#include "Graph.h"

using namespace std;

Graph::Graph(int numberOfVertices) {

    this->numberOfVertices = numberOfVertices;
    adjacencyList = new list<int>[numberOfVertices];
}

Graph::~Graph() {
    delete[] adjacencyList;
}

void Graph::addEdge(int v, int w) {
    adjacencyList[v].push_back(w); // Add w to v’s list.
}

void Graph::dfs(int s) {

    // Mark all the vertices as not visited
    bool visited[numberOfVertices];

    for(int i = 0; i < numberOfVertices; i++)
        visited[i] = false;

    // Create a stack for DFS
    stack<int> q;

    // Mark the current node as visited and push it
    visited[s] = true;
    q.push(s);


    // ’i’ will be used to get all adjacent
    // vertices of a vertex
    list<int>::iterator i;

    while(!q.empty()) {

        // Get top vertex from stack and print it
        s = q.top();

        cout << s << " ";
        q.pop();

        // Get all adjacent vertices of the popped
        // vertex s. If an adjacent has not been visited,
        // then mark it visited and push it
        for (i = adjacencyList[s].begin(); i != adjacencyList[s].end(); ++i) {
            if (!visited[*i]) {
                visited[*i] = true;
                q.push(*i);
            }
        }
    }
}

void Graph::breadthFirstSearch(int s) {

    // Mark all the vertices as not visited
    bool visited[numberOfVertices];

    for(int i = 0; i < numberOfVertices; i++)
        visited[i] = false;

    // Create a queue for BFS
    queue<int> q;

    // Mark the current node as visited and enqueue it
    visited[s] = true;
    q.push(s);


    // ’i’ will be used to get all adjacent
    // vertices of a vertex
    list<int>::iterator i;
    while(!q.empty()) {

        // Dequeue a vertex from queue and print it
        s = q.front();
        cout << s << " ";
        q.pop();

        // Get all adjacent vertices of the dequeued
        // vertex s. If an adjacent has not been visited,
        // then mark it visited and enqueue it
        for (i = adjacencyList[s].begin(); i != adjacencyList[s].end(); ++i) {
            if (!visited[*i]) {
                visited[*i] = true;
                q.push(*i);
            }
        }
    }
}

void Graph::traverse(int v, bool visited[]) {

    // Mark the current node as visited and
    // print it

    visited[v] = true;
    cout << v << " ";

    // Recur for all the vertices adjacent
    // to this vertex
    list<int>::iterator i;
    for (i = adjacencyList[v].begin(); i != adjacencyList[v].end(); ++i)
        if (!visited[*i])
            traverse(*i, visited);
}

void Graph::depthFirstSearch(int v) {
// Mark all the vertices as not visited
    bool visited[numberOfVertices];
    for (int i = 0; i < numberOfVertices; i++)
        visited[i] = false;
// Call the recursive helper function
// to print DFS traversal
    traverse(v, visited);
}

