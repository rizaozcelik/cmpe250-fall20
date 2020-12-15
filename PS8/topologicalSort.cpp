#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

typedef pair<int, int> Edge;

class Vertex {
public:
	vector<int> adjacencyList;
	int inDegree;
	int ID;

	Vertex(int ID) {
		this->ID = ID;
		this->inDegree = 0;
	};	

	void addEdge(Vertex& v) {
		this->adjacencyList.push_back(v.ID);
		v.inDegree++;
	}
};

vector<Edge> generateDAGEdges(int nVertices, int nEdges) {
	vector<Edge> edgeList(nEdges);
	for (int i = 0; i < nEdges; i++) {
		int from = rand() % (nVertices - 1);
		int to = 1 + from + (rand() % (nVertices - from - 1));
		edgeList[i] = Edge(from, to);
	}
	return edgeList;

}

vector<Vertex> createGraph(int V, vector<Edge> edgeList) {
	vector<Vertex> graph;
	for (int i = 0; i < V; i++) {
		graph.push_back(Vertex(i));
	}

	for (auto edge : edgeList) {
		int from = edge.first;
		int to = edge.second;
		graph[from].addEdge(graph[to]);
	}
	return graph;
}

vector<int> topologicalSort(vector<Vertex> graph) {
	queue<int> freeVertexIDs;
	for (auto vertex: graph) {
		if (vertex.inDegree == 0) {
			freeVertexIDs.push(vertex.ID);
		}
	}

	vector<int> topologicalOrder;
	while (freeVertexIDs.size() > 0) {
		int nextFreeVertexID = freeVertexIDs.front();
		freeVertexIDs.pop();
		topologicalOrder.push_back(nextFreeVertexID);
		for (auto vertexID: graph[nextFreeVertexID].adjacencyList) {
			graph[vertexID].inDegree--;
			if (graph[vertexID].inDegree == 0) {
				freeVertexIDs.push(vertexID);
			}
		}
	}
	
	if (topologicalOrder.size() != graph.size()) {
		cout << "There is no topological order. The graph is not a DAG!" << endl;
	} 

	for(auto vertexID : topologicalOrder) {
		cout << vertexID << " ";
	}
	cout << endl;
	
	return topologicalOrder;
}

bool checkTopoOrder(const vector<Edge>& edgeList, const vector<int>& topologicalOrder) {
	unordered_map<int, int> vertexIDToTopoOrder;
	for (int i = 0; i < topologicalOrder.size(); i++) {
		vertexIDToTopoOrder[topologicalOrder[i]] = i;
	}

	for (auto edge : edgeList) {
		int from = edge.first;
		int to = edge.second;
		auto fromTopoOrder = vertexIDToTopoOrder.find(from);
		auto toTopoOrder = vertexIDToTopoOrder.find(to);

		if (fromTopoOrder == vertexIDToTopoOrder.end() ||
			toTopoOrder == vertexIDToTopoOrder.end() ||
			fromTopoOrder->second > toTopoOrder->second) {
			cout << "This is not a topological sort!" << endl;
			return false;
		}

	}
	cout << "This seems as a perfect topological sort!" << endl;
	return true;
}

int main(int argc, char const *argv[]) {
	vector<Edge> edgeListDAG = {Edge(0, 1), Edge(0, 2), Edge(0, 3),
								Edge(1, 3), Edge(1, 4),
								Edge(2, 5),
								Edge(3, 2), Edge(3, 5), Edge(3, 6),
								Edge(4, 3), Edge(4, 6), 
								Edge(6, 5)};

	vector<Vertex> dag = createGraph(7, edgeListDAG);
	vector<int> topologicalOrderDAG = topologicalSort(dag);
	checkTopoOrder(edgeListDAG, topologicalOrderDAG);


	vector<Edge> edgeListCyclic(edgeListDAG);
	edgeListCyclic.push_back(Edge(6, 2)); // Does not create cycle
	edgeListCyclic.push_back(Edge(6, 3));

	vector<Vertex> cyclicGraph = createGraph(7, edgeListCyclic);
	vector<int> topologicalOrderCyclic = topologicalSort(cyclicGraph);
	checkTopoOrder(edgeListCyclic, topologicalOrderCyclic);
	

	int V = 1000000;
	int E = 9000000;
	vector<Edge> randomEdges =  generateDAGEdges(V, E);
	vector<Vertex> randomGraph = createGraph(V, randomEdges);
	vector<int> topologicalOrderRandom = topologicalSort(randomGraph);	
	checkTopoOrder(randomEdges, topologicalOrderRandom);

	return 0;
}