#include <iostream>

using namespace std;

void changeMyNameRaw(string name) {
	name = "Heisenberg";
}

void changeMyNamePtr(string* name) {
	*name = "Heisenberg";
}

void changeMyNameAlias(string& name) {
	name = "Heisenberg";
}

int main(int argc, char const *argv[]){
	string name = "Walter White";
	changeMyNameRaw(name); 
	cout << name << endl; // Did not change


	name = "Walter White";
	string* name_ptr = &name;
	cout << name_ptr << endl; // 0x7ffebccef860 (or a different address in your computer)
	changeMyNamePtr(name_ptr); 
	cout << name << endl; // Did change


	name = "Walter White";
	changeMyNameAlias(name); 
	cout << name << endl; // Did change

	string& alias = name;
	cout << "Before the change " << alias << " and " << name << endl; 
	alias = "Jesse Pinkman, yo";
	cout << "After the change " << alias << " and  " << name << endl; 

	int arrLen = 10;
	int* int_arr = new int[arrLen];
	int* int_arr_ptr = int_arr;
	cout << "Intger array (squareds):" << endl;
	for (int i=0; i < arrLen; i++) {
		// int_arr[i] = i * i;
		*(int_arr_ptr + i) = i * i;
	}

	for (int i=0; i < arrLen; i++) {
		cout << int_arr[i] << ' ';
	}
	cout << endl;

	float* float_arr = new float[arrLen];
	float* float_arr_ptr = float_arr;
	cout << "Float array (cubes):" << endl;
	for (int i = 0; i < arrLen; i++) {
		*float_arr_ptr = i * i * i;
		// float_arr_ptr++; // Also works
		float_arr_ptr = float_arr_ptr + 1;
		cout << float_arr_ptr << endl; // The addresses increment by 4 bytes (32 bits).
	}

	for (int i = 0; i < arrLen; i++) {
		cout << float_arr[i] << ' ';
	}
	cout << endl;
	
	double* double_arr = new double[arrLen];
	double* double_arr_ptr = double_arr;
	cout << "Double array (fourth powers):" << endl;
	for (int i = 0.0; i < arrLen; i++) {
		*double_arr_ptr = i * i * i * i;
		// long_arr_ptr++;
		double_arr_ptr = double_arr_ptr + 1; // You might expect a problem due to size of a double by problem is averted by C++
		cout << double_arr_ptr << endl; // The addresses increment by 8 bytes. (64 bits).
	}

	for (int i = 0; i < arrLen; i++) {
		cout << double_arr[i] << ' ';
	}
	return 0;
}