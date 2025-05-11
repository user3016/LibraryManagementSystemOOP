#include "Book.h"
#include <string>
#include <ctime>
using namespace std;


Book::Book(string n, string c, string a) : name(n), category(c), author(a) {
	setBID();
	available = true;
}

bool Book::isAvilable()
{
	if (available) return true;
	else return false;
}

void Book::setName(string n) {
	name = n;
}

void Book::setBID() {
	int x = time(0);
	srand(x);
	BID = 1 + rand() % 10000;
}

void Book::setCategory(string c) {
	category = c;
}

void Book::setAuthor(string a) {
	author = a;
}

void Book::changeState(bool a) {
	available = a;
}


string Book::getName()
{
	return name;
}

int Book::getBID()
{
	return BID;
}

string Book::getCategory()
{
	return category;
}

string Book::getAuthor()
{
	return author;
}

void Book::getBookInfo() {
	cout << "Name: " << name << endl;
	cout << "BID: " << BID << endl;
	cout << "Category: " << category << endl;
	cout << "Author: " << author << endl;
	if (available) cout << "Avilable: Yes" << endl;
	else cout << "Avilable: No" << endl;
}
