#pragma once
#include <iostream>

class Login
{
private:
	
	static int n; // hashing algorithm returns a value (mod n)
	static int e; // the power to which each hash iteration is raised to

	static void Input(std::string &login, std::string &password); // input login and password
	static int Hash(std::string password); // hash a password
public:
	static bool Run(); // run the process of logging in (returns true when an error occurs)
	Login();
};

