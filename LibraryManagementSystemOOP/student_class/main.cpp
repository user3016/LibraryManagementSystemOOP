#include <iostream>
#include <string>
#include "student.h"
using namespace std;

void welcome() {
	cout << "===========================AL-NASS UNIVERSITY IN EGYPT (NUE)===============================\n";
	cout << "Welcome, please choose one of the following options: " << endl;
	cout << "If you are a new student, choose [1].\n";
	cout << "[1] Create an account.\n";
	cout << "[2] Display account info.\n";
	cout << "[3] Quit.\n";
}

int main() {
	int input;
	student student1;
	while (true) {
		system("clear");
		welcome();
		cin >> input;
		if (input == 1) {
			student1.setName();
			student1.setAge();
			student1.setEmail();
			student1.createUID();
		}
		else if (input == 2) {
			student1.printInfo();
		}
		else if (input == 3) {
			break;
		}
		else {
			cerr << "Error, please make sure you choose one of the previous options." << endl;
		}
	}
	return 0;
}
