#include <iostream>
#include <vector>
#include <list>
#include <queue>

using namespace std;

class OpenHashSet {
private:
	vector<list<int>> data;
	int tableSize, nElements;
	float loadFactor, maxLoadFactor;
	queue<int> nextPrimes;
public:
	OpenHashSet(int tableSize, float maxLoadFactor);	
	int hash(int val, int base);
	bool insert(int val);
	bool contains(int val);
	void rehash();
	friend ostream& operator <<(ostream& out, const OpenHashSet& hashSet);

};