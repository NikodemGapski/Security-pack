#include <iostream>
#include <string>
#include "Database.h"
#include "Message.h"

bool Message::Create() {
	if (AssignReceiver() == false) {
		std::cout << "There is no such user in the database." << std::endl;
		system("pause");
		return false;
	}

	std::cout << "Topic:" << std::endl;
	std::getline(std::cin, topic);
	std::cout << std::endl << "Body:" << std::endl;
	std::string input;
	do {
		std::getline(std::cin, input);
		if (input != "<END>") {
			body += "\n" + input;
		}
	} while (input != "<END>");

	std::cout << std::endl;
	std::cout << "That's what the message will look like for the receiver:" << std::endl;
	Display();
	while (true) {
		std::cout << "Are you sure you want to send this message to " << receiver << "? (yes/no)" << std::endl;
		std::cin >> input;
		if (input == "yes") {
			std::cout << "Message sent!" << std::endl;
			system("pause");
			return true;
		}
		if (input == "no") {
			std::cout << "Message deleted!" << std::endl;
			system("pause");
			return false;
		}
		std::cout << "	Incorrect input. Write yes if you want to send the message and no if you don't." << std::endl;
	}
}

bool Message::AssignReceiver() {
	std::cout << "Receiver: ";
	std::string input;
	std::cin.ignore();
	std::getline(std::cin, input);

	if (Database::ExistsReceiver(input) == true) {
		receiver = input;
		return true;
	}
	return false;
}

void Message::Display() {
	std::cout << "From: ";
	if (sender == "") {
		std::cout << Database::currentUser.getLogin();
	}
	std::cout << sender << std::endl;

	std::cout << "Topic:" << std::endl;
	std::cout << topic << std::endl << std::endl;
	std::cout << "Body: ";
	std::cout << body << std::endl << std::endl;
}

void Message::setTopic(std::string data) {
	topic = data;
}
void Message::setBody(std::string data) {
	body = data;
}
void Message::setSender(std::string login) {
	sender = login;
}
void Message::setReceiver(std::string login) {
	receiver = login;
}

std::string Message::getTopic() {
	return topic;
}
std::string Message::getBody() {
	return body;
}
std::string Message::getSender() {
	return sender;
}
std::string Message::getReceiver() {
	return receiver;
}