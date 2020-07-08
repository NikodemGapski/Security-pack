#include <iostream>
#include <vector>
#include "Database.h"

std::vector<std::string> Database::logins;
std::vector<int> Database::h_passwords;

bool Database::ExistsLogin(std::string l) {
	for (int i = 0; i < logins.size(); i++) {
		if (l == logins[i]) {
			return true;
		}
	}
	return false;
}

bool Database::ExistsPassword(int hash) {
	for (int i = 0; i < h_passwords.size(); i++) {
		if (hash == h_passwords[i]) {
			return true;
		}
	}
	return false;
}

void Database::Upload() {
	logins.clear();
	h_passwords.clear();


	// here it does some stupid stuff ( Hash("this")=0 ), TODO: upload data from .sql files in the database folder
	logins.push_back("myLogin");
	h_passwords.push_back(0);
}