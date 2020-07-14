#pragma once
#include <iostream>
#include "DatabaseConnection.h"

class Database {
private:
	static const char* dir; // users database directory
public:
	static DBConnect::User currentUser; // current user's data
	static int ExistsUser(std::string l, int hash); // returns 1 if a user is found in the database,
													//0 if the password is wrong and -1 if the login is wrong
	static void Upload(); // uploads all logins and h_passwords from the database (currently just creates them with predefined data)
};