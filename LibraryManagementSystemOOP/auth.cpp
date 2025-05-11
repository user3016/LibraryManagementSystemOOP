#include <iostream>
#include <mariadb/mysql.h>
#include <string>
using namespace std;

void welcome() {
        system("clear");
        cout << "==============Welcome=============" << endl;
        cout << "Choose one of the following options: " << endl;
        cout << "[1] Sign Up" << endl;
        cout << "[2] Log In" << endl;
        cout << "[3] Exit " << endl;
}

void signUp(MYSQL* conn) {
        string username, password;
        int age;
        cout << "Enter your username: " << endl;
        cin.ignore();
        getline(cin, username);
        cout << "Enter your age: " << endl;
        cin >> age;
        cout << "Enter your password: " << endl;
        cin >> password;

        string query = "INSERT INTO users (username, age, password) VALUES ('" + username + "', " + to_string(age) + " ,'" + password + "');";

        if (mysql_query(conn, query.c_str())) {
                cerr << "Query Failed: " << mysql_error(conn) << endl;
                return;
        }
        else {
                cout << "Sign Up Successful" << endl;
        }

//cout << "Sign Up Query: " << query << endl;
}

bool logIn(MYSQL* conn) {
        string username, password;
        cout << "Enter your username: " << endl;
    cin.ignore();
        getline(cin, username);
    cout << "Enter your password: " << endl;
    cin >> password;

        string query = "SELECT * FROM users WHERE username='" + username + "' AND password='" + password + "'; ";
//      cout << "Sign IN Query: " << query << endl;
        if (mysql_query(conn, query.c_str())) {
                cerr << "Log In Failed: " << mysql_error(conn) << endl;
                return false;
        }
        MYSQL_RES* res = mysql_store_result(conn);
        if (res == NULL) {
                cerr << "Log In Failed: " << mysql_error(conn) << endl;
                return false;
        }

        if (mysql_num_rows(res) > 0) cout << "Welcome Back!" << endl;
        else {
                cout << "Log In Failed, Try Again." << endl;
                return false;
        }

// PRINT (res)
/*
        MYSQL_ROW row;
        int num_fields = mysql_num_fields(res);

        while ((row = mysql_fetch_row(res))) {
        for(int i = 0; i < num_fields; i++) {
                // Print each field in the row
                if (row[i]) {
                 cout << row[i] << " "; // Print field value
                } else {
            cout << "NULL "; // Handle NULL values
        }
    }
    cout << endl; // Newline after each row
}
*/

        mysql_free_result(res);
        return true;
}

int main() {
        const char* host = "localhost";
        const char* username = "root";
        const char* password = "root";
        const char* database = "test";

        MYSQL* conn = mysql_init(NULL);
    MYSQL_RES* res;
    MYSQL_ROW row;

    if (!mysql_real_connect(conn, host, username, password, database, 0, NULL, 0)) {
        cerr << "MySQL connection failed: " << mysql_error(conn) << std::endl;
        return 0;
    }

        //const char* query;
        int input;
        while (true) {
                welcome();
                cin >> input;
                switch(input) {
                case 1:
                        signUp(conn);
                        break;
                case 2:
                        logIn(conn);
                        break;
                case 3:
                        cout << "GoodBye!" << endl;
                        return 0;
                default:
                        cout << "Please choose one of the given options." << endl;
                }
        cout << "\nPress Enter to continue...";
        cin.ignore(); // Ignore the newline character from previous input
        cin.get(); 
        }
        return 0;
}
