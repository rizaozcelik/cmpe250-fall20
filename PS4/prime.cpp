#include <iostream>
#include <list>
#include <vector>
#include <chrono>
/**
 * Information about Sieve of Eratosthenes
 * https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
 * https://youtu.be/Da8qe1TRwuo?t=3
 *
 * */

using namespace std;

/**
 * The print command for any type of container
 * Taken from previous Ps
 * 
 * */
template <typename Container>
void printContainer(Container container) {
    for (typename Container::iterator it=container.begin(); it != container.end(); it++) {
        cout << *it << ' ';
    }
    cout << endl;
}
/**
 * Brute Force Algorithm
 * 
 * */
vector<int> primev1(int n){  

    vector<int> result;

    for(int i = 2 ; i < n ; i++){

        bool prime = true;
        for( int j = 2 ; j  < i ; j++){

            if( i % j == 0){
                prime = false;
                break;
            }
        }
        if(prime) {
            result.push_back(i);
        }

    }
    return result;
}

/**
 * Improvement in second for loop.
 * 
 * */
vector<int> primev2(int n){

    vector<int> result;

    for(int i = 2 ; i < n ; i++){

        bool prime = true;
        for( int j = 2 ; j * j < i ; j++){

            if( i % j == 0){
                prime = false;
                break;
            }
        }
        if(prime) {
            result.push_back(i);
        }

    }
    return result;
}

/**
 * More improvement in second loop.
 * Traverse the prime number arrays to detect prime number. 
 * 
 * */
vector<int> primev3(int n){

    vector<int> result;
    result.push_back(2);
    for(int i =3 ; i < n ; i++){

        bool prime = true;

        for( int temp : result){
            if(temp * temp > i){
                break;
            }
            if( i % temp == 0){
                prime = false;
                break;
            }
        }
        if(prime) {
            result.push_back(i);
        }

    }
    return result;
}

/**
 * Sieve of Eratosthenes
 * 
 * */
vector<int> primev4(int n){
    vector<bool> container(n+1, true);
    vector<int> primes;

    for (int i = 2; i <= n ; i++){
        if(container[i] == false)
            continue;

        for(int j = i*2; j <= n ; j += i )
            container[j] = false;
    }
    for ( int i = 2; i<= n ; i++){
        if(container[i] == true) primes.push_back(i);
    }
    return primes;

}

int main(int argc, char const *argv[])
{
    vector<int> result;
    int number;
    cin >> number;

    auto start = chrono::high_resolution_clock().now();

    result = primev1( number );

    auto stop = chrono::high_resolution_clock().now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
    int elapsed = duration.count();

    cout << "Time cost of v1: " << elapsed << endl;
    //printContainer(result);

    cout << endl;

    start = chrono::high_resolution_clock().now();

    result = primev2( number );

    stop = chrono::high_resolution_clock().now();
    duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
    elapsed = duration.count();
    cout <<  "Time cost of v2: " << elapsed << endl;
    //printContainer(result);

    cout << endl;

    start = chrono::high_resolution_clock().now();

    result = primev3( number );

    stop = chrono::high_resolution_clock().now();
    duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
    elapsed = duration.count();
    cout <<  "Time cost of v3: " << elapsed << endl;
    //printContainer(result);

    cout << endl;

    start = chrono::high_resolution_clock().now();

    result = primev4( number );

    stop = chrono::high_resolution_clock().now();
    duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
    elapsed = duration.count();
    cout <<  "Time cost of v4: " << elapsed << endl;
    //printContainer(result);

    cout << endl;
    /**
     * In order to try input dependent exec. time
     * Run the code below
     * 
     * */
//    for( int n = 10 ; n < 100000; n+= 1000){
//        start = chrono::high_resolution_clock().now();
//        primev1( n );
//        stop = chrono::high_resolution_clock().now();
//        duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
//        elapsed = duration.count();
//        cout <<  "Time cost: " << elapsed << endl;
//    }

    return 0;
}