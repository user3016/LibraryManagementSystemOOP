#include <string>
using namespace std;

class student {
private:
	string name;
	string email;
	int age;
	float GPA = 4.5;
	int UID;

public:
	void setName();
	void setAge();
	void setEmail();
	int createUID();
	void printInfo();
};

