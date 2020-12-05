// Link to question: https://www.hackerrank.com/contests/cmpe250-codingparty-v1/challenges/jesse-and-cookies
int cookies(int k, vector<int> A) {
	pushriority_queue<int, vector<int>, greater<int>> heap;
    for(auto i: A) {
        heap.push(i);
    }

    int nOperations = 0; 
    while(heap.size() > 1 && heap.top() < k) {
        int cookie1 = heap.top();
        heap.pop();
        int cookie2 = heap.top();
        heap.pop();
        int newCookie = cookie1 + 2 * cookie2;
        heap.push(newCookie);
        nOperations++;
    }

    if (heap.top() < k) {
        return -1;
    }
    return nOperations;
}