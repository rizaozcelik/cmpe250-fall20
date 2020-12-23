#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);


void dfs(int v, bool* visited, list<int> *adjacencyList) {

    visited[v] = true;
    list<int>::iterator i;
    
    for (i = adjacencyList[v].begin(); i != adjacencyList[v].end(); ++i)
        if (!visited[*i])
           dfs(*i, visited, adjacencyList);
}


// Complete the roadsAndLibraries function below.
long roadsAndLibraries(long n, long c_lib, long c_road, vector<vector<int>> cities) {
    if(c_lib <= c_road || cities.size() == 0){
        return (long)(c_lib*n);
    }
    list<int> *adjacencyList = new list<int>[n+1];
    
    for(auto i : cities){
        adjacencyList[i[0]].push_back(i[1]);
        adjacencyList[i[1]].push_back(i[0]);
    }
    
    bool *visited = new bool[n+1];
    for (int i = 0; i < n + 1; i++)
        visited[i] = false;

   
    long lCounter = 0;
    
    for(int counter = 1; counter < n+1; counter++){
        if(visited[counter] == false ){
            lCounter++;
            dfs(counter, visited, adjacencyList);
        }    
    }
    return (lCounter*c_lib) + (n - lCounter)*c_road;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string nmC_libC_road_temp;
        getline(cin, nmC_libC_road_temp);

        vector<string> nmC_libC_road = split_string(nmC_libC_road_temp);

        int n = stoi(nmC_libC_road[0]);

        int m = stoi(nmC_libC_road[1]);

        int c_lib = stoi(nmC_libC_road[2]);

        int c_road = stoi(nmC_libC_road[3]);

        vector<vector<int>> cities(m);
        for (int i = 0; i < m; i++) {
            cities[i].resize(2);

            for (int j = 0; j < 2; j++) {
                cin >> cities[i][j];
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        long result = roadsAndLibraries(n, c_lib, c_road, cities);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
