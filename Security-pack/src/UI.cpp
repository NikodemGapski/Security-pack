#include <iostream>
#include <string>
#include "Error.h"
#include "Database.h"
#include "Math.h"
#include "UI.h"

std::string UI::WelcomeMenu() {
	std::string choice;
	bool isOK;
	do {
		system("cls");
		std::cout << "Security-pack by Nikodem Gapski" << std::endl;
		std::cout << "0 - log in" << std::endl;
		std::cout << "1 - don't have an account? Register" << std::endl;
		std::cout << "2 - exit" << std::endl;

		std::cin >> choice;

		isOK = true;

		if (choice != "0" && choice != "1" && choice != "2") {
			Error::Write("UI::WelcomeMenu", Error::Type::index);
			isOK = false;
		}
	} while (isOK == false);
	system("cls");

	return choice;
}

std::string UI::MainMenu() {
	std::string choice;
	bool isOK;
	do {
		system("cls");
		std::cout << "What do you want to do " << Database::currentUser.getLogin() << "?" << std::endl;
		std::cout << "0 - check inbox" << std::endl;
		std::cout << "1 - send a message" << std::endl;
		std::cout << "2 - log out" << std::endl;

		std::cin >> choice;

		isOK = true;

		if (choice != "0" && choice != "1" && choice != "2") {
			Error::Write("UI::MainMenu", Error::Type::index);
			isOK = false;
		}
	} while (isOK == false);

	return choice;
}

void UI::MessageMenu() {
	std::string choice;
	bool isOK;

	while (true) {
		do {
			system("cls");
			std::cout << "Your inbox:" << std::endl;
			for (int i = 0; i < Database::currentUser.inbox.size(); i++) {
				std::cout << i << ". " << Database::DecryptTopic(Database::currentUser.inbox[i]) << std::endl;
			}
			std::cout << std::endl;
			std::cout << "Choose which message you want to see: (to go back write no)" << std::endl;

			std::cin >> choice;
			if (choice == "no") {
				return;
			}

			isOK = true;

			if (Math::IsNumber(choice) == false) {
				Error::Write("UI::MessageMenu", Error::Type::index);
				isOK = false;
			}
			else if (std::stoi(choice) < 0 || std::stoi(choice) >= Database::currentUser.inbox.size()) {
				Error::Write("UI::MessageMenu", Error::Type::index);
				isOK = false;
			}
		} while (isOK == false);

		system("cls");
		int c = std::stoi(choice);
		Database::DisplayMessage(Database::currentUser.inbox[c]);
		system("pause");
	}

}