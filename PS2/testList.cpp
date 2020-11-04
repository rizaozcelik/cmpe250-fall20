#include <iostream>
#include "ArrayList.h"

using namespace std;

int main(int argc, char const *argv[])
{
	ArrayList lst = ArrayList(10);
	// ArrayList lst = ArrayList(); // Equivalent lines.

	int n = 10;
	for (int i = 0; i < n; i++) {
		int rnd = rand() % 10;
		lst.insert(rnd);
		cout << rnd << ' ';
	}
	cout << endl;
	lst.print();

	// If the .cpp file is not implemented properly, these lines cause error due to shared heap memory. 
	cout << "Inserted first elements\n";
	ArrayList lst2 = ArrayList(lst); // Copy constructor is called
	// ArrayList lst2 = lst // Copy constructor is called.
	ArrayList lst3;
	lst3 = lst; // Assignment operator is called

	cout << "Lst:";
	lst.print();

	cout << "Lst2:";
	lst2.print();

	cout << "Lst3:";
	lst3.print();

	// To show that each one of them is run independently.
	lst.insert(1);
	cout << "Lst:";
	lst.print();
	
	lst2.insert(2);
	cout << "Lst2:";
	lst2.print();
 
	lst3.insert(3);
	cout << "Lst3:";
	lst3.print();

	return 0;
}