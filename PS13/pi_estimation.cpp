// With contributions from https://www.geeksforgeeks.org/estimating-value-pi-using-monte-carlo/
#include <iostream>
#include <random>
using namespace std;


int main(int argc, char const *argv[]) {
	const int randomPrecision = 100000;
	uniform_real_distribution<double> unif(-1, 1);
	default_random_engine re;

	int k = stoi(argv[1]);
	int insideTheCircleCount = 0;
	for (int i = 1; i <= k; i++) {
		double x = unif(re);
		double y = unif(re);
		if (x * x + y * y <= 1) {
			insideTheCircleCount++;
		}

		if (i % 1000 == 0) {
			cout << "The pi estimation for k=" << i << " is: " << 4 * (insideTheCircleCount + 0.0) / i << endl;
		}
	}

	return 0;
}