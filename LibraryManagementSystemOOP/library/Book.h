#pragma once
#include <iostream>
#include <string>
using namespace std;

class Book {
private:
	string name, category, author;
	int BID;
	bool available;

public:
	Book(string n, string c, string a);

	bool isAvilable();
	void setName(string n);
	void setBID();
	void setCategory(string c);
	void setAuthor(string a);
	void changeState(bool a);

	string getName();
	int getBID();
	string getName();
	int getBID();
	string getCategory();
	string getAuthor();

	void getBookInfo();
};

