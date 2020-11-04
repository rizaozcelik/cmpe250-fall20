#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char const *argv[])
{
	
	// Simple IO
	cout << "Hello, World!" << endl;

	float f = 3.5;
	int i = 3;
	bool b = true;
	char c = 'a';
	string s = "Hello, World";
	cout << f << i << b << c << s << '\n'; 

	string name;

	cout << "what is your name, yo?\n";
	cin >> name;
	cout << "Lets cook!" << name << "\n";


	// File IO with the filenames from terminal
	cout << argc << argv[0]; // Prints the number of terminal arguments and the first argument: name of the program 

	ifstream infile;
	infile.open(argv[1]); // Open the inputfile specified from terminal.

	string surname;
	int age;
	infile >> name >> surname >> age; // Read from file to variable. Yep, this simple!
	infile.close();
	cout << "Read from file\n";

	ofstream outfile;
	outfile.open(argv[2]);
	outfile << "Welcome " << name << " " << surname << " You are " << age << " years old!" << endl;
	outfile.close();

	return 0;
}

