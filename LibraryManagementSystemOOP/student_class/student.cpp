#include "student.h"
#include <iostream>
#include <stdlib.h>
#include <ctime>
using namespace std;

string s = "Your Name";
int n;

void student::setName() {
	cout << "Enter your name: " << endl;
	cin.ignore();
	getline(cin, s);
	name = s;
}

void student::setAge() {
	cout << "Enter your age: " << endl;
	cin >> n;
	age = n;
}

void student::setEmail() {
	cout << "Enter your email: " << endl;
	cin >> s;
	email = s;
}

int student::createUID() {
	int x = time(0);
	srand(x);
	UID = 1 + rand() % 10000;
	return UID;
}

void student::printInfo() {
	cout << "Name: " << name << endl;
	cout << "Age: " << age << endl;
	cout << "Email: " << email << endl;
	cout << "UID: " << UID << endl;
	cout << "GPA: " << GPA << endl;
	cout << "Press Enter to exit." << endl;
	cin.ignore();
	cin.get();
}



