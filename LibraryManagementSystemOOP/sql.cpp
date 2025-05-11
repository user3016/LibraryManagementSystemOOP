#include <iostream>
#include <fstream>
#include <mariadb/mysql.h>
//#include <mariadb/mysql_error.h>
#include <string>
using namespace std;

int main() {
    const char* host = "localhost";
    const char* username = "root";
    const char* password = "root";
    const char* database = "test";
    const char* query;

    MYSQL* conn = mysql_init(NULL);
    MYSQL_RES* res;
    MYSQL_ROW row;

    if (!mysql_real_connect(conn, host, username, password, database, 0, NULL, 0)) {
        cerr << "MySQL connection failed: " << mysql_error(conn) << std::endl;
        return 1;
    }

    query = "INSERT INTO users (name, age, password) VALUES ('Youssef Essam', 22, 'mypass');";
    if (mysql_query(conn, query)) {
        cerr << "Query failed: " << mysql_error(conn) << endl;
        return 0;
    }

    res = mysql_store_result(conn);

    while ((row = mysql_fetch_row(res)) != NULL) {
        for(int i = 0; i < mysql_num_fields(res); i++) {
            cout << row[i] << " ";
        }
        cout << endl;
    }

    mysql_free_result(res);
    mysql_close(conn);

    return 0;
}
