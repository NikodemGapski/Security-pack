#include <iostream>
#include "MainController.h"
#include "Login.h"
#include "Register.h"
#include "Database.h"
#include "Error.h"

void MainController::Run() {
	bool error = false;
	std::string choice;

	do {
		Database::Upload();
		choice = ViewWelcomeMenu();
		if (choice == "0") {
			error = Login::Run();
		}
		else if (choice == "1") {
			error = Register::Run();
		}
	} while (error == true);

}

std::string MainController::ViewWelcomeMenu() {
	std::string choice;
	bool isOK;
	do {
		system("cls");
		std::cout << "Security-pack by Nikodem Gapski" << std::endl;
		std::cout << "0 - log in" << std::endl;
		std::cout << "1 - don't have an account? Register" << std::endl;

		std::cin >> choice;

		isOK = true;

		if (choice != "0" && choice != "1") {
			Error::Write("MainController::ViewWelcomeMenu", Error::Type::index);
			isOK = false;
		}
	} while (isOK == false);
	system("cls");

	return choice;
}
