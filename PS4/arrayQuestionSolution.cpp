#include <iostream>
#include <vector>
#include <stack>
#include <chrono>

using namespace std;

/**
 * Find all elements in an array that are 
 * greater than all elements present to their right.
 * 
 * For example for arr = { 10, 3, 6, 4, 5}
 * Result will be { 10, 6, 5 }
 * 
 * Try to solve this problem 
 * a) With brute force
 * b) With just one traverse
 * c) From left to right one traverse with using a stack
 * 
 * */

vector<int> solveV1(int input[], int size ){

    vector<int> result;
    for( int i = 0; i < size ; i++){

        bool valid = true;
        for( int j = i + 1 ; j < size ; j++ ){
            if(input[i] <= input[j]){
                valid = false;
                break;
            }
        }
        if(valid){
            result.push_back(input[i]);
        }

    }
    return result;


}

vector<int> solveV2(int input[], int size ){

    vector<int> result;
    int maxVal = input[size - 1] - 1;
    for( int i = size - 1; i >= 0; i--){

        if( input[i] > maxVal){
            result.push_back(input[i]);
            maxVal = input[i];
        }

    }
    return result;


}


vector<int> solveV3(int input[], int size ){


    vector<int> result;
    stack<int> container;

    for( int i = 0; i < size; i++){

        while(!container.empty() && input[i] >= container.top()){
            container.pop();
        }
        container.push(input[i]);
    }

    while(!container.empty()){
        result.push_back(container.top());
        container.pop();
    }

    return result;


}



int main(int argc, char const * argv[]){
    int size;
    cin >> size;

    int input[size];

    for(int i = 0 ; i < size ; i++){
        input[i] = rand() % 100;
    }
   
    vector<int> myRes = solveV1(input,size);
    
    for(auto d:myRes){
        cout << d << " ";
    }
    cout << endl;
    cout << endl;

    myRes = solveV2(input,size);
   
    for(auto d:myRes){
        cout << d << " ";
    }
    
    cout << endl;
    cout << endl;
    
    myRes = solveV3(input,size);
    
    for(auto d:myRes){
        cout << d << " ";
    }
    cout << endl;

    return 0;

}

