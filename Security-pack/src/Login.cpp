#include <iostream>
#include "Login.h"
#include "Math.h"
#include "Database.h"

int Login::n;
int Login::e;

Login::Login() {
	n = 1000000000;
	e = 13;
}

bool Login::Run() {
	std::string login;
	std::string password;
	bool error;

	Input(login, password);

	int hash; // hashed password
	hash = Hash(password);
	std::cout << "(debugging tool) hash = " << hash << std::endl;

	if (Database::ExistsLogin(login)) {
		if (Database::ExistsPassword(hash)) {
			std::cout << "Logged in!" << std::endl;
			error = false;
		}
		else {
			std::cout << "There is no matching password in the database" << std::endl;
			error = true;
		}
	}
	else {
		std::cout << "There is no user with login " << login << std::endl;
		error = true;
	}
	system("pause");
	return error;
}

void Login::Input(std::string &login, std::string &password) {
	std::cout << "login: " << std::endl;
	std::cin >> login;
	std::cout << "password: " << std::endl;
	std::cin >> password;
	std::cout << std::endl;
}

int Login::Hash(std::string password) {
	int hash = 0;
	for (int i = 0; i < password.size(); i++) {
		hash += password[i]; // add the next character ASCII value to the hash
		hash = Math::Power(hash, e, n); // raise 'hash' to the power 'e' modulo 'n'
	}
	return hash;
}