#include <iostream>
#include <cmath>
using namespace std;

bool isPrime(int n, int k) {
	for (int i = 1; i <= k; i++) {
		int a = 2 + rand() % (n - 3);
		if (a < 2 || a > n - 2) {
			cout << "There is a huge error!\n";
		} 
		if ((long) pow(a, n - 1) % n != 1) {
			cout << "The equality is not satisfied for a: " << a << '\n';
			return false;
		}
	}
	return true;
}

int main(int argc, char const *argv[]) {
	int n = stoi(argv[1]);
	int k = stoi(argv[2]);

	if (isPrime(n, k)) {
		cout << n << " is probably prime\n";
	} else {
		cout << n << " is definitely not prime\n";
	}

	return 0;
}