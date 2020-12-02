#include <vector>
#include <ostream>
#include <iostream>

using namespace std;

#ifndef Heap_H
#define Heap_H

template <class T> class Heap {
private:
	int capacity;
	int nItems = 0;
	vector<T> items;
	void percolateDown(int bubbleIdx);
	void percolateUp(int bubbleIdx);
public:
	Heap<T>();
	Heap<T>(int capacity);
	Heap<T>(const vector<T> v);
	T top();
	bool pop();
	bool push(const T item);
	int size();
	void print(int maxIdx=-1);
};

#endif

// Can be used for creating vector<Heap>(n). Equivalent to using a default value for the capacity argument.
template <class T> Heap<T>::Heap() {
	this->capacity = 20000;
	this->items = vector<T>(this->capacity);
}

template <class T> Heap<T>::Heap(int capacity) {
	this->capacity = capacity;
	this->items = vector<T>(capacity);
}

template <class T> Heap<T>::Heap(const vector<T> items) {
	this->nItems = items.size();
	this->capacity = nItems + 1;
	this->items = vector<T>(this->capacity);
	for (int i = 1; i <= items.size(); i++) {
		this->items[i] = items[i - 1];
	}

	for(int i = this->nItems / 2; i > 0; i--) {
		this->percolateDown(i);
	}
}

template <class T> T Heap<T>::top() {
	return this->items[1];
}

template <class T> bool Heap<T>::pop() {
	// Nothing to pop.
	if (this->nItems == 0) {
		return false;
	}
	swap(this->items[1], this->items[nItems]);
	this->nItems--;
	this->percolateDown(1);
	return true;
}

template <class T> void Heap<T>::percolateDown(int bubbleIdx) {
	bool isHeap = false;
	while (!isHeap) {
		isHeap = true;
		int leftChildIdx = 2 * bubbleIdx;
		int rightChildIdx = 2 * bubbleIdx + 1;
		T& parent = this->items[bubbleIdx];
		// If there is a right child...
		if (rightChildIdx <= this->nItems) {
			T& leftChild = this->items[leftChildIdx];
			T& rightChild = this->items[rightChildIdx];
			if (leftChild < parent || rightChild < parent) {
				isHeap = false;
				// Move the minimum to upper level
				if (leftChild < rightChild ) {
					swap(parent, leftChild);
					bubbleIdx = leftChildIdx;
				} else {
					swap(parent, rightChild);
					bubbleIdx = rightChildIdx;
				} 
			}
		// If there is a left child...
		} else if (leftChildIdx <= this->nItems) {
			T& leftChild = this->items[leftChildIdx];
			// Move the child up, if it is smaller than the parent.
			if (leftChild < parent) {
				swap(parent, leftChild);
				bubbleIdx = leftChildIdx;
			} 
		} 
	}
}

template <class T> bool Heap<T>::push(const T item) {
	// Reject insertion due to full capacity
	if (this->nItems == this->capacity - 1) {
		return false;
	}

	this->nItems++;
	this->items[this->nItems] = item;
	this->percolateUp(this->nItems);
	return true;
}

template <class T> void Heap<T>::percolateUp(int bubbleIdx) {
	bool isHeap = false;
	// Move a node up until it has a parent and it is smaller than its parent.
	while (bubbleIdx > 1 && !isHeap) {
		T& child = this->items[bubbleIdx];
		T& parent = this->items[bubbleIdx / 2];
		isHeap = child > parent;
		if (!isHeap) {
			swap(child, parent);
			bubbleIdx = bubbleIdx / 2;
		}
	}
}

template <class T> int Heap<T>::size() {
	return this->nItems;
}

template <class T> void Heap<T>::print(int maxIdx) {
	if (maxIdx == -1) {
		maxIdx = this->nItems;
	}
	for(int i = 1; i <= maxIdx; i++) {
		cout << this->items[i] << " ";
	}
	cout << endl;
}
