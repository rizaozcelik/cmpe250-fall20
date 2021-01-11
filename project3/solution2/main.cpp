#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <sstream>
#include <queue>

using namespace std;
 

list<int> path;
FILE* fp;
void merge(vector<int>& new_circle,int common_point_index){
    auto pos = path.begin();
    advance(pos,common_point_index+1);
    if (path.size()==0) path.insert(pos,new_circle.begin(),new_circle.end());
    else path.insert(pos,new_circle.begin()+1,new_circle.end());
    
}

bool eulerian(int* out_degrees,int* in_degrees,int size){
   
    for(int i =0;i<size;i++){
        if(in_degrees[i]!=out_degrees[i]){
            fprintf(fp,"no path");
            return false;
        }
    }
    return true;
}

int main(int argc, char const *argv[]) {

 ifstream infile(argv[1]);
 
 fp = fopen(argv[2],"w");
	int number_of_vertices;
	infile >> number_of_vertices;
   
	int number_of_edges = 0;
	vector<queue<int>> adj_list;
    int out_degrees[number_of_vertices] = { 0 };
	int in_degrees[number_of_vertices] = { 0 };

    for (int i = 0; i < number_of_vertices; i++) {
		int vertex, out_degree;
        
        queue<int> neighbors;
		infile >> vertex >> out_degree;
        out_degrees[vertex] += out_degree;

		for (int i = 0; i < out_degree; i++) {
			int neighbor;
			infile >> neighbor;
            in_degrees[neighbor] ++;
			neighbors.push(neighbor);
			number_of_edges++;
		}
        adj_list.push_back(neighbors);
	}
  
	int init_vertex;
	infile >> init_vertex;
	infile.close();

   
    if(eulerian(out_degrees,in_degrees,number_of_vertices))
    {
    int current_vertex = init_vertex;
    int common_point_index = 0;
    cout<<number_of_edges<<endl;
    while(number_of_edges>0){
        vector<int> temp_path;
        temp_path.push_back(current_vertex);
        
        while(adj_list[current_vertex].size()>0){
            int new_vertex = adj_list[current_vertex].front();
            adj_list[current_vertex].pop();
            current_vertex = new_vertex;
            temp_path.push_back(current_vertex);
            number_of_edges--;
        }
        merge(temp_path,common_point_index);
      
        for(int i=1;i<temp_path.size();i++){
            if(adj_list[temp_path[i]].size()!=0){
                common_point_index += i;
                current_vertex = temp_path[i];
                break;
            }
        }
       
    }
    
    for (list<int>::iterator it = path.begin(); it != path.end(); ++it)  fprintf(fp,"%d ",*it);
    }
     fclose(fp);
     return 0;
}