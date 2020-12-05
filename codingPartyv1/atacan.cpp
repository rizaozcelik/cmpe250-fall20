// Link to question: https://www.hackerrank.com/contests/cmpe250-codingparty-v1/challenges/atacan-plays-hide-and-seek
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

int main() {
    int N, M;
    cin  >> N >> M;
    unordered_map<int, int> heightToIndex;
    for (int i = 0; i < N; i++) {
        int wallHeight;
        cin >> wallHeight;
        if (heightToIndex.find(wallHeight) != heightToIndex.end()) {
            heightToIndex[wallHeight] = -1;
        } else {
            heightToIndex[wallHeight] = i + 1;
        }
    }
    
    for (int i = 0; i < M; i++) {
        int friendHeight;
        cin >> friendHeight;
        if (heightToIndex.find(friendHeight) == heightToIndex.end()) {
            cout << -1 << endl;
        } else {
            cout << heightToIndex[friendHeight] << endl;
        }
    }

    return 0;
}