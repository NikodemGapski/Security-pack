#pragma once
#include <iostream>

class Register
{
private:
	static void Input(std::string &login, std::string &password, std::string &repeatedPassword); // input login and password
	static bool CheckData(std::string data);
public:
	static bool Run(); // run the process of registering (returns true when an error occurs)
};