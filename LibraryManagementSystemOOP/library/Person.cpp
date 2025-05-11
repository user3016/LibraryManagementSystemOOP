#include "Person.h"
#include <iostream>
#include <string>
#include <mariadb/mysql.h>
#include <vector>
using namespace std;

Person::Person() {

}

Person::Person(string t, MYSQL* conn) {
	cout << "Enter your name: " << endl;
	cin.ignore();
	getline(cin, name);

	cout << "Enter your gender: " << endl;
	cin >> gender;

	cout << "Enter your email: " << endl;
	cin >> email;

	cout << "Enter your phone number: " << endl;
	cin >> phoneNumber;

	cout << "Enter your age: " << endl;
	cin >> age;

	type = t;

	cout << "Enter your password: " << endl;
	cin >> password;

	AddToDatabase(conn);
}

void Person::setName(string n) {
	name = n;
}

void Person::setGender(string g) {
	gender = g;
}

void Person::setEmail(string e) {
	email = e;
}

void Person::setPhoneNumber(string pn) {
	phoneNumber = pn;
}

void Person::setAge(int a) {
	age = a;
}

string Person::getName() {
	return name;
}

string Person::getGender() {
	return gender;
}

string Person::getEmail() {
	return email;
}

string Person::getPhoneNumber() {
	return phoneNumber;
}

int Person::getAge() {
	return age;
}

string Person::getPassword() {
	return password;
}

void Person::getAccountInfo(string userName, MYSQL* conn) {
	vector<string> fields = {"Name: ", "Gender: ", "Age: ", "Phone Number: ", "Email: ", "Account Type: ", ""};
	string query = "SELECT * FROM people WHERE name='" + userName + "'";
	if (mysql_query(conn, query.c_str())) {
		cerr << "Query Failed. check your username and try again." << mysql_error(conn) << endl;
		return;
	}
	MYSQL_RES* res = mysql_store_result(conn);
	MYSQL_ROW row;
        int num_fields = mysql_num_fields(res);

    while ((row = mysql_fetch_row(res))) {
        for(int i = 1; i < num_fields - 1; i++) {
                if (row[i]) {
                	cout << fields[i-1] << row[i] << " " << endl; // Print field value
                } else {
            cout << "NULL " << endl; // Handle NULL values
        }
    }
	}
}

void Person::AddToDatabase(MYSQL* conn) {
		string query = "INSERT INTO people (name, gender, age, phone_number, email, type, password) VALUES ('" 
				+ name + "', '" 
				+ gender + "', " 
				+ to_string(age) + ", '" 
				+ phoneNumber + "', '" 
				+ email + "', '" 
				+ type + "', '" 
				+ password + "');";

		if (mysql_query(conn, query.c_str())) {
			cerr << "Query Failed: " << mysql_error(conn) << endl;
			return;
        }
}

