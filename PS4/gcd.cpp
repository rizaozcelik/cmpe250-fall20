#include <iostream>
#include <chrono>

using namespace std;

int gcd1(int num1, int num2){ //Brute Force Algorithm

    int counter = 1;
    int result = 1;

    while( counter <= num1 && counter <= num2 ){

        if( num1 % counter == 0 && num2 % counter == 0 ){
            result = counter;
        }

        counter++;
    }
    return result;
}

int gcd2(int num1,int num2){ // Recursion way of Euclid Algorithm

    if( num1 == num2) return num1;

    if( num1 > num2) return gcd2(num1-num2 , num2);

    else return gcd2(num1,num2-num1);

}

int gcd3(int num1, int num2){ // Non-Recursive way of Euclid Algorithm

    while(num1 != num2){
        if(num1 > num2){
            num1 -= num2;
        }
        else{
            int temp = num2;
            num2 = num1;
            num1 = temp;
        }
    }
    return num1;
}

int main( int argc , char const * argv[]){

    int result;
    int num1,num2;

    // Generating random in a specific range. Change this in order to change input
    num1 = rand() % 1000000 + 10000;
    num2 = rand() % 10000 + 10000;

    auto start = chrono::high_resolution_clock().now();

    result = gcd1( num1,num2 ); // Running first algorithm

    auto stop = chrono::high_resolution_clock().now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
    int elapsed = duration.count();

    cout << "Time cost in gcd1: " << elapsed << endl;
    cout << result;

    cout << endl;

    start = chrono::high_resolution_clock().now();

    result = gcd2( num1,num2 ); // Running second algorithm

    stop = chrono::high_resolution_clock().now();
    duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
    elapsed = duration.count();

    cout << "Time cost in gcd2: " << elapsed << endl;
    cout << result;

    cout << endl;

    start = chrono::high_resolution_clock().now();

    result = gcd3( num1,num2 ); // Running third algorithm

    stop = chrono::high_resolution_clock().now();
    duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
    elapsed = duration.count();

    cout << "Time cost in gcd3: " << elapsed << endl;
    cout << result;

    cout << endl;


    return 0;
}
