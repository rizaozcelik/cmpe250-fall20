#include <iostream>
#include "ArrayList.h"

void testHeapManagementAssignment() {
	ArrayList lst1 = ArrayList(10);
	for (int i = 0; i < 100000; i++) {
		lst1.insert(rand() % 10);
	}

	ArrayList lst4;
	for (int i = 0; i <= 10000; i++) {
		lst4 = lst1;
	}

}

void testHeapManagementInsert() {
	ArrayList lst1 = ArrayList(10);
	for (int i = 0; i < 100000; i++) {
		lst1.insert(rand() % 10);
	}
}

int main(int argc, char const *argv[]) {

	ArrayList lst1 = ArrayList(10);

	for (int i = 0; i < 5; i++) {
		int rnd = rand() % 10;
		lst1.insert(rnd);
		cout << rnd << ' ';
	}

	cout << "Inserted first elements\nLst1: ";
	lst1.print();

	cout << "Now Creating lst2 from lst1 by ArrayList(lst1)" << endl;
	// Run the below block with and without a copy constructor and observe the difference!
	ArrayList lst2 = ArrayList(lst1);
	lst2.insert(123); 
	lst2.print();
	lst1.print();

	cout << "Now Creating lst2 from lst1 by = lst1" << endl;
	ArrayList lst3 = lst1;
	lst3.insert(123); 
	lst3.print();
	lst1.print();

	// Run the below block with and without an assignment operator and observe the difference!
	cout << "Now Creating lst4 from lst1 in two lines" << endl;
	ArrayList lst4;
	lst4 = lst1;
	lst4.insert(123); 
	lst4.print();
	lst1.print();

	return 0;
}