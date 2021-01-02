#include <iostream>
#include <unordered_map>
#include <string>
#include <stack>
#include <limits>
using namespace std;


class Vertex {
public:
	string name;
	unordered_map<string, int> adjacencyMap;

	Vertex(string name="") {
		this->name = name;
	}

	void addEdge(string name, int capacity) {
		adjacencyMap[name] = capacity;
	}

};

ostream& operator<<(ostream& os, const Vertex v) {
	for (auto map: v.adjacencyMap) {
		os << map.first << " " << map.second << " ";
	}
	os << endl;
	return os;
}

class AugmentingPath {
public:
	int amount;
	stack <string> path;

	AugmentingPath() {
		this->amount = -1;
	}

	AugmentingPath(int amount, stack<string> path) {
		this->amount = amount;
		this->path = path;
	}
};


void printGraph(unordered_map<string, Vertex>& g) {
	for (auto v: g) {
		cout << v.first << " " << v.second;
	}
}

void printPath(stack<string> path) {
	cout << "Found path: ";
	while (path.size() > 0) {
		cout << path.top() << " ";
		path.pop();
	}
	cout << endl;
}
