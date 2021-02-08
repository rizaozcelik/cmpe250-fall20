#include <vector>
#include <climits>
#include <queue>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iterator>
#include <chrono>

using namespace std;

class Edge{
	public:
	int src, dest, weight;
};

int V;
vector<int> path;
vector<vector<Edge>> adj;


bool detectCycle(int *pr, int x){
	bool flag = false;
	int y = x;
	for(int i = 0; i < V-2; i++){
		y = pr[y];
		if(y == 0)return false;
	}
	for(int cur = y; ; cur = pr[cur]){
		path.push_back(cur);
		if(cur == y && path.size() > 1){
			flag = true;
			break;
		}
	}
	return flag;
}

bool bellman(){
	int nV = V - 2;
	int dist[V];
	for(int i = 0; i < V; i++) dist[i] = INT_MAX;
	dist[1] = 0;
	
	int pr[V];
	for(int i = 0; i < V; i++) pr[i] = 0;

	int x = 0;
	int flag = 0;
	bool bl = true;
	
	queue<int> q;
	bool inqueue[V] = {false};
	int count = 0;
	q.push(1);
	inqueue[1] = true;
	while(!q.empty()){
		int u = q.front();
		q.pop();
		inqueue[u] = false;
		for(int i = 0; i < adj[u].size(); i++){
			Edge e = adj[u][i];
			int v = e.dest;
			int weight = e.weight;
			if(dist[u] + weight < dist[v]){
				dist[v] = dist[u] + weight;
				pr[v] = u;
				x = v;
				count++;
				if(count == V-2){
					count = 0;
					bool cycle = detectCycle(pr,x);
					if(cycle == true){
						flag = 1;
						break;
					}
				}
				if(inqueue[v] == false){
					q.push(v);
					inqueue[v] = true;
				}
			}
		}
		if(flag == 1){
			break;
		}
	}
	if(flag == 0){
		bl = false;
	}
	return bl;
}


void costNetwork(int **rGraph, int **costs) {
	for(int i = 0; i < V; i++) {
		for(int j = 0; j < V; j++) {
			if(rGraph[i][j] == 1){
				if(i % 2 == 1 && j != 0 && i != V-1) {
					Edge nEdge;
					nEdge.src = i;
					nEdge.dest = j;
					nEdge.weight = -1 * costs[(i-1)/2][(j/2)-1];
					adj[i].push_back(nEdge);
				}else if(i % 2 == 0){
					Edge nEdge;
					nEdge.src = i;
					nEdge.dest = j;
					nEdge.weight = costs[(j-1)/2][(i/2)-1];
					adj[i].push_back(nEdge);
					break;
				}else {
					continue;
				}
			}
		}
	}
}


int** residualGraph() {
	int **rGraph = new int*[V];
	for(int i = 0; i < V; i++){
		rGraph[i] = new int[V];
	}
	for(int i = 0; i < V; i++) {
		for(int j = 0; j < V; j++) {
			if(i == 0 && j % 2 == 1 && j != V-1) {
				rGraph[i][j] = 1;
			}else if(i % 2 == 1 && i != V-1 && j % 2 == 0 && j != 0) {
				rGraph[i][j] = 1;
			}else if(i % 2 == 0 && j == V-1 && i != 0) {
				rGraph[i][j] = 1;
			}else {
				rGraph[i][j] = 0;
			}
		}
	}
	return rGraph;
}

bool bfs(int **rGraph, int s, int t, int *parent) { 
	bool visited[V] = {false}; 
	queue<int> q; 
	q.push(s); 
	visited[s] = true; 
	parent[s]=-1; 
	while (!q.empty()) { 
		int u = q.front(); 
		q.pop();
		for (int v = 0; v < V; v++) { 
			if (visited[v]==false && rGraph[u][v] > 0) { 
				q.push(v); 
				parent[v] = u; 
				visited[v] = true; 
			} 
		} 
	} 
	return (visited[t] == true); 
}

int minCost(int **costs) {
	int **rGraph = residualGraph();
		
	int parent[V];
	for(int i = 0; i < V; i++) parent[i] = 0;
	
	while (bfs(rGraph, 0, V-1, parent)) {
		for (int v = V-1; v != 0; v=parent[v]) { 
			int u = parent[v]; 
			rGraph[u][v] -= 1; 
			rGraph[v][u] += 1; 
		} 
	} 
	costNetwork(rGraph,costs);	
	while(bellman()) {
		for(int i = path.size()-1; i > 0; i--) {
			int u = path[i];
			int v = path[i-1];
			rGraph[u][v] -= 1; 
			rGraph[v][u] += 1;
		}
		path.clear();
		for(int i = 0; i < 400; i++) {
			adj[i].clear();
		}
		costNetwork(rGraph,costs);
	}
	int cost = 0;
	for(int i = 2; i < V; i = i + 2) {
		for(int j = 1; j < V; j = j + 2) {
			if(rGraph[i][j] == 1) {
				cost += costs[j/2][(i-1)/2];
				j = V;
			}
		}
	}
	for(int i = 0; i < V; i++){
		delete[] rGraph[i];
	}
	delete[] rGraph;
	return cost;
} 

int main(int argc, char* argv[]){
	auto t1 = std::chrono::high_resolution_clock::now();
	string line;
	
	ifstream infile(argv[1]);
	ofstream outfile(argv[2]);
	
	getline(infile,line);
	int testCount = stoi(line);
	for(int j = 0; j < testCount; j++){
		adj.clear();
		for(int i = 0; i < 400; i++){
			vector<Edge> vect;
			adj.push_back(vect);
		}
		getline(infile,line);
		int v = stoi(line);
		V = 2 * v + 2;
		int **costs = new int*[v];
		for(int i = 0; i < v; i++){
			costs[i] = new int[v];
		}		
		string str;
		int x;
		for(x = 0; x < v; x++){
			getline(infile,line);
			istringstream buf(line);
			istream_iterator<string> beg(buf), end;
			vector<string> integers(beg,end);
			for(int i = 0; i < integers.size(); i++){
				costs[x][i] = stoi(integers[i]);
			}
		}
		outfile<<minCost(costs)<<endl;
		//cout << minCost(costs)<< endl;
		for(int i = 0; i < v; i++){
			delete[] costs[i];
		}
		delete[] costs;
	}
	auto t2 = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
	float dur =  duration / 1000000.0;
	cout << dur << endl;
}

