#include <iostream>
#include <vector>

using namespace std;

class Edge {
public:
	int from, to, weight;
	Edge(int from, int to, int weight) {
		this->from = from;
		this->to = to;
		this->weight = weight;
	}
};

// A pretty print function for distances array
void print(int** arr, int V, const int INF) {
	cout << "  ";
	for (int i = 1; i <= V; i++) {
		cout << i << "\t";
	}

	cout << endl;
	for (int i = 1; i <= V; i++) {
		cout << i << " ";
		for (int j = 1; j <= V; j++) {
			if (arr[i][j] == INF) {
				cout << "INF" << "\t";
			}
			else {
				cout << arr[i][j] << "\t";				
			}
		}
		cout << '\n';
	}
	cout << "\n=========================================\n"; 
}

int main(int argc, char const *argv[]) {
	// Store the graph as a list of edges
	vector<Edge> edges = {Edge(1, 3, 6), Edge(1, 4, 3), 
						  Edge(2, 1, 3), Edge(3, 4, 2),
						  Edge(4, 2, 1), Edge(4, 3, 1),
						  Edge(5, 2, 4), Edge(5, 4, 2)};

	// Set a tighter bound on the maximum distance than int::max.					
	int INF = 0;
	for (Edge e : edges) {
		if (e.weight > 0) {
			INF += e.weight;
		}
	}

	// Create the distances array. We omit the 0th index and start vertex indexing from 1.
	int V = 5;
	int** distances = new int*[V + 1];
	for (int i = 0; i < V + 1; i++) {
		distances[i] = new int[V + 1];
	}

	// Initialize the distances
	for (int i = 0; i < V + 1; i++) {
		for (int j = 0; j < V + 1; j++) {
			if (i == j) {
				distances[i][j] = 0;
			} else {
				distances[i][j] = INF;				
			}
		}
	}

	for (Edge e : edges) {
		distances[e.from][e.to] = e.weight;
	}

	cout << "Initial distances:\n";
	print(distances, V, INF);

	// Find the distances through {1, 2, ... k}.
	for (int k = 1; k <= V; k++) {
		for (int i = 1; i <= V; i++) {
			for (int j = 1; j <= V; j++) {
				if (distances[i][k] + distances[k][j] < distances[i][j]) {
					distances[i][j] = distances[i][k] + distances[k][j];
					cout << "Found a shorter path from " << i << " to "<< j << " through "<< k << endl;
					print(distances, V, INF);
				}
			}
		}
	}

	// Free heap to prevent memory leak.
	for (int i = 0; i < V + 1; i++) {
		delete[] distances[i];
	}
	delete[] distances;
	
	return 0;
}