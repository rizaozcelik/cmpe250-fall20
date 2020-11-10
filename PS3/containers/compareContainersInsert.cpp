#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <stack>
#include <list>
#include <chrono>
#include <fstream>

using namespace std;

int N = 1000000;
// int N = 10;

template <typename Container>
void printContainer(Container container) {
	for (typename Container::iterator it=container.begin(); it != container.end(); it++) {
		cout << *it << ' ';
	}
	cout << endl;
}

void saveTimes(list<int>& times, string filename) {
	ofstream out;
	out.open("./measurements/" + filename, ios_base::app);
	for (list<int>::iterator it = times.begin(); it != times.end(); it++) {
		out << *it << " ";
	}
	out << endl;
	out.close();
}

template <typename Container>
void append(Container container, string filename) {
	list<int> times;
	for (int i = 0; i < N; i++) {
		int rnd = rand() % 20;
		// cout << rnd << " ";
		auto start = chrono::high_resolution_clock().now();
		container.push_back(rnd);
		auto stop = chrono::high_resolution_clock().now();
		auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start); 
	  	int elapsed = duration.count();
	  	// cout << elapsed << " ";
	  	times.push_back(elapsed);
	}
	// cout << endl;
	// printContainer(container);
	saveTimes(times, filename);
}


template <typename Container>
void prepend(Container container, string filename) {
	list<int> times;
	for (int i = 0; i < N; i++) {
		int rnd = rand() % 20;
		// cout << rnd << " ";
		auto start = chrono::high_resolution_clock().now();
		container.insert(container.begin(), rnd);
		auto stop = chrono::high_resolution_clock().now();
		auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start); 
	  	int elapsed = duration.count();
	  	// cout << elapsed << " ";
	  	times.push_back(elapsed);
	}
	// cout << endl;
	// printContainer(container);
	saveTimes(times, filename);
}


template <typename Container>
void insertMiddleDirectAccess(Container container, string filename) {
	list<int> times;
	for (int i = 0; i < N; i++) {
		int rnd = rand() % 20;
		// cout << rnd << " ";
		auto start = chrono::high_resolution_clock().now();
		container.insert(container.begin() + i / 2, rnd);
		auto stop = chrono::high_resolution_clock().now();
		auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start); 
	  	int elapsed = duration.count();
	  	// cout << elapsed << " ";
	  	times.push_back(elapsed);
	}
	// cout << endl;
	// printContainer(container);
	saveTimes(times, filename);
}

template <typename Container>
void insertMiddleIterator(Container container, string filename) {
	container.push_front(0); // Just a starter for convenience
	// cout << "0 ";
	typename Container::iterator it = container.begin(); 
	list<int> times;
	for (int i = 0; i < N; i++) {
		int rnd = rand() % 20;
		// cout << rnd << " ";
		auto start = chrono::high_resolution_clock().now();
		if (i % 2 == 0 && i != 0) {
			it--;
		}
		container.insert(it, rnd);
		auto stop = chrono::high_resolution_clock().now();
		auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start); 
	  	int elapsed = duration.count();
	  	times.push_back(elapsed);
	}
	saveTimes(times, filename);
}


int main(int argc, char const *argv[]) {

	for (int i = 0; i < 10; i++) {
		append(vector<int>(), "vector_append.txt");
		append(deque<int>(), "deque_append.txt");	
		append(list<int>(), "list_append.txt");
		cout << "Done append" << endl;

		prepend(vector<int>(), "vector_prepend.txt");
		prepend(deque<int>(), "deque_prepend.txt");	
		prepend(list<int>(), "list_prepend.txt");
		cout << "Done prepend" << endl;

		insertMiddleDirectAccess(vector<int>(), "vector_middle.txt");
		insertMiddleDirectAccess(deque<int>(), "deque_middle.txt");	
		insertMiddleIterator(list<int>(), "list_middle.txt");
		cout << "Done " << i << endl; 
	}
	return 0;
}