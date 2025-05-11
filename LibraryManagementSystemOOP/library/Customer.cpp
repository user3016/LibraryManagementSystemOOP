#include "Customer.h"
#include "Person.h"
#include "funcs.h"
#include <iostream>
#include <mariadb/mysql.h>
#include <string>
#include <vector>
using namespace std;


Customer::Customer() {

}

Customer::Customer(string t, MYSQL* conn) : Person(t, conn) {
	AddToDatabase(conn);
}

void Customer::getBookInfo(MYSQL* conn) {
    vector<string> fields = {"Name: ", "Book ID: ", "Category: ", "Author: ", "Available: "};

    string book_name;
    cout << "Enter Book Name: " << endl;
    cin.ignore();
    getline(cin, book_name);

    string query = "SELECT * FROM books WHERE name='" + book_name + "';";
    if (mysql_query(conn, query.c_str())) {
        cerr << "Query Failed, check the book name and try again: " << mysql_error(conn) << endl;
        return;
    }

    MYSQL_RES* res = mysql_store_result(conn);
    if (res == NULL) {
        cerr << "Query Failed, check the book name and try again: " << mysql_error(conn) << endl;
        return;
    }

    MYSQL_ROW row;
    int num_fields = mysql_num_fields(res);

    while ((row = mysql_fetch_row(res))) {
        for (int i = 1; i < num_fields; i++) { // Start from 1 to skip ID field, stop before the last field
            if (row[i]) {
                cout << fields[i-1] << row[i] << endl; // Print the field label and value
            } else {
                cout << fields[i-1] << "NULL" << endl; // Handle NULL values
            }
        }
    }

    mysql_free_result(res); // Free the result after use
}





void Customer::borrowBook(MYSQL* conn) {
	int book_id;
	cout << "Enter Book ID: " << endl;
	cin >> book_id;
	string query = "UPDATE books SET available='No' WHERE BID='" + to_string(book_id) + "';";
	if (mysql_query(conn, query.c_str())) {
		cerr << "Query Failed. check the book's ID and try again." << mysql_error(conn) << endl;
		return;
	}
	cout << "Borrowed Book." << endl;
}



void Customer::buyBook(MYSQL* conn) {
	int book_id;
	cout << "Enter Book ID: " << endl;
	cin >> book_id;
	string query = "UPDATE books SET available='No' WHERE BID='" + to_string(book_id) + "';";
	if (mysql_query(conn, query.c_str())) {
		cerr << "Query Failed. check the book's ID and try again." << mysql_error(conn) << endl;
		return;
	}
	cout << "Bought Book." << endl;
}

void Customer::AddToDatabase(MYSQL* conn) {
	string query = "INSERT INTO customers (name, gender, age, phone_number, email, password) VALUES ('" 
				+ getName() + "', '" 
				+ getGender() + "', " 
				+ to_string(getAge()) + ", '" 
				+ getPhoneNumber() + "', '" 
				+ getEmail() + "', '" 
				+ getPassword() + "');";

	if (mysql_query(conn, query.c_str())) {
		cerr << "Query Failed: " << mysql_error(conn) << endl;
		return;
	}
	else {
		cout << "Sign Up Successful" << endl;
	}
}

void Customer::userFunc(string userName, MYSQL* conn) {
	int input;
	while (true) {
		system("clear");
		cout << "[1] Get Book Info" << endl;
		cout << "[2] Borrow Book" << endl;
		cout << "[3] Buy Book" << endl;
		cout << "[4] Get Account Info" << endl;
		cout << "[5] Exit" << endl;
		cin >> input;
		if (input == 1) {
			getBookInfo(conn);
		}
		else if (input == 2) {
			borrowBook(conn);
		}
		else if (input == 3) {
			buyBook(conn);
		}
		else if (input == 4) {
			Person::getAccountInfo(userName, conn);
		}
		else if (input == 5) {
			return;
		}
		else {
			cout << "Please select one of the given options." << endl;
		}
			wait_for_user_input();
	}
}

