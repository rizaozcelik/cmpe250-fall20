// Link to question: https://www.hackerrank.com/challenges/ctci-making-anagrams/
int number_needed(string a, string b) {
    vector<int> chars1(26);
    vector<int> chars2(26);
        
    for(int i = 0; i < a.length(); i++){
        chars1[a[i]- 'a']++;
    }
    
    for(int i = 0; i < b.length(); i++){
        chars2[b[i]- 'a']++;
    }
    
    int res = 0;
    for(int i= 0; i < 26; i++){
        res += abs(chars1[i] - chars2[i]);
    }

    return res;
}