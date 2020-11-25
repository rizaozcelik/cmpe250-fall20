#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
#include <chrono>
#include <unordered_set>
#include "OpenHashSet.h"

using namespace std;

int main(int argc, char const *argv[]) {
	// Test if our implementation is working.
	int tableSize = 11;
	float maxLoadFactor = 0.8;
	OpenHashSet hashSet = OpenHashSet(tableSize, maxLoadFactor);
	hashSet.insert(5);
	hashSet.insert(15);
	hashSet.insert(16);
	hashSet.insert(5);
	hashSet.insert(0);

	cout << hashSet.contains(10) << " " << hashSet.contains(0) << " " << hashSet.contains(5) << endl;
	cout << hashSet;

	// Compare our open hash set implementation with vector and unordered_set
	// Play with these parameters and observe how run times change with respect to both of them.
	int largeTableSize = 49999;
	float largeMaxLoadFactor = 3;
	int N = 100000;

	// Just generate some random numbers for testing.
	deque<int> randomNumbers;
	for (int i = 0; i < N; i++) {
		int rnd = rand();
		randomNumbers.push_back(rnd);
	}

	OpenHashSet hashSet2 = OpenHashSet(largeTableSize, largeMaxLoadFactor);
	vector<int> v(largeTableSize);

	auto start = chrono::high_resolution_clock().now();
	for (auto rnd :  randomNumbers) {
		hashSet2.insert(rnd);
	}

	auto stop = chrono::high_resolution_clock().now();
	int hsInsertionTime = chrono::duration_cast<chrono::milliseconds>(stop - start).count(); 
	cout << "HashSet insertion took "<< hsInsertionTime << "ms\n";

	start = chrono::high_resolution_clock().now();
	for (auto rnd : randomNumbers) {
		v.push_back(rnd);
	}

	stop = chrono::high_resolution_clock().now();
	int vInsertionTime = chrono::duration_cast<chrono::milliseconds>(stop - start).count(); 
	cout << "Vector insertion took "<< vInsertionTime << "ms\n";


	start = chrono::high_resolution_clock().now();
	for (auto rnd : randomNumbers) {
		hashSet2.contains(rnd);
	}
	stop = chrono::high_resolution_clock().now();
	int hsSearchTime = chrono::duration_cast<chrono::milliseconds>(stop - start).count(); 
	cout << "HashSet search took "<< hsSearchTime << "ms\n";


	start = chrono::high_resolution_clock().now();
	for (auto rnd : randomNumbers) {
		find(v.begin(), v.end(), rnd);
	}

	stop = chrono::high_resolution_clock().now();
	int vSearchTime = chrono::duration_cast<chrono::milliseconds>(stop - start).count(); 
	cout << "Vector search took "<< vSearchTime << "ms\n";

	unordered_set<int> set(largeTableSize);
	cout << set.bucket_count() << endl;
	start = chrono::high_resolution_clock().now();
	for (auto rnd : randomNumbers) {
		set.insert(rnd);
	}

	stop = chrono::high_resolution_clock().now();
	int usInsertionTime = chrono::duration_cast<chrono::milliseconds>(stop - start).count(); 
	cout << "Unordered Set insertion took "<< usInsertionTime << "ms\n";


	start = chrono::high_resolution_clock().now();
	for (auto rnd : randomNumbers) {
		set.find(rnd);
	}

	stop = chrono::high_resolution_clock().now();
	int usSearchTime = chrono::duration_cast<chrono::milliseconds>(stop - start).count(); 
	cout << "Unordered Set search took "<< usSearchTime << "ms\n";

	cout << "HashSet total: " << hsInsertionTime + hsSearchTime << endl;
	cout << "Vector total: " << vInsertionTime + vSearchTime << endl;
	cout << "Unordered Set total: " << usInsertionTime + usSearchTime << endl;

	return 0;
}
