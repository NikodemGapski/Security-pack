#include <iostream>
#include "MainController.h"
#include "Math.h"
#include <ctime>
#include <string>

int main()
{
	srand(time(NULL));
	//MainController::Run();
	
	// example code for RSA
	std::string message = "HI! My name is Nikodem.";
	_int64 n, phi, privateKey, publicKey;
	Math::InitRSA(n, phi, publicKey, privateKey);
	message = Math::StringToData(message);
	std::cout << message << std::endl;
	message = Math::PerformRSA(message, publicKey, n);
	std::cout << message << std::endl;
	message = Math::PerformRSA(message, privateKey, n);
	std::cout << message << std::endl;
	message = Math::DataToString(message);
	std::cout << std::endl << message;
}
