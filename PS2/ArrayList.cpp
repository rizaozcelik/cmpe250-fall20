#include <iostream>
#include "ArrayList.h"

using namespace std;

ArrayList::ArrayList(int adjustSize) {
	this->len = 0;
	this->adjustSize = adjustSize;
	this->data = new int[adjustSize];
}

ArrayList::ArrayList(const ArrayList& listToCopy) {
	cout << "Copy constructor is called." << endl;
	this->len = listToCopy.len;
	this->adjustSize = listToCopy.adjustSize;
	int new_size = this->len + (adjustSize - (len % adjustSize)); // Round len up to the next multiple of adjustSize.
	this->data = new int[new_size];
	for (int i = 0; i < this->len; ++i){
		data[i] = listToCopy.data[i];
	}
}

ArrayList ArrayList::operator=(const ArrayList& listToAssign) {
	cout << "Assignment operator is called." << endl;
	if (this == &listToAssign) {
		return *this;
	}
	if (this->data != NULL) { // If this object was used before, free the memory it has used.
		delete[] this->data;		
	}
	this->len = listToAssign.len;
	this->adjustSize = listToAssign.adjustSize;
	int new_size = this->len + (adjustSize - (len % adjustSize)); // Round len up to the next multiple of adjustSize.
	this->data = new int[new_size];
	for (int i = 0; i < this->len; ++i){
		data[i] = listToAssign.data[i];
	}
	return *this;
}

void ArrayList::insert(int val, int idx) {
	if (idx < 0 || idx > this->len) {
		return;
	}
	if (this->len % adjustSize == 0) {
		 // We need to copy the material to a new array
		cout << "I am full! Gimme some space, bruh!" << endl;
		int* new_data = new int[this->len + this->adjustSize];
		for (int i = 0; i < this->len; i++) {
			new_data[i] = this->data[i];
		}
		delete[] this->data; // Does the magic!
		this->data = new_data;
	}
		
	for (int i = this->len-1; i >= idx; i--) {
		this->data[i+1] = this->data[i];
	}
	this->data[idx] = val;
	this->len++;
}

int ArrayList::get(int index) {
	if (this->len > 0 && index < this->len) {
		return this->data[index];
	}
	return -1;
}

int ArrayList::getLength() {
	return this->len;
}

void ArrayList::print() {
	for (int i = 0; i < this->len; i++)	{
		cout << this->data[i] << ' ';		
	}
	cout << endl;
}

ArrayList::~ArrayList() {
	cout << "Destructing...";
	print();
	delete[] this->data;
	cout << "Destructed the object with data address: " << data << endl;
}

