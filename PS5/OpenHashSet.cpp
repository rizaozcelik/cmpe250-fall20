#include "OpenHashSet.h"

OpenHashSet::OpenHashSet(int tableSize, float maxLoadFactor) {
	this->tableSize = tableSize;
	this->maxLoadFactor = maxLoadFactor;
	this->data = vector<list<int>>(tableSize);
	this->nElements = 0;
	this->loadFactor = 0;
	this->nextPrimes = queue<int>(); // Will be used for rehashing

	int maxPrime = 1000003;
	vector<bool> isPrime(maxPrime, true);
    for (int i = 2; i <= maxPrime / 2; i++){
        if(isPrime[i]) {
	        for(int j = i*2; j < maxPrime; j+=i) {
	            isPrime[j] = false;
	        }
	        if (i > this->tableSize) {
		        this->nextPrimes.push(i);
	        }
	    }
    }
}

int OpenHashSet::hash(int val, int base) {
	return val % base;
}

bool OpenHashSet::contains(int val) {
	int bucketIdx = hash(val, this->tableSize);
	list<int> bucket = this->data[bucketIdx];
	for (auto i : bucket) {
		if (i == val) {
			return true;
		}
	}
	return false;
}

bool OpenHashSet::insert(int val) {
	// Keep the elements in the set unique.
	if (this->contains(val)) {
		return false;
	}
	int bucketIdx = hash(val, this->tableSize);
	this->data[bucketIdx].push_back(val);
	this->nElements++;
	this->loadFactor = ((float) this->nElements) / this->tableSize;	
	if (this->loadFactor > this->maxLoadFactor) {
		this->rehash();
	}
	return true;
}


void OpenHashSet::rehash() {
	// cout << "loadFactor: " << this->loadFactor << " Rehashing.\n";
	// Using the next prime is good for demonstration purposes but it is not the smartest idea for scalability.
	// Because, rehashing is expensive and when you rehash once, you would not like to rehash for a considerable amount of time. 
	int nextTableSize = this->nextPrimes.front();
	this->nextPrimes.pop();
	vector<list<int>> newData(nextTableSize);
	for (auto bucket : this->data) {
		for (auto i : bucket) {
			int bucketIdx = hash(i, nextTableSize);
			newData[bucketIdx].push_back(i);
		}
	}
	this->data = newData;
	this->tableSize = nextTableSize;
	this->loadFactor = ((float) this->nElements) / this->tableSize;	
}

ostream& operator<<(ostream& out, const OpenHashSet& hashSet) {
	for (int i = 0; i < hashSet.data.size(); i++) {
		list<int> bucket = hashSet.data[i];
		out << "Bucket " << i << ": ";
		for (auto val : bucket) {
			out << val << " ";
		}
		out << endl;
	}
}