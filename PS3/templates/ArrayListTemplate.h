#include <string>
#include <iostream>

using namespace std;

#ifndef ArrayList_H
#define ArrayList_H

template <class T> class ArrayList {
private:
	static int nCreatedInstance;
	int len;
	T* data = NULL;
public:
	int id, adjustSize;
	ArrayList<T>(int adjustSize=10);
	ArrayList<T>(const ArrayList<T>& listToCopy);
	void insert(T val, int idx=0);
	T get(int idx=0);
	int getLength();
	void print();
	ArrayList<T>& operator=(const ArrayList<T>& listToAssign);
	template <class T2> friend ostream& operator <<(ostream& out, const ArrayList<T2>& l);
	~ArrayList<T>();
};

template <class T>
int ArrayList<T>::nCreatedInstance = 0;


template <class T>
ArrayList<T>::ArrayList(int _adjustSize) {
	this->len = 0;
	this->adjustSize = _adjustSize;
	this->data = new T[_adjustSize];

	ArrayList::nCreatedInstance++;
	this->id = ArrayList::nCreatedInstance;	
}

template <class T> 
ArrayList<T>::ArrayList(const ArrayList& listToCopy) {
	// cout << "Copy constructor is called." << endl;
	this->len = listToCopy.len;
	this->adjustSize = listToCopy.adjustSize;
	int newSize = this->len + (adjustSize - (len % adjustSize)); // Round len up to the next multiple of adjustSize.
	
	this->data = new T[newSize];
	for (int i = 0; i < this->len; ++i){
		data[i] = listToCopy.data[i];
	}

	ArrayList::nCreatedInstance++;
	this->id = ArrayList::nCreatedInstance;	
	// cout << "Copied instance: " << listToCopy.id << " to new object with id: " << this->id << endl;  
}

template <class T> 
ArrayList<T>& ArrayList<T>::operator=(const ArrayList& listToAssign) {
	// cout << "Assignment operator is called." << endl;
	if (this == &listToAssign) {
		return *this;
	}
	// If this object was used before, free the memory it has used. Test the effectiveness by assigning objects to one another so many times!
	// For testing, comment out this if block and run tester code in testList.cpp
	if (this->data != NULL) { 
		// cout << "Deleting previously used data array (Assignment operator)" << endl;
		delete[] this->data;		
	}
	this->len = listToAssign.len;
	this->adjustSize = listToAssign.adjustSize;
	int newSize = this->len + (adjustSize - (len % adjustSize)); // Round len up to the next multiple of adjustSize.
	this->data = new T[newSize];
	for (int i = 0; i < this->len; i++){
		data[i] = listToAssign.data[i];
	}

	// cout << "Assigned instance: " << listToAssign.id << " to new object with id: " << this->id  << endl;  	
	return *this;
}

template <class T> 
void ArrayList<T>::insert(T val, int idx) {
	if (idx < 0 || idx > this->len) {
		return;
	}
	if (this->len % adjustSize == 0 && this->len !=0) {
		// We need to copy the material to a new array
		// cout << "I am full! Gimme some space, bruh!" << endl;
		T* new_data = new T[this->len + this->adjustSize];
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

template <class T> 
T ArrayList<T>::get(int index) {
	if (this->len > 0 && index < this->len) {
		return this->data[index];
	}
	return -1;
}

template <class T> 
int ArrayList<T>::getLength() {
	return this->len;
}

template <class T> 
void ArrayList<T>::print() {
	for (int i = 0; i < this->len; i++)	{
		cout << this->data[i] << ' ';		
	}
	cout << endl;
}

template <class T> 
ostream& operator<<(ostream& out, const ArrayList<T>& l) {
	for (int i = 0; i < l.len; i++)	{
		out << l.data[i] << ' ';		
	}
	out << endl;
	return out;
}

template <class T> 
ArrayList<T>::~ArrayList() {
	if (this->data != NULL) {
		delete[] this->data;
	}
}

#endif
