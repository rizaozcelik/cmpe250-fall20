#include <iostream>
#include "ArrayListTemplate.h"


int main(int argc, char const *argv[]) {
	ArrayList<int> lst1 = ArrayList<int>(10);

	for (int i = 0; i < 5; i++) {
		int rnd = rand() % 10;
		lst1.insert(rnd);
		cout << rnd << ' ';
	}

	cout << "Inserted integers\nLst1: ";
	lst1.print();

	ArrayList<char> lst2 = ArrayList<char>(10);
	for (int i = 0; i < 5; i++) {
		int rnd = rand() % 10;
		lst2.insert(char(rnd + int('a')));
		cout << char(rnd + int('a')) << ' ';
	}

	cout << "Inserted chars\nLst2: " << lst2;
	lst2.print();

	ArrayList<ArrayList<int>> lists;
	for (int i = 0; i < 5; i++) {
		ArrayList<int> l;
		for (int j = 0; j < 9; j++){
			int rnd = rand() % 10;
			l.insert(rnd);
		}
		lists.insert(l);
	}
	lists.print();
	cout << lists << endl;

	return 0;
}