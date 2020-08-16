#pragma once
#include <iostream>

class Login
{
private:
	static void Input(std::string &login, std::string &password); // input login and password

public:
	static bool Run(); // run the process of logging in (returns true when an error occurs)
	static void LogOut(); // run the process of logging out
};