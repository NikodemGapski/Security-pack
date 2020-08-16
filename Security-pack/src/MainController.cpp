#include <iostream>
#include "MainController.h"
#include "Login.h"
#include "Register.h"
#include "Database.h"
#include "Error.h"
#include "UI.h"
#include "Message.h"


bool MainController::isLoggedIn;

void MainController::Run() {
	bool error;
	bool loggedIn;
	std::string choice;

	while(true) {
		// welcome screen
		do {
			error = false;
			loggedIn = false;
			Database::Upload();
			choice = UI::WelcomeMenu();

			if (choice == "0") {
				// log in
				loggedIn = Login::Run();
			}
			else if (choice == "1") {
				// register
				error = Register::Run();
			}
			else if (choice == "2") {
				// exit
				return;
			}
			system("pause");

		} while (error == true || loggedIn == false);

		if (loggedIn == true) {
			// no error, logged in
			setLoggedIn(true);
		}

		// logged in screen
		while (getLoggedIn() == true) {
			system("cls");
			choice = UI::MainMenu();

			if (choice == "0") {
				// check inbox
				Database::UploadMessages();
				UI::MessageMenu();
			}
			else if (choice == "1") {
				// send a message
				Message message;
				bool sending = message.Create();
				if (sending == true) {
					Database::SendMessage(message);
				}
			}
			else if (choice == "2") {
				// log out
				Login::LogOut();
				setLoggedIn(false);
			}
			system("pause");
		}
	}
}

bool MainController::getLoggedIn() {
	return isLoggedIn;
}

void MainController::setLoggedIn(bool isLogged) {
	isLoggedIn = isLogged;
}