#pragma once
#include "Person.h"
#include <string>
#include <ctime>
#include <mariadb/mysql.h>
using namespace std;



class Employee : public Person {

private:

    string title;
    int employee_id, salary, working_hours;



public:
    Employee();

    Employee(string t, MYSQL* conn);

    void setID();
    void setSalary();
    void setWorkingHours();



    string getTitle();
    int getID();
    int getSalary();
    int getWorkingHours();

    void getAccountInfo(string userName, MYSQL* conn);

	void AddToDatabase(MYSQL* conn);

	void userFunc(string userName, MYSQL* conn);
};



