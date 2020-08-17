#include <iostream>
#include "MainController.h"
#include "Math.h"
#include <ctime>
#include <string>

int main()
{
	srand(time(NULL));
	/// conclusion: we have a problem... custom INT is way too SLOOOOOOOOOOOOOOOOOOW

	//std::cout << a.divide(INT(4));
	//MainController::Run();
	// example code for RSA
	/*std::string message = "abc\nabc";
	_int64 n = 161322719, privateKey = 159827143, publicKey = 14839;
	//Math::InitRSA(n, publicKey, privateKey);
	message = Math::StringToData(message);
	std::cout << message << std::endl;
	message = Math::PerformRSA(message, publicKey, n);
	std::cout << message << std::endl;
	message = Math::PerformRSA(message, privateKey, n);
	std::cout << message << std::endl;
	message = Math::DataToString(message);
	std::cout << std::endl << message;*/
}
