#include <iostream>
#include "Graph.h"
#include "GraphDj.h"


int main() {
    // Create a graph given in the above diagram
    // Create a graph
    Graph g(7);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 6);
    g.addEdge(2, 3);
    g.addEdge(2, 1);
    g.addEdge(3, 1);
    g.addEdge(3, 2);
    g.addEdge(3, 6);
    g.addEdge(3, 5);
    g.addEdge(3, 4);
    g.addEdge(4, 1);
    g.addEdge(4, 3);
    g.addEdge(4, 5);
    g.addEdge(5, 3);
    g.addEdge(5, 4);
    g.addEdge(6, 2);
    g.addEdge(6, 3);
    cout << "Following is Depth First Traversal"
         << " (starting from vertex 1)" << endl;
    g.depthFirstSearch(1);
    cout << "Second one:" << endl;
    g.dfs(1);
    cout << endl;
    cout << "Following is Breadth First Traversal "
         << "(starting from vertex 2) \n";
    g.breadthFirstSearch(2);

    GraphDj graph(6);

    graph.addEdge(0, 1, 2);
    graph.addEdge(0, 2, 4);
    graph.addEdge(1, 2, 81);
    graph.addEdge(1, 3, 4);
    graph.addEdge(1, 4, 2);
    graph.addEdge(2, 4, 3);
    graph.addEdge(3, 5, 2);
    graph.addEdge(4, 3, 3);
    graph.addEdge(4, 5, 2);

    graph.shortestPath(0);

    return 0;

}