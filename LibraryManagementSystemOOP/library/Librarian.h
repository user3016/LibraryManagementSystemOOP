#pragma once
#include "Employee.h"
#include <mariadb/mysql.h>

class Librarian : public Employee {


public:
	Librarian();
	Librarian(string t, MYSQL* conn);
	void addBook(MYSQL* conn);
	void removeBook(MYSQL* conn);
	void getBookInfo(MYSQL* conn);

	void userFunc(string userName, MYSQL* conn);
};

