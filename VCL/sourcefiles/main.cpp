#include "headerfiles/main_window.h"

#include <iostream>

#include <QApplication>
/*#include "sqlite\sqlite3.h"

static int callback(void * , int argc, char **argv, char **azColName) {
    int i;
    for (i = 0; i<argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}
*/
int main(int argc, char *argv[])
{
    /*const char *sql = "CREATE TABLE Files("  \
        "ID INT PRIMARY KEY     NOT NULL," \
        "Name           TEXT    NOT NULL," \
        "Directory            TEXT     NOT NULL );";
    const char* name = "baza.db";
    char *zErrMsg = 0;
    sqlite3* con;
    //sqlite3_initialize();
    sqlite3_open(name, &con);
    sqlite3_exec(con, sql, callback, 0, &zErrMsg);
    sql = "insert into Files values ('0', 'a', 'b');";
    sqlite3_exec(con, sql, callback, 0, &zErrMsg);
    sqlite3_close(con);*/
    //sqlite3_shutdown();

	QApplication a(argc, argv);
	MainWindow w(argc, argv);
	w.show();
	return a.exec();
}