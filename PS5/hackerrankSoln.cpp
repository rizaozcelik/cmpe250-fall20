// Link to question: https://www.hackerrank.com/challenges/pairs/problem
int pairsBruteForce(int k, vector<int> arr) {
    int counter = 0;
    for (int  i = 0; i < arr.size(); i++) {
        int num1 = arr[i];
        for (int j = i+1; j < arr.size(); j++) {
            int num2 = arr[j];
            if (abs(num1 - num2) == k) {
                counter++;
            }
        }
    }
    return counter;
}

int pairsHashSet(int k, vector<int> arr) {
    unordered_set<int> hashSet(arr.begin(), arr.end());   
    int counter = 0;
    for (int i = 0; i < arr.size(); i++) {
        int num = arr[i];
        if (hashSet.find(num + k) != hashSet.end()) {
            counter++;  
        }
    }
    return counter;
}
