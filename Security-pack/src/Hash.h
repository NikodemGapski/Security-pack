#pragma once
#include <iostream>

class Hash
{
private:
	static int n; // hashing algorithm returns a value (mod n)
	static int e; // the power to which each hash iteration is raised to

public:
	static int HashPassword(std::string password); // hash a password
};

