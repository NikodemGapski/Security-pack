#include <iostream>
#include "Hash.h"
#include "Math.h"
#include "Database.h"
#include "Register.h"

bool Register::Run() {
	std::string login;
	std::string password;
	std::string repeatedPassword;
	bool error;

	Input(login, password, repeatedPassword);
	if (password != repeatedPassword) {
		std::cout << "Passwords are different!" << std::endl;
		error = true;
	}
	else {
		int hash; // hashed password
		hash = Hash::HashPassword(password);

		int existsUser = Database::ExistsUser(login, hash);

		if (existsUser == 1 || existsUser == 0) { // the login is already taken
			std::cout << "The login is already taken" << std::endl;
			error = true;
		}
		else if (CheckData(login) == false) { // the login cannot be used (incorrent characters)
			std::cout << "The login cannot be empty and can only contain these characters:" << std::endl;
			std::cout << "- numbers 0 - 9" << std::endl << "- small and big latin letters a-z" << std::endl << "- @ sign" << std::endl;
			error = true;
		}
		else { // everything is OK
			// create RSA values
			_int64 publicKey, n, privateKey;
			Math::InitRSA(n, publicKey, privateKey);
			// addd the user to the database
			Database::AddUser(login, hash, publicKey, n, privateKey);
			error = false;
		}
	}
	return error;
}

void Register::Input(std::string &login, std::string &password, std::string &repeatedPassword) {
	std::cout << "login: " << std::endl;
	std::cin >> login;
	std::cout << "password: " << std::endl;
	std::cin >> password;
	std::cout << "repeat password: " << std::endl;
	std::cin >> repeatedPassword;
	std::cout << std::endl;
}

bool Register::CheckData(std::string data) {
	if (data.size() <= 0) {
		return false;
	}
	for (int i = 0; i < data.size(); i++) {
		int x = (int)data[i];
		if (x < 48 || (x > 57 && x < 64) || (x > 90 && x < 97) || x > 122) {
			return false;
		}
	}
	return true;
}