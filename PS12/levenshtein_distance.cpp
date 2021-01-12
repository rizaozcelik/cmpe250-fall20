#include <iostream>
#include <vector>

using namespace std;
void printTable(vector<vector<int>> distanceTable, string word1, string word2) {
	word2 = " " + word2;
	for (int i = 0; i < word2.length(); i++) {
		cout << word2[i] << " ";
	}
	cout << endl;

	for (int i = 0; i < word1.length(); i++) {
		cout << word1[i] << " ";		
		for (int j = 0; j < word2.length() - 1; j++) {
			cout << distanceTable[i][j] << " ";			
		}
		cout << endl;
	}
	cout << "==========================\n"; 
}

int main(int argc, char const *argv[]) {
	string word1 = argv[1];
	string word2 = argv[2];
	word1 = "/" + word1;
	word2 = "/" + word2;
	int length1 = word1.length();
	int length2 = word2.length();

	vector<vector<int>> distanceTable;
	for (int i = 0; i < length1; i++) {
		distanceTable.push_back(vector<int>(length2));
	}

	for (int i = 0; i < length1; i++) {
		distanceTable[i][0] = i;
	}
	for (int i = 0; i < length2; i++) {
		distanceTable[0][i] = i;
	}

	printTable(distanceTable, word1, word2);
	for (int i = 1; i < length1; i++) {
		for (int j = 1; j < length2; j++) {
			int insertionCost = distanceTable[i][j - 1] + 1;
			int deletionCost = distanceTable[i - 1][j] + 1;
			int copyCost = distanceTable[i - 1][j - 1];
			if (word1[i] != word2[j]) {
				copyCost++;
			} 
			int cost = min(insertionCost, min(deletionCost, copyCost));
			distanceTable[i][j] = cost;
		}
		printTable(distanceTable, word1, word2);
	}
	return 0;
}