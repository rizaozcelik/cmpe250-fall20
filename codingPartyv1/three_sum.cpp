// Link to question: https://www.hackerrank.com/contests/cmpe250-codingparty-v1/challenges/finding-3-sum
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>
using namespace std;

int main() {
    int N, X;
    cin >> N >> X;

    unordered_set<int> uniques;
    for (int i = 0; i < N; i++) {
        int num;
        cin >> num;
        uniques.insert(num);
    }
    vector<int> nums;
    for (auto num : uniques) {
        nums.push_back(num);
    }
    
    sort(nums.begin(), nums.end());
    int counter = 0;
    for (int i = 0; i < int(nums.size()); i++) {
        int n1 = nums[i];
        int low = i;
        int high = nums.size() - 1;
        int k = X - n1;
        while (low <= high) {
            int n2 = nums[low];
            int n3 = nums[high];
            if (n2 + n3 < k) {
                low++;
            } else if (n2 + n3 > k) {
                high--;
            } else {
                counter++;
                high--;
                low++;
            }
        }
    }
    cout << counter;
    return 0;
}
