#pragma once
#include <string>
#include "Person.h"
#include <mariadb/mysql.h>
using namespace std;

class Customer : public Person {

private:
	// int borrowed_books, bought_books;

public:
	Customer();
	Customer(string t, MYSQL* conn);
	void getBookInfo(MYSQL* conn);
	void borrowBook(MYSQL* conn);
	void buyBook(MYSQL* conn);

	void AddToDatabase(MYSQL* conn);

	void userFunc(string userName, MYSQL* conn);

};



