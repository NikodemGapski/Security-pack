#include <iostream>
#include <sstream>
#include "sqlite3.h"
#include "Error.h"
#include "DatabaseConnection.h"


namespace DBConnect {
	std::string DBConnect::User::getLogin() {
		return login;
	}
	int User::getH_Password() {
		return h_password;
	}

	void User::setLogin(std::string _login) {
		login = _login;
	}
	void User::setH_Password(int _h_password) {
		h_password = _h_password;
	}

	User::User(std::string _login, int _hash) {
		login = _login;
		h_password = _hash;
	}
	User::User() {
		login = "";
		h_password = NULL;
	}

	void createDB(const char* dir) {
		sqlite3* database;
		sqlite3_open(dir, &database);
		sqlite3_close(database);
	}
	void createTable(const char* dir) {
		sqlite3* database;
		sqlite3_open(dir, &database);

		std::string sql = "create table if not exists Users("
			"ID integer primary key autoincrement, "
			"login text not null, "
			"h_password integer);";

		char* msgError;
		int exit = sqlite3_exec(database, sql.c_str(), NULL, NULL, &msgError);
		if (exit != SQLITE_OK) {
			Error::Write("Database::Upload", Error::Type::instantiate);
			sqlite3_free(msgError);
		}
		sqlite3_close(database);
	}
	void insertRow(const char* dir, User u) {
		sqlite3* database;
		sqlite3_open(dir, &database);

		std::string sql = "insert into Users (login, h_password) values('" +
			u.getLogin() + "', " + std::to_string(u.getH_Password()) + ");";


		char* msgError;
		int exit = sqlite3_exec(database, sql.c_str(), NULL, NULL, &msgError);
		if (exit != SQLITE_OK) {
			Error::Write("Database::Register", Error::Type::database); /// change it to wherever you register
			sqlite3_free(msgError);
		}
		sqlite3_close(database);
	}

	int callback(void* data, int length, char** values, char** columns) {
		User* u = static_cast<User*>(data);
		u->setLogin(values[1]);
		// convert const char* to an integer
		std::stringstream strValue;
		strValue << values[2];
		int intValue;
		strValue >> intValue;
		/////////////////////////////////////
		u->setH_Password(intValue);
		return 0;
	}
	
	void selectRow(const char* dir, std::string login, User& u) {
		sqlite3* database;
		sqlite3_open(dir, &database);

		std::string sql = "select * from Users where login = '" + login + "';";

		sqlite3_exec(database, sql.c_str(), callback, &u, NULL);
		sqlite3_close(database);
	}

}
