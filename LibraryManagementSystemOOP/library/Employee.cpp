#include <iostream>
#include "Person.h"
#include "Employee.h"
#include "funcs.h"
#include <string>
#include <ctime>
#include <mariadb/mysql.h>
#include <vector>
using namespace std;

Employee::Employee() {}

Employee::Employee(string t, MYSQL* conn) : Person(t, conn) {
    cout << "Enter your title: " << endl;
    cin >> title;

    setID();
    setSalary();
    setWorkingHours();

    AddToDatabase(conn);
}

void Employee::setID() {
        int x = time(0);
        srand(x);
        employee_id = 1 + rand() % 10000;
    }

    void Employee::setSalary() {
        int x = time(0);
        srand(x);
        salary = 1 + rand() % 10000;
    }

    void Employee::setWorkingHours() {
        int x = time(0);
        srand(x);
        working_hours = 1 + rand() % 10000;
    }



    string Employee::getTitle() {
        return title;
    }

    int Employee::getID() {
        return employee_id;
    }

    int Employee::getSalary() {
        return salary;
    }

    int Employee::getWorkingHours() {
        return working_hours;
    }

void Employee::getAccountInfo(string userName, MYSQL* conn) {
	vector<string> fields = {"Name: ", "Gender: ", "Age: ", "Phone Number: ", "Email: ", "Account Type: ", "Title: ", "Employee ID: ", "Salary: ", "Working Hours: ", ""};
	string query = "SELECT * FROM employees WHERE name='" + userName + "'";
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

    void Employee::AddToDatabase(MYSQL* conn) {
    	string query = "INSERT INTO employees (name, gender, age, phone_number, email, title, employee_id, salary, working_hours, password) VALUES ('" 
				+ getName() + "', '" 
				+ getGender() + "', " 
				+ to_string(getAge()) + ", '" 
				+ getPhoneNumber() + "', '" 
				+ getEmail() + "', '" 
                + title + "', '" 
                + to_string(employee_id) + "', '" 
                + to_string(salary) + "', '" 
                + to_string(working_hours) + "', '" 
				+ getPassword() + "');";

		if (mysql_query(conn, query.c_str())) {
			cerr << "Query Failed: " << mysql_error(conn) << endl;
			return;
        }
        else {
            cout << "Sign Up Successful" << endl;
        }
    }

void Employee::userFunc(string userName, MYSQL* conn) {
    int input;
    while (true) {
        system("clear");
        cout << "[1] Get Account Info" << endl;
        cout << "[2] Exit" << endl;
        cin >> input;
        if (input == 1) {
            getAccountInfo(userName, conn);
        }
        else if (input == 2) {
            return;
        }
        else {
            cout << "Please select one of the given options." << endl;
        }
            wait_for_user_input();
    }
}


