#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm>  
#include "Heap.h" // Implemented by Rıza Özçelik and usage permission is retrieved.
#include <bits/stdc++.h> 
#include <time.h>    

using namespace std;


class Edge{
    public:
    int vertex1,vertex2,weight;

    Edge(){// for Heap
        this->vertex1 = 0;
        this->vertex2 = 0;
        this->weight = 0;
    }
    
    Edge(int vertex1,int vertex2, int weight){
        this->vertex1 = vertex1;
        this->vertex2 = vertex2;
        this->weight = weight;
    }

    bool operator<(const Edge& another_edge) const{
        return this->weight < another_edge.weight;
    }


    bool operator>(const Edge& another_edge) const{
        return this->weight > another_edge.weight;
    }
};

ostream& operator<<(ostream& os, const Edge& edge){
    os <<"("<<edge.vertex1+1<<"-"<<edge.vertex2+1<<")"; 
    return os;
}

int find(vector<int>& forest, int element){
    if(forest[element] < 0) return element;
    forest[element] = find(forest, forest[element]);
    return forest[element];
}

void union_size(vector<int>& forest, int root1, int root2){
    if(forest[root1] < forest[root2]){
        forest[root1] += forest[root2];
        forest[root2] = root1;
    }
    else{
        forest[root2] += forest[root1];
        forest[root1] = root2;
    }
}

void union_height(vector<int>& forest, int root1, int root2){
    if(forest[root1] < forest[root2]){
        forest[root2] = root1;
    }
    else if(forest[root2]< forest[root1]){
        forest[root1] = root2;
    }
    else{
        forest[root1] = root2;
        forest[root2] -= 1;
    }
}

void KruskalMST(vector<Edge>& edge_list,int number_of_vertices){

Heap<Edge> edges(edge_list);

vector<Edge> tree;
int min_cost = 0;

vector<int> forest;
for(int i=0;i<number_of_vertices;i++){
    forest.push_back(-1);
}

while(tree.size() != number_of_vertices -1){
    Edge pot_edge = edges.top();
    edges.pop();

    int root1 = find(forest, pot_edge.vertex1);
    int root2 = find(forest, pot_edge.vertex2);

    if(root1 != root2){
        union_height(forest,root1,root2);
        min_cost += pot_edge.weight;
        tree.push_back(pot_edge);
    }
}
cout<<min_cost<<endl;
for(int i=0;i<tree.size();i++){
    cout<<tree[i]<<endl;
}


}


int main(int argc, char const *argv[]) {
    vector<Edge> edge_list{Edge(0,1,2),
    Edge(0,2,4),
    Edge(0,3,1),
    Edge(1,3,3),
    Edge(1,4,10),
    Edge(2,3,2),
    Edge(2,5,5),
    Edge(3,4,7),
    Edge(3,5,8),
    Edge(3,6,4),
    Edge(4,6,6),
    Edge(5,6,1)};
   KruskalMST(edge_list,7);

/*
 srand (time(NULL));
    ifstream infile(argv[1]);
    vector<Edge> edge_list;
    int number_of_vertices;
	infile >> number_of_vertices;

     for (int i = 0; i < number_of_vertices; i++) {
         int vertex, out_degree;

        infile >> vertex >> out_degree;

        for (int i = 0; i < out_degree; i++) {
			int neighbor;
			infile >> neighbor;
            int weight = rand() % 100 + 2;  
            edge_list.push_back(Edge(vertex,neighbor,weight));
            
        }

     }

     KruskalMST(edge_list,number_of_vertices);*/
    return 0;
}
