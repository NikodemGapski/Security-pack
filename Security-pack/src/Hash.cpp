#include <iostream>
#include "Math.h"
#include "Hash.h"

int Hash::n = 1000000000;
int Hash::e = 13;


int Hash::HashPassword(std::string password) {
	int hash = 0;
	for (int i = 0; i < password.size(); i++) {
		hash += password[i]; // add the next character ASCII value to the hash
		hash = Math::Power(hash, e, n); // raise 'hash' to the power 'e' modulo 'n'
	}
	return hash;
}