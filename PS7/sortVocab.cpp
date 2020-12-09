#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_set>
#include <chrono>
#include <algorithm>

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

void addRandomWords(vector<string>& vocab, int maxWordLen=23, int nRandomWords=1000001) {
	for (int i = 0; i < nRandomWords; i++) {
		int length = min(rand() % maxWordLen, 2);
		string s;
		for (int l = 0; l < length; l++) {
			char c = char('a' + (rand() % 26));
			s.push_back(c);
		}
		vocab.push_back(s);
	}
}


template <typename T> void insertionSort(vector<T>& elements, int startIndex, int lastIndex) {
	if (lastIndex < startIndex || startIndex < 0 || lastIndex < 0) {
		return;
	}
	
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
	if(left + 20 <= right) {
		T pivot = elements[right]; // pivot  
		int i = left;
		
	    for (int j = left; j <= right - 1; j++) {  
	        if (elements[j] < pivot)  {
	        	if (i != j) {
		            swap(elements[i], elements[j]); 	        		
	        	}  
	     		i++;
	        }  
	    }
	    swap(elements[i], elements[right]);  
	    quickSort(elements, left, i - 1);  
        quickSort(elements, i + 1, right);
	} else {
		insertionSort(elements, left, right);
	}
}

int main(int argc, char const *argv[]) {
	ifstream input("./nli_tr_sentences.txt");
	// Get only unique words
	unordered_set<string> words;
	int maxWordLen = 23;
	string word;
	while (input >> word) {
		// Get rid of nonsensical words.
		if (word.length() <= maxWordLen) {
			words.insert(word);			
		}
	}
	
	vector<string> vocab;
	for (auto word : words) {
		vocab.push_back(word);
	}

	// Comment this in to observe the scalability of radix sort
	addRandomWords(vocab);
	vector<string> vocab2(vocab);
	
	auto start = chrono::high_resolution_clock().now();
	// Start from the last letter and iterate all words
	for (int i = maxWordLen - 1; i >= 0; i--) {
		// Use a bucket for each letter and reserve one for small inputs
		vector<vector<string>> buckets(27);
		for (auto word : vocab) {
			if (word.length() > i) {
				char c = word[i];
				buckets[int(c - 'a') + 1].push_back(word);
			} else {
				buckets[0].push_back(word);
			}
		}

		int wordIdx = 0;
		for (auto bucket : buckets) {
			for (auto word : bucket) {
				vocab[wordIdx] = word;
				wordIdx++;
			}
		}
	}

	auto stop = chrono::high_resolution_clock().now();
	int radixSortTime = chrono::duration_cast<chrono::milliseconds>(stop - start).count(); 
	isSortedAsc(vocab);
	cout << "Radix Sort ends in " << radixSortTime << " ms" << endl;

	start = chrono::high_resolution_clock().now();
	quickSort(vocab2, 0, vocab2.size()-1);
	stop = chrono::high_resolution_clock().now();
	int qsTime = chrono::duration_cast<chrono::milliseconds>(stop - start).count(); 
	isSortedAsc(vocab2);
	cout << "Quick Sort ends in " << qsTime << " ms" << endl;
	
	return 0;
}