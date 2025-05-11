#include <iostream>
#include "Person.h"
#include "Customer.h"
#include "Employee.h"
#include "Librarian.h"
#include "funcs.h"
#include <mariadb/mysql.h>
using namespace std;

void signUp(MYSQL* conn) {
	int input2;
	while (true) {
		system("clear");
		cout << "Select Account Type" << endl;
		cout << "[1] Customer" << endl;
		cout << "[2] Employee" << endl;
		cout << "[3] Librarian" << endl;
		cin >> input2;
			if (input2 == 1) {
				Customer c("Customer", conn);
				break;
			}
			else if (input2 == 2) {
				Employee e("Employee", conn);
				break;
			}
			else if (input2 == 3) {
				Librarian l("Librarian", conn);
				break;
			}
			else {
				cout << "Error, Please choose one of the given options." << endl;
			}
		}
}
//cout << "Sign Up Query: " << query << endl;


bool logIn(MYSQL* conn) {
	string username, password;
	cout << "Enter your username: " << endl;
    cin.ignore();
	getline(cin, username);
    cout << "Enter your password: " << endl;
    cin >> password;

	string query = "SELECT * FROM people WHERE name='" + username + "' AND password='" + password + "'; ";
//  cout << "Sign IN Query: " << query << endl;
	if (mysql_query(conn, query.c_str())) {
			cerr << "Log In Failed: " << mysql_error(conn) << endl;
			return false;
	}
	MYSQL_RES* res = mysql_store_result(conn);
	if (res == NULL) {
			cerr << "Log In Failed: " << mysql_error(conn) << endl;
			return false;
	}

	if (mysql_num_rows(res) > 0) cout << "" << endl;
	else {
			cout << "Log In Failed, Try Again." << endl;
			return false;
	}

    MYSQL_ROW row = mysql_fetch_row(res);
    if (row) {
        cout << "Welcome Back " << row[1] << "!" << endl;

        if (string(row[6]) == "Customer") {
            Customer c;
			wait_for_user_input();
           c.userFunc(username, conn);
        } else if (string(row[6]) == "Employee") {
            Employee e;
			wait_for_user_input();
            e.userFunc(username, conn);
        } else if (string(row[6]) == "Librarian") {
            Librarian l;
			wait_for_user_input();
            l.userFunc(username, conn);
        } else {
            cerr << "Error: Invalid account type." << endl;
        }
    }
		return true;
}

int main() {
	const char* host = "localhost";
    const char* username = "root";
    const char* password = "root";
    const char* database = "library";	
	MYSQL* conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, host, username, password, database, 0, NULL, 0)) {
        cerr << "MySQL connection failed: " << mysql_error(conn) << std::endl;
        return 0;
    }

	int input;
	string type;
	while (true) {
		system("clear");
		cout << "==============Welcome=============" << endl;
		cout << "[1] Sign Up" << endl;
		cout << "[2] Log In" << endl;
		cout << "[3] Exit" << endl;
		cin >> input;
		switch (input) {
			case 1:
				signUp(conn);
				break;
			case 2:
				logIn(conn);
				break;
			case 3:
				return 0;
				break;
			default:
				cout << "Error, Please choose one of the given options." << endl;
		}
			wait_for_user_input();
	}
	return 0;
}