#pragma once
#include <iostream>
#include <vector>

class Database {
private:
	static std::vector<std::string> logins; // logins in the database
	static std::vector<int> h_passwords; // hashed passwords in the database
public:
	static bool ExistsLogin(std::string l); // returns true if l is found in logins
	static bool ExistsPassword(int hash); // returns true if hash is found in h_passwords
	static void Upload(); // uploads all logins and h_passwords from the database (currently just creates them with predefined data)
};