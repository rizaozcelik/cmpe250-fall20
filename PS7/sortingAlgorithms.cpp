#include <iostream>
#include <vector>

using namespace std;

template <typename T> bool isSortedAsc(const vector<T>& elements) {
	for (int i = 0; i < elements.size() - 1; i++) {
		if(elements[i] > elements[i+1]) {
			cout << "There is an error!"  << elements[i] << " is larger than " << elements[i+1] << endl;
			return false;
		}
	}
	cout << "No error! You must be very very smart!" << endl;
	return true;
}

template <typename Container> void printContainer(Container container) {
	for (auto i : container) {
		cout << i << " ";
	}
	cout << endl;
}

template <typename T> void insertionSort(vector<T>& elements, int startIndex, int lastIndex) {
	// Some sanity checks...
	if (lastIndex < startIndex || startIndex < 0 || lastIndex < 0) {
		return;
	}

	// Shift all elements to the right until you find the insertion index 
	for (int i = startIndex + 1; i <= lastIndex; i++) {
		T elemToInsert = elements[i];
		int insertionIndex = i;
		bool foundIndex = false;
		while (insertionIndex > startIndex && !foundIndex) {
			if (elements[insertionIndex - 1] > elemToInsert) {
				elements[insertionIndex] = elements[insertionIndex - 1];
				insertionIndex--;
			} else {
				foundIndex = true;
			}
		}
		elements[insertionIndex] = elemToInsert;
	}
}

// This code is adapted from: https://www.geeksforgeeks.org/quick-sort/
template <typename T> void quickSort(vector<T>& elements, int left, int right) {
	// Insertion sort is faster for small inputs!
	if(left + 20 <= right) {
		// Pick the last element as pivot. This is the worst idea for reversed sorted inputs
		T pivot = elements[right]; 
		int i = left; // Keep track of the elements smaller than pivot
		
		// If an element is smaller than the pivot, copy it to LHS.
	    for (int j = left; j <= right - 1; j++) {
	        if (elements[j] < pivot) {
	        	if (i != j) {
		            swap(elements[i], elements[j]); 	        		
	        	}
	     		i++;
	        }  
	    }
	    // Put the pivot in its position and continue.
	    swap(elements[i], elements[right]);  
	    quickSort(elements, left, i - 1);  
        quickSort(elements, i + 1, right);
	} else {
		insertionSort(elements, left, right);
	}
}

// Smart way of hashing for sorting...
int countingSort(vector<int>& elements, int max) {
	// Construct a frequency table.
	vector<int> counts(max);
	for (auto i : elements) {
		counts[i]++;
	}

	// Construct the array from frequencies
	int numberIdx = 0;
	for (int i = 0; i < counts.size(); i++) {
		int count = counts[i];
		for (int j = 0; j < count; j++) {
			elements[numberIdx] = i;
			numberIdx++;
		}
	}
}

// Stabilize counting sort...
int bucketSort(vector<int>& elements, int nBuckets) {
	vector<vector<int>> buckets(nBuckets);
	for (auto i : elements) {
		buckets[i].push_back(i);
	}

	int numberIdx = 0;
	for (auto bucket : buckets) {
		for (auto number : bucket) {
			elements[numberIdx] = number;
			numberIdx++;
		}
	}
}

int main(int argc, char const *argv[]) {	
	vector<int> elements;
	int N = 1001;
	int max = 1000;
	for (int i = 0; i < N; i++) {
		int rnd = rand() % max;
		elements.push_back(rnd);
	}

	insertionSort(elements, 0, elements.size() - 1);
	// quickSort(elements, 0, elements.size() - 1);
	// countingSort(elements, max);
	// bucketSort(elements, max);

	// printContainer(elements);
	isSortedAsc(elements);
	
	return 0;
}