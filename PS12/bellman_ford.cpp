#include <iostream>
#include <vector>
#include <stack>

class Edge {
public:
	int from, to, weight;
	Edge(int from, int to, int weight) {
		this->from = from;
		this->to = to;
		this->weight = weight;
	}
};

using namespace std;
template<class T> void print(vector<T> v) {
	for (int i = 1; i < v.size(); i++) {
		cout << v[i] << " ";
	}
	cout << "\n==========================\n"; 
}

int main(int argc, char const *argv[]) {
	int V = 5;
	int source = 5;
    const int inf = 100000;

	vector<Edge> edges = {Edge(1, 3, 6), Edge(1, 4, 3), 
						  Edge(2, 1, 3), Edge(3, 4, 2),
						  Edge(3, 1, -7), // To create a negative cycle.
						  Edge(4, 2, 1), Edge(4, 3, 1),
						  Edge(5, 2, 4), Edge(5, 4, 2)};
    
    // Create vectors of V + 1 to use 1-based indexing. We will ignore the first element of each vector.
    vector<int> distances(V + 1, inf);
    distances[source] = 0;
    cout << "Initial distances" << endl;
    print(distances);
    vector<int> predecessors(V + 1, -1);

    int nIter = 0;
    bool isUpdated = true; // Will be used for cycle detection.
    int lastUpdatedVertex = -1; // Will be used for cycle backtracking.
    // If the number of iterations is equal to V, then there is a cycle and we should stop iterating
    // If there is no update in an iteration, then the optimality is satisfied and we should again stop. 
    while (nIter < V && isUpdated) {
    	isUpdated = false;
    	for (Edge e : edges) {
    		if (distances[e.from] + e.weight < distances[e.to]) {
    			distances[e.to] = distances[e.from] + e.weight;
    			predecessors[e.to] = e.from;
    			isUpdated = true;
    			lastUpdatedVertex = e.to;
    			print(distances);
    		}
    	}
    	nIter++;
    }

    if (nIter == V && isUpdated) {
		cout << "Here is a negative cycle!" << endl;
		// Construct the cycle
		int parent = predecessors[lastUpdatedVertex];
		stack<int> cycle;
		cycle.push(lastUpdatedVertex);
		while (lastUpdatedVertex != parent) {
			cycle.push(parent);
			parent = predecessors[parent];
		}
		cycle.push(lastUpdatedVertex);
		
		// Print the cycle
		while (cycle.size() > 1) {
			cout << cycle.top() << "-";
			cycle.pop();
		}
		cout << cycle.top() << endl;
    }

    cout << "Final distances" << endl;
	print(distances);
	cout << "Final predecessors" << endl;
	print(predecessors);
	return 0;
}