#include <iostream>
#include "Database.h"
#include "Error.h"
#include "DatabaseConnection.h"



const char* Database::dir = "./database/users.db";
DBConnect::User Database::currentUser;

int Database::ExistsUser(std::string l, int hash) {
	DBConnect::User user;
	DBConnect::selectRow(dir, l, user);


	if (user.getLogin() != l && user.getLogin().size() <= 0) {
		return -1;
	}
	if (user.getH_Password() != hash) {
		return 0;
	}

	currentUser = user;
	return 1;
}

void Database::AddUser(std::string l, int hash) {
	DBConnect::User user(l, hash);
	DBConnect::insertRow(dir, user);
}


void Database::Upload() {
	// creates a database and a table if they don't exist
	DBConnect::createDB(dir);
	DBConnect::createTable(dir);

	// some stupid stuff (debugging)
	//DBConnect::User user1("marc", 0);
	//DBConnect::insertRow(dir, user1);

}
