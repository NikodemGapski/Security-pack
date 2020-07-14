#pragma once
#include <iostream>

namespace DBConnect {
	// User class containing a login and a hashed password (used as an object for communicating with the database)
	class User {
	private:
		std::string login;
		int h_password;
	public:
		std::string getLogin();
		int getH_Password();

		void setLogin(std::string _login);
		void setH_Password(int _h_password);

		User(std::string _login, int _hash);
		User();
	};
	// create a database if it doesn't exist
	void createDB(const char* dir);
	// create a table Users in the database if one doesn't exist
	void createTable(const char* dir);
	// create another user in Users table
	void insertRow(const char* dir, User u);
	// a function used in selectRow (retrieving data from the selected objects in the database)
	int callback(void* data, int length, char** values, char** columns);
	// select a row in the database where the given login is found
	void selectRow(const char* dir, std::string login, User& u);
}