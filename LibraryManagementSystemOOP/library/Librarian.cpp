#include "Librarian.h"
#include "funcs.h"
#include <iostream>
#include <mariadb/mysql.h>
#include <ctime>
#include <vector>
using namespace std;

Librarian::Librarian() {

}

Librarian::Librarian(string t, MYSQL* conn) : Employee(t, conn){
}

void Librarian::addBook(MYSQL* conn) {
	string book_name, category, author;
	int book_id;
	cout << "Enter book's name: " << endl;
	cin.ignore();
	getline(cin, book_name);

	cout << "Enter book's category: " << endl;
	cin.ignore();
	getline(cin, category);

	cout << "Enter book's author: " << endl;
	cin.ignore();
	getline(cin, author);

	srand(time(0));
	book_id = 1 + rand() % 10000;

	string query = "INSERT INTO books (name, BID, category, author, available) VALUES ('" + book_name + "', '" + to_string(book_id) + "', '" + category + "', '" + author + "', 'Yes');";
	if (mysql_query(conn, query.c_str())) {
		cerr << "Query Failed, please try again." << mysql_error(conn) << endl;
		return;
	}
	cout << "Book Added." << endl;
}

void Librarian::removeBook(MYSQL* conn) {
	int book_id;
	cout << "Enter Book ID: " << endl;
	cin >> book_id;
	string query = "DELETE FROM books WHERE id='" + to_string(book_id) + "';";
	if (mysql_query(conn, query.c_str())) {
		cerr << "Query Failed, check the book's ID and try again." << mysql_error(conn) << endl;
		return;
	}
	else {
		cout << "Book Removed." << endl;
	}
}

void Librarian::getBookInfo(MYSQL* conn) {
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

void Librarian::userFunc(string userName, MYSQL* conn) {
	int input;
	while (true) {
		system("clear");
		cout << "Choose one of the following options." << endl;
		cout << "[1] Add Book" << endl;
		cout << "[2] Remove Book" << endl;
		cout << "[3] Get Book Info" << endl;
		cout << "[4] Get Account Info" << endl;
		cout << "[5] Exit" << endl;
		cin >> input;
		switch (input) {
			case 1:
				addBook(conn);
				break;
			case 2:
				removeBook(conn);
				break;
			case 3:
				getBookInfo(conn);
				break;
			case 4:
				Employee::getAccountInfo(userName, conn);
				break;
			case 5:
				return;
			default:
				cerr << "Error, please choose one of the given options." << endl;
		}
		wait_for_user_input();
	}
}
//call employee get info

//call employee add to database;
