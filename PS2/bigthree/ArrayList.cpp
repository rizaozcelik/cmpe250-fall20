#include <iostream>
#include "ArrayList.h"

int ArrayList::nCreatedInstance = 0;

ArrayList::ArrayList(int _adjustSize) {
	this->len = 0;
	this->adjustSize = _adjustSize;
	this->data = new int[_adjustSize];

	ArrayList::nCreatedInstance++;
	this->id = ArrayList::nCreatedInstance;	
}

ArrayList::ArrayList(const ArrayList& listToCopy) {
	cout << "Copy constructor is called." << endl;
	this->len = listToCopy.len;
	this->adjustSize = listToCopy.adjustSize;
	int newSize = this->len + (adjustSize - (len % adjustSize)); // Round len up to the next multiple of adjustSize.
	
	this->data = new int[newSize];
	for (int i = 0; i < this->len; ++i){
		data[i] = listToCopy.data[i];
	}

	ArrayList::nCreatedInstance++;
	this->id = ArrayList::nCreatedInstance;	
	cout << "Copied instance: " << listToCopy.id << " to new object with id: " << this->id << endl;  
}

ArrayList& ArrayList::operator=(const ArrayList& listToAssign) {
	cout << "Assignment operator is called." << endl;
	if (this == &listToAssign) {
		return *this;
	}
	// If this object was used before, free the memory it has used. Test the effectiveness by assigning objects to one another so many times!
	// For testing, comment out this if block and run tester code in testList.cpp
	if (this->data != NULL) { 
		cout << "Deleting previously used data array (Assignment operator)" << endl;
		delete[] this->data;		
	}
	this->len = listToAssign.len;
	this->adjustSize = listToAssign.adjustSize;
	int newSize = this->len + (adjustSize - (len % adjustSize)); // Round len up to the next multiple of adjustSize.
	this->data = new int[newSize];
	for (int i = 0; i < this->len; i++){
		data[i] = listToAssign.data[i];
	}

	cout << "Assigned instance: " << listToAssign.id << " to new object with id: " << this->id  << endl;  	
	return *this;
}

void ArrayList::insert(int val, int idx) {
	if (idx < 0 || idx > this->len) {
		return;
	}
	if (this->len % adjustSize == 0 && this->len !=0) {
		// We need to copy the material to a new array
		// cout << "I am full! Gimme some space, bruh!" << endl;
		int* new_data = new int[this->len + this->adjustSize];
		for (int i = 0; i < this->len; i++) {
			new_data[i] = this->data[i];
		}

		// Does the magic! Without this line, heap keeps growing and growing... Then comes the program is killed!
		// If you do not believe me, comment out this line and run insert 100K times!
		delete[] this->data; 			
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
	cout << "Destructing instance with id: " << this->id << endl;
	// print();
	if (this->data != NULL) {
		delete[] this->data;
	}
	cout << "Destructed the object with data address: " << data << endl;
}

