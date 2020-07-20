#include <iostream>
#include "Login.h"
#include "Hash.h"
#include "Database.h"


bool Login::Run() {
	std::string login;
	std::string password;
	bool loggedIn;

	Input(login, password);

	int hash; // hashed password
	hash = Hash::HashPassword(password);

	int existsUser = Database::ExistsUser(login, hash);

	if (existsUser == 1) { // the user exists
		std::cout << "Logged in!" << std::endl;
		std::cout << "Hi " << Database::currentUser.getLogin() << "!" << std::endl;
		loggedIn = true;
	}
	else if(existsUser == 0) { // the password is wrong but the login exists
		std::cout << "There is no matching password in the database" << std::endl;
		loggedIn = false;
	}
	else { // there is no such login
		std::cout << "There is no user with login " << login << std::endl;
		loggedIn = false;
	}
	return loggedIn;
}

void Login::LogOut() {
	Database::currentUser = DBConnect::User(); // remove the data stored in Database class about the current user

	std::cout << std::endl << "Logged out!" << std::endl;
}


void Login::Input(std::string &login, std::string &password) {
	std::cout << "login: " << std::endl;
	std::cin >> login;
	std::cout << "password: " << std::endl;
	std::cin >> password;
	std::cout << std::endl;
}
