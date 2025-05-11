#pragma once
#include <string>
#include <mariadb/mysql.h>
using namespace std;
class Person {

private:

	string name, gender, email, phoneNumber, type, password;
	int age;



public:
	Person();
	Person(string t, MYSQL* conn);


	void setName(string n);
	void setGender(string g);
	void setEmail(string e);
	void setPhoneNumber(string pn);
	void setAge(int a);



	string getName();
	string getGender();
	string getEmail();
	string getPhoneNumber();
	int getAge();
	string getPassword();
	
	void getAccountInfo(string userName, MYSQL* conn);

	void AddToDatabase(MYSQL* conn);

};



