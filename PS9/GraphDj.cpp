//
// Created by cmpe250student on 21.12.2020.
//

#include "GraphDj.h"

GraphDj::GraphDj(int numberOfVertices) {
    this->numberOfVertices = numberOfVertices;
    adjacencyList = new list< pair<int, int> >[numberOfVertices];
}

GraphDj::~GraphDj() {
    delete[] adjacencyList;
}

void GraphDj::addEdge(int u, int v, int w) {
    adjacencyList[u].push_back(make_pair(v, w));
    adjacencyList[v].push_back(make_pair(u, w));
}

void GraphDj::shortestPath(int src) {

    // Create a set to store vertices that are being
    // processed
    set< pair<int, int> > setds;

    // Create a vector for distances and initialize all
    // distances as infinite (INF)
    vector<int> dist(numberOfVertices, INF);


    // Insert source itself in Set and initialize its
    // distance as 0.
    setds.insert(make_pair(0, src));
    dist[src] = 0;

    // Looping till all shortest distance are finalized
    // then setds will become empty
    while (!setds.empty()) {

        // The first vertex in Set is the minimum distance
        // vertex, extract it from set.
        pair<int, int> tmp = *(setds.begin());
        setds.erase(setds.begin());

        // vertex label is stored in the second of pair (it
        // has to be done this way to keep the vertices
        // sorted distance (distance must be first item
        // in pair)
        int u = tmp.second;

        // ’i’ is used to get all adjacent vertices of a vertex
        list< pair<int, int> >::iterator i;
        for (i = adjacencyList[u].begin(); i != adjacencyList[u].end(); ++i) {

            // Get vertex label and weight of current adjacent
            // of u.
            int v = (*i).first;
            int weight = (*i).second;
            // If there is shorter path to v through u.
            if (dist[v] > dist[u] + weight) {

                // If distance of v is not INF then it must be in
                // our set, so removing it and inserting again
                // with updated shorter distance.
                // Note : We extract only those vertices from Set
                // for which distance is finalized. So for them,
                // we would never reach here.
                if (dist[v] != INF)
                    setds.erase(setds.find(make_pair(dist[v], v)));

                // Updating distance of v
                dist[v] = dist[u] + weight;
                setds.insert(make_pair(dist[v], v));
            }
        }
    }

    // Print shortest distances stored in dist[]
    cout<<"Vertex Distance from Source"<<endl;
    for (int i = 0; i < numberOfVertices; ++i)
        cout<<i<<" "<<dist[i]<<endl;
}
