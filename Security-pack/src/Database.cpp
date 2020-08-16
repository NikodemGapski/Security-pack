#include <iostream>
#include "Error.h"
#include "Message.h"
#include "Math.h"
#include "DatabaseConnection.h"
#include "Database.h"



const char* Database::dirUsers = "./database/users.db";
const char* Database::dirPrivateKeys = "./database/privateKeys.db";
const char* Database::dirMessages = "./database/messages.db";
DBConnect::User Database::currentUser;

int Database::ExistsUser(std::string l, int hash) {
	DBConnect::User user;
	user.SelectRowUsers(dirUsers, l);


	if (user.getLogin() != l || user.getLogin().size() <= 0) {
		return -1;
	}
	if (user.getH_Password() != hash) {
		return 0;
	}

	currentUser = user;
	return 1;
}

bool Database::ExistsKey() {
	bool success = currentUser.SelectRowKeys(dirPrivateKeys);
	return success;
}

bool Database::ExistsReceiver(std::string l) {
	DBConnect::User receiver;
	receiver.SelectRowUsers(dirUsers, l);

	if (receiver.getLogin() != l || receiver.getLogin().size() <= 0) { // no matching user found
		return false;
	}
	return true;
}

void Database::AddUser(std::string l, int hash, _int64 publicKey, _int64 n, _int64 privateKey) {
	DBConnect::User user(l, hash, publicKey, n, privateKey);
	user.InsertRowUsers(dirUsers);
	user.InsertRowKeys(dirPrivateKeys);
}

void Database::SendMessage(Message message) {
	DBConnect::User receiver;
	receiver.SelectRowUsers(dirUsers, message.getReceiver());

	message.setTopic(Math::StringToData(message.getTopic()));
	message.setBody(Math::StringToData(message.getBody()));
	message.setTopic(Math::PerformRSA(message.getTopic(), receiver.getPublicKey(), receiver.getN()));
	message.setBody(Math::PerformRSA(message.getBody(), receiver.getPublicKey(), receiver.getN()));

	currentUser.SendMessage(dirMessages, message);
}

void Database::DisplayMessage(Message message) {
	Message m;
	m.setTopic(Math::PerformRSA(message.getTopic(), currentUser.getPrivateKey(), currentUser.getN()));
	m.setBody(Math::PerformRSA(message.getBody(), currentUser.getPrivateKey(), currentUser.getN()));
	m.setTopic(Math::DataToString(m.getTopic()));
	m.setBody(Math::DataToString(m.getBody()));

	m.Display();
}

std::string Database::DecryptTopic(Message message) {
	std::string t;
	t = Math::PerformRSA(message.getTopic(), currentUser.getPrivateKey(), currentUser.getN());
	t = Math::DataToString(t);
	return t;
}

void Database::UploadMessages() {
	currentUser.SelectRowsMessages(dirMessages);
}

void Database::Upload() {
	// creates databases and tables if they don't exist
	DBConnect::createDB(dirUsers);
	DBConnect::createTableUsers(dirUsers);

	DBConnect::createDB(dirPrivateKeys);
	DBConnect::createTableKeys(dirPrivateKeys);

	DBConnect::createDB(dirMessages);
	DBConnect::createTableMessages(dirMessages);
}
