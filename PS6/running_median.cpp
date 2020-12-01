// https://www.hackerrank.com/challenges/find-the-running-median/submissions/code/189316906
vector<double> runningMedian(vector<int> a) {
    priority_queue<int> smallers;
    priority_queue<int, vector<int>, greater<int>> largers;
    vector<double> medians {a[0]+0.0};
    smallers.push (a[0]);
    for(unsigned int i = 1; i < a.size(); i++) {
        int num = a[i];
        if (num > medians[i - 1]) {
            largers.push(num);
        } else {
            smallers.push(num);
        }
        
        if (largers.size() > smallers.size() + 1) {
            int val = largers.top();
            largers.pop();
            smallers.push(val);
        } else if (smallers.size() > largers.size() + 1) {
            int val = smallers.top();
            smallers.pop();
            largers.push(val);
        }

        float median;
        if (largers.size() > smallers.size()) {
            median = largers.top();
        } else if(largers.size() < smallers.size()) {
            median = smallers.top();
        } else {
            median = (largers.top() + smallers.top()) / 2.0;
        }
        medians.push_back(median);
    }
return medians; 