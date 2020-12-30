#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm>  
#include "Heap.h" // Implemented by Rıza Özçelik and usage permission is retrieved.
#include <bits/stdc++.h> 
#include <limits>

using namespace std;

struct MyTuple{
    int vertex_id;
    int weight_to;

    MyTuple(int id, int weight){
        this->vertex_id = id;
        this->weight_to = weight;
    }

    MyTuple(){// for heap
        this->vertex_id = 0;
        this->weight_to = 0;
    }

    bool operator<(const MyTuple& another_tuple) const {
        return this->weight_to < another_tuple.weight_to;
    }

     bool operator>(const MyTuple& another_tuple) const {
        return this->weight_to > another_tuple.weight_to;
    }
};

void PrimMST(vector<vector<MyTuple>> adj_list,int starting_vertex){
    int num_of_vertices = adj_list.size();
    int infinity = numeric_limits<int>::max();

    int cost[num_of_vertices];
    int path[num_of_vertices];
    bool in_tree[num_of_vertices];
    
    for(int i = 0; i< num_of_vertices;i++){
        cost[i] = infinity;
        path[i] = -1;
        in_tree[i] = false;
    }
    
    cost[starting_vertex] = 0;
    path[starting_vertex] = starting_vertex;
    in_tree[starting_vertex] = true;
    
    vector<string> edges_tree;

    Heap<MyTuple> pot_vertices;

    vector<MyTuple> starting_neighbors = adj_list[starting_vertex];
   
    for(int i=0;i<starting_neighbors.size();i++){
        MyTuple pot_vertex = starting_neighbors[i];

        cost[pot_vertex.vertex_id] = pot_vertex.weight_to;
        path[pot_vertex.vertex_id] = starting_vertex;

        pot_vertices.push(pot_vertex);
    }   
    
    int number_of_used_edges = 0;
    int min_cost = 0;
    while(pot_vertices.size() != 0 && number_of_used_edges != num_of_vertices -1){
        MyTuple pot_vertex = pot_vertices.top();
        pot_vertices.pop();
       
        if(!in_tree[pot_vertex.vertex_id]){
        
            edges_tree.push_back(to_string(path[pot_vertex.vertex_id])+"->"+to_string(pot_vertex.vertex_id));
            in_tree[pot_vertex.vertex_id] = true;
            number_of_used_edges++;
             min_cost += cost[pot_vertex.vertex_id];
            vector<MyTuple> neighbors = adj_list[pot_vertex.vertex_id];

            for(int i = 0; i < neighbors.size() ; i++){
                MyTuple new_pot_vertex = neighbors[i];

                if(!in_tree[new_pot_vertex.vertex_id] && cost[new_pot_vertex.vertex_id] > new_pot_vertex.weight_to){
                        cost[new_pot_vertex.vertex_id] = new_pot_vertex.weight_to;
                        path[new_pot_vertex.vertex_id] = pot_vertex.vertex_id;
                       
                        pot_vertices.push(new_pot_vertex);
                }
                
            }  
        }
    }
    cout<<min_cost<<endl;
    for(int i = 0;i<edges_tree.size();i++){
        cout<<edges_tree[i]<<endl;
    }
}

int main(int argc, char const *argv[]) {
    vector<vector<MyTuple>> adj_list;
    vector<MyTuple> vertexA;
    vertexA.push_back(MyTuple(1,8));//B
    vertexA.push_back(MyTuple(7,4));//H
    vertexA.push_back(MyTuple(5,10));//F
    adj_list.push_back(vertexA);

    vector<MyTuple> vertexB;
    vertexB.push_back(MyTuple(7,9));//H
    vertexB.push_back(MyTuple(0,8));//A
    vertexB.push_back(MyTuple(5,7));//F
    vertexB.push_back(MyTuple(2,4));//C
    vertexB.push_back(MyTuple(4,10));//E
    adj_list.push_back(vertexB);

    vector<MyTuple> vertexC;
    vertexC.push_back(MyTuple(5,3));//F
    vertexC.push_back(MyTuple(1,4));//B
    vertexC.push_back(MyTuple(3,3));//D
    adj_list.push_back(vertexC);


    vector<MyTuple> vertexD;
    vertexD.push_back(MyTuple(4,25));//E
    vertexD.push_back(MyTuple(6,2));//G
    vertexD.push_back(MyTuple(5,18));//F
    vertexD.push_back(MyTuple(2,3));//C
    adj_list.push_back(vertexD);


    vector<MyTuple> vertexE;
    vertexE.push_back(MyTuple(6,7));//G
    vertexE.push_back(MyTuple(1,10));//B
    vertexE.push_back(MyTuple(3,25));//D
    vertexE.push_back(MyTuple(5,2));//F
    adj_list.push_back(vertexE);


    vector<MyTuple> vertexF;
    vertexF.push_back(MyTuple(4,2));//E
    vertexF.push_back(MyTuple(2,3));//C
    vertexF.push_back(MyTuple(3,18));//D
    vertexF.push_back(MyTuple(1,7));//B
    vertexF.push_back(MyTuple(0,10));//A
    adj_list.push_back(vertexF);


    vector<MyTuple> vertexG;
    vertexG.push_back(MyTuple(7,3));//H
    vertexG.push_back(MyTuple(3,2));//D
    vertexG.push_back(MyTuple(4,7));//E
    adj_list.push_back(vertexG);

    vector<MyTuple> vertexH;
    vertexH.push_back(MyTuple(0,4));//A
    vertexH.push_back(MyTuple(1,9));//B
    vertexH.push_back(MyTuple(6,3));//G
    adj_list.push_back(vertexH);

    PrimMST(adj_list,3);//D

/*
 srand (time(NULL));
    ifstream infile(argv[1]);
    vector<vector<MyTuple>> adj_list;
    int number_of_vertices;
	infile >> number_of_vertices;

     for (int i = 0; i < number_of_vertices; i++) {
         int vertex, out_degree;
        vector<MyTuple> neighbors;
        infile >> vertex >> out_degree;

        for (int i = 0; i < out_degree; i++) {
			int neighbor;
			infile >> neighbor;
            int weight = rand() % 100 + 2;  
            neighbors.push_back(MyTuple(neighbor,weight));
        }
        adj_list.push_back(neighbors);
     }

      PrimMST(adj_list,1);//D */
    return 0;
}

// A -> 0
// B -> 1
// C -> 2
// D -> 3
// E -> 4
// F -> 5
// G -> 6
// H -> 7