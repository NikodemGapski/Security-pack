#pragma once
#include <iostream>

namespace Math {
	int Power(int base, int power);
	int Power(int base, int power, int modulo);
	_int64 Power(_int64 base, _int64 power, _int64 modulo);
	_int64 InverseModulo(int a, _int64 modulo);

	bool IsPrime(_int64 p);
	_int64 FindBigPrime(_int64 modulo);
	int GCD(_int64 a, _int64 b);
	int FindCoprime(_int64 a, int min, int modulo);
	void InitRSA(_int64 &n, _int64 &phi, _int64 &publicKey, _int64 &privateKey, _int64 modulo = 100000, int min = 5000);
	std::string StringToData(std::string text); // input: readable text;
												 // output: each 2 characters of a string represent a number
												 // data divided into 5-character chunks separated by '-'
	std::string DataToString(std::string data); // input: all above; output: readable text
	std::string PerformRSA(std::string message, _int64 key, _int64 modulo); // input and output must be in convention (numbers separated by '-')

}
