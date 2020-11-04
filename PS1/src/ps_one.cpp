#include <iostream>
#include <string>

using namespace std;

// Does not even compile! If parameter is const, it cannot be at LHS!
// void make_me_famous_v3(const string& name) {
// 	if (name == "Walter White") {
// 		name = "Heisenberg";
// 	} 

// }

void make_me_famous_v2(string& name) {
	if (name == "WalterWhite") {
		name = "Heisenberg";
	} 
}


// Does not work as expected
void make_me_famous_v1(string name) {
	if (name == "WalterWhite") {
		name = "Heisenberg";
	} 
}


string make_me_famous_v0(string name) {
	if (name == "WalterWhite") {
		name = "Heisenberg";
	} 
	return name;
}


int main(int argc, char const *argv[]) {
	cout << "What is your name, yo?" << endl;
	string name;
	cin >> name;

	string name_v0 = make_me_famous_v0(name);
	cout << "You are now " << name_v0 << endl;
	
	make_me_famous_v2(name);
	cout << "You are now " << name << endl;
	
	// make_me_famous_v3(name);
	// cout << name << endl;

	// bool there_is_a_problem = false;
	// if (name == "Heisenberg") {
	// 	there_is_a_problem = false;
	// } else {
	// 	there_is_a_problem = true;
	// }

	// if (there_is_a_problem) {
	// 	cout << "Cops are here! Hide the stashes!" << endl;
	// } else {
	// 	cout << "Welcome to your turf " << name << endl;
	// }

	/* 
	These lines can be shorthened to:
	if (name == "Heisenberg") {
		cout << "Welcome to your turf " << name << endl;
	} else {
		cout << "Cops are here! Hide the stashes!" << endl;
	}
	*/

	return 0;
}