#include <iostream>
#include <vector>
#include <deque>
#include <list>

using namespace std;


template <typename Container>
void printContainer(Container container) {
	for (typename Container::iterator it=container.begin(); it != container.end(); it++) {
		cout << *it << ' ';
	}
	cout << endl;
}

int main(int argc, char const *argv[])
{

	int n = 5;
	vector<int> v;
	for (int i = 0; i < n; i++) {
		int rnd = rand() % 10;
		v.push_back(rnd); // Fast 
		cout << rnd << ' ';
	}
	cout << endl;
	printContainer(v);

	vector<int>::iterator vectorIt;
	vectorIt = v.insert(v.begin() + 3, 251); // Slow insertion.
	cout <<  "The iterator points to " << *vectorIt << endl; // 251
	printContainer(v);
	vectorIt++;
	v.insert(vectorIt, 252); // Insert to the right of 251.
	printContainer(v);
	cout << v[0] << " " << v.at(2) << " " << *(vectorIt - 1) << endl; // Different access ways.
	

	deque<int> d;
	for (int i = 0; i < n; i++) {
		int rnd = rand() % 10;
		d.push_back(rnd); // Fast 
		cout << rnd << ' ';
	}
	cout << endl;
	for (int i = 0; i < n; i++) {
		int rnd = rand() % 10;
		d.push_front(rnd); // Different from vector; this is also fast. 
		cout << rnd << ' ';
	}
	cout << endl;
	printContainer(d);

	// Same interface with vector.
	deque<int>::iterator dequeIt;
	dequeIt = d.insert(d.begin() + 3, 251); // Slow insertion.
	cout <<  "The iterator points to " << *dequeIt << endl; // 251
	printContainer(d);
	dequeIt++;
	d.insert(dequeIt, 252); // Insert to the right of 251.
	printContainer(d);
	cout << d[0] << " " << d.at(2) << " " << *(dequeIt - 1) << endl; // Different access ways.
	
	list<int> l;
	for (int i = 0; i < n; i++) {
		int rnd = rand() % 10;
		l.push_back(rnd); // Fast 
		cout << rnd << ' ';
	}
	cout << endl;
	for (int i = 0; i < n; i++) {
		int rnd = rand() % 10;
		l.push_front(rnd); // Also fast. 
		cout << rnd << ' ';
	}
	cout << endl;

	list<int>::iterator listIt = l.begin();
	// This iteration slows insertion down
	for (int i = 0; i < 5; i++) {
		listIt++; 
	}
	l.insert(listIt, 251); // This is fast due to inherent doubly linked list structure.
	cout << *listIt << endl; // Direct acess (at and []) is not possible .

	return 0;
}