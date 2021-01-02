#include "utils.cpp"

// Finds an augmenting path from source to target in the residual graph. Uses DFS to find the path.
AugmentingPath findAugmentingPath(unordered_map<string, Vertex>& residualGraph, string sourceName, string targetName, string notReached="X") {
	// Will be used to construct the path from source to target, when the target is reached.
	unordered_map<string, string> reachedFrom;
	for (auto v: residualGraph) {
		reachedFrom[v.first] = notReached;
	}

	// This block is the DFS implementation and track where each vertex is reached from.
    stack<string> dfsStack;
    dfsStack.push(sourceName);
    while(!dfsStack.empty() && reachedFrom[targetName] == notReached) {
        string currentVertex = dfsStack.top();
        dfsStack.pop();
        for (auto edge: residualGraph[currentVertex].adjacencyMap) {
        	string toName = edge.first;
            if (reachedFrom[toName] == notReached) {
                reachedFrom[toName] = currentVertex;
                dfsStack.push(toName);
            }
        }
    }

    // If the target is not reached, return an empty path.
    if (reachedFrom[targetName] == notReached) {
    	return AugmentingPath();
    }

    // Backtrack from the target to construct the path. Use a stack to store the path for "LIFO" property.
    // Also find the minimum capacity (bottleneck) along the path to decide the amount of flow.
    int minCapacity = numeric_limits<int>::max();
	stack<string> path;
	string childName = targetName;
	while (childName != sourceName) {
		path.push(childName);
		string parentName = reachedFrom[childName];
		minCapacity = min(minCapacity, residualGraph[parentName].adjacencyMap[childName]);
		childName = parentName;
	}
	path.push(sourceName);
	return AugmentingPath(minCapacity, path);
}

// Update the residual graph to realize the augmentation. The path is stored as a path, so the first popped element is the source.
void augment(unordered_map<string, Vertex>& residualGraph, AugmentingPath augmentingPath) {
	int amount = augmentingPath.amount;
	stack<string> path = augmentingPath.path;
	cout << "Augmenting " << amount << " along ";
	while (path.size() > 1) {
		string fromVertex = path.top();
		path.pop();
		string toVertex = path.top();

		// Decrease the forward capacity and delete the edge if the remaining capacity is 0.
		int fwdCapacity = residualGraph[fromVertex].adjacencyMap[toVertex];
		int remainingCapacity = fwdCapacity - amount;
		cout << fromVertex << " - ";

		if (remainingCapacity == 0) {
			residualGraph[fromVertex].adjacencyMap.erase(toVertex);
		} else {
			residualGraph[fromVertex].adjacencyMap[toVertex] = remainingCapacity;
		}

		// Add a backward edge or increment its capacity if it already exists. 
		// Note: at(val) returns an exception if val is not in the unordered_map.
		try {
			// There is already an edge. Increment the capacity
			residualGraph[toVertex].adjacencyMap.at(fromVertex) += amount;
		} catch (const std::out_of_range& oor) {
			// Add an edge.
			residualGraph[toVertex].adjacencyMap[fromVertex] = amount;
		}
	}
	cout << path.top() << endl;
}


// Run Ford-Fulkerson algorithm to find the maximum flow in a graph.
int fordFulkerson(unordered_map<string, Vertex>& graph, string sourceName, string targetName) {
	string notReachedFlag = "X";
	unordered_map<string, Vertex> residualGraph = graph;
	cout << "Initial residual graph:\n" ;
	printGraph(residualGraph);

	int maxFlow = 0, i = 0;
	// Augment until no path is left.
	bool isAugmentingPathLeft = true;
	while (isAugmentingPathLeft) {
		AugmentingPath augmentingPath = findAugmentingPath(residualGraph, sourceName, targetName, notReachedFlag);

		if (augmentingPath.amount > 0) {
			augment(residualGraph, augmentingPath);
			maxFlow = maxFlow + augmentingPath.amount;
			i++;
			cout << "Residual graph at iteration: " << i << endl;
			printGraph(residualGraph);
		} else {
			isAugmentingPathLeft = false;			
		}
	} 

	return maxFlow;
}

int main(int argc, char const *argv[]) {
	unordered_map<string, Vertex> graph;
	string names[6] = {"s", "a", "b", "c", "d", "t"};
	for (int i = 0; i < 6; i++) {
		string name = names[i];
		graph[name] = Vertex(name);
	}

	graph["s"].addEdge("a", 10);
	graph["s"].addEdge("b", 20);
	
	graph["a"].addEdge("d", 5);
	graph["a"].addEdge("c", 15);	

	graph["b"].addEdge("d", 8);

	graph["c"].addEdge("t", 30);
	graph["d"].addEdge("t", 12);

	cout << "Maximum flow is: " << fordFulkerson(graph, "s", "t") << endl;
	return 0;
}