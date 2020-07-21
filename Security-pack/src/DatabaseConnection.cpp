#include <iostream>
#include <sstream>
#include "sqlite3.h"
#include "Error.h"
#include "Message.h"
#include "Database.h"
#include "DatabaseConnection.h"

// temporal structure passed as an argument to callback (in User class methods set(value) are all private
	// and function callback can't be a member of a class to be transferred as an argument)
struct tempUser {
	std::string login;
	int hash;
	_int64 publicKey;
	_int64 n;
	tempUser() {
		hash = NULL;
		publicKey = NULL;
		n = NULL;
	}
};
struct tempKey {
	std::string login;
	_int64 privateKey;
	tempKey() {
		privateKey = NULL;
	}
};

// a function used in SelectRowUsers (retrieving data from the selected objects in the database)
int callbackUsers(void* data, int length, char** values, char** columns) {
	tempUser* u = static_cast<tempUser*>(data);
	u->login = values[1];
	// convert const char* to an integer
	std::stringstream strValue;
	_int64 int64Value;
	int intValue;

	strValue << values[2];
	strValue >> intValue;
	u->hash = intValue;
	std::stringstream().swap(strValue);

	strValue << values[3];
	strValue >> int64Value;
	u->publicKey = int64Value;
	std::stringstream().swap(strValue);

	strValue << values[4];
	strValue >> int64Value;
	u->n = int64Value;
	/////////////////////////////////////
	return 0;
}
// a function used in SelectRowKeys (retrieving data from the selected objects in the database)
int callbackKeys(void* data, int length, char** values, char** columns) {
	tempKey* k = static_cast<tempKey*>(data);
	k->login = values[1];
	// convert const char* to an integer
	std::stringstream strValue;
	_int64 intValue;

	strValue << values[2];
	strValue >> intValue;
	k->privateKey = intValue;
	/////////////////////////////////////
	return 0;
}
// a function used in SelectRowsMessages (retrieving data from the selected objects in the database)
int callbackMessages(void* data, int length, char** values, char** columns) {
	std::vector<Message>* m = static_cast< std::vector<Message>* >(data);
	for (int i = 0; i < length / 5; i++) {
		Message temp;
		temp.setSender(values[5 * i + 1]);
		temp.setReceiver(values[5 * i + 2]);
		temp.setTopic(values[5 * i + 3]);
		temp.setBody(values[5 * i + 4]);
		m->push_back(temp);
	}
	return 0;
}


namespace DBConnect {

	std::string DBConnect::User::getLogin() {
		return login;
	}
	int User::getH_Password() {
		return h_password;
	}
	_int64 User::getPublicKey() {
		return publicKey;
	}
	_int64 User::getN() {
		return n;
	}
	_int64 User::getPrivateKey() {
		return privateKey;
	}

	void User::setLogin(std::string _login) {
		login = _login;
	}
	void User::setH_Password(int _h_password) {
		h_password = _h_password;
	}
	void User::setPublicKey(_int64 _publicKey) {
		publicKey = _publicKey;
	}
	void User::setN(_int64 _n) {
		n = _n;
	}
	void User::setPrivateKey(_int64 _privateKey) {
		privateKey = _privateKey;
	}

	User::User(std::string _login, int _hash, _int64 _publicKey, _int64 _n, _int64 _privateKey) {
		setLogin(_login);
		setH_Password(_hash);
		setPublicKey(_publicKey);
		setN(_n);
		setPrivateKey(_privateKey);
	}
	User::User() {
		login = "";
		h_password = NULL;
		publicKey = NULL;
		n = NULL;
		privateKey = NULL;
	}
	
	void User::InsertRowUsers(const char* dirUsers) {
		sqlite3* database;
		sqlite3_open(dirUsers, &database);

		std::string sql = "insert into Users (login, h_password, publicKey, n) values('" +
			getLogin() + "', " + std::to_string(getH_Password()) + ", " + std::to_string(getPublicKey()) + ", " + std::to_string(getN()) + ");";


		char* msgError;
		int exit = sqlite3_exec(database, sql.c_str(), NULL, NULL, &msgError);
		if (exit != SQLITE_OK) {
			Error::Write("DBConnect::User::InsertRowUsers", Error::Type::database);
			sqlite3_free(msgError);
		}
		sqlite3_close(database);
	}
	void User::SelectRowUsers(const char* dirUsers, std::string _login) {
		sqlite3* database;
		sqlite3_open(dirUsers, &database);

		std::string sql = "select * from Users where login = '" + _login + "';";

		tempUser temp;
		sqlite3_exec(database, sql.c_str(), callbackUsers, &temp, NULL);

		// apply temp values to the User class
		setLogin(temp.login);
		setH_Password(temp.hash);
		setPublicKey(temp.publicKey);
		setN(temp.n);

		sqlite3_close(database);
	}

	void User::InsertRowKeys(const char* dirPrivateKeys) {
		sqlite3* database;
		sqlite3_open(dirPrivateKeys, &database);

		std::string sql = "insert into Keys (login, privateKey) values('" +
			getLogin() + "', " + std::to_string(getPrivateKey()) + ");";


		char* msgError;
		int exit = sqlite3_exec(database, sql.c_str(), NULL, NULL, &msgError);
		if (exit != SQLITE_OK) {
			Error::Write("DBConnect::User::InsertRowKeys", Error::Type::database);
			sqlite3_free(msgError);
		}
		sqlite3_close(database);
	}
	bool User::SelectRowKeys(const char* dirPrivateKeys) {
		sqlite3* database;
		sqlite3_open(dirPrivateKeys, &database);

		bool success = true;

		std::string sql = "select * from Keys where login = '" + getLogin() + "';";

		tempKey temp;
		sqlite3_exec(database, sql.c_str(), callbackKeys, &temp, NULL);

		// apply temp values to the User class
		if (getLogin() != temp.login || temp.login.size() <= 0) { // no matching account in the privateKeys.db database
			Error::Write("DBConnect::User::SelectRowKeys", Error::Type::database);
			success = false;
		}
		else {
			setPrivateKey(temp.privateKey);
		}

		sqlite3_close(database);
		return success;
	}

	void User::InsertRowMessages(const char* dirMessages, Message message) {
		sqlite3* database;
		sqlite3_open(dirMessages, &database);

		std::string sql = "insert into Messages (sender, receiver, topic, body) values('" +
			message.getSender() + "', '" + message.getReceiver() + 
			"', '" + message.getTopic() + "', '" + message.getBody() + "');";


		char* msgError;
		int exit = sqlite3_exec(database, sql.c_str(), NULL, NULL, &msgError);
		if (exit != SQLITE_OK) {
			Error::Write("DBConnect::User::InsertRowMessages", Error::Type::database);
			sqlite3_free(msgError);
		}
		sqlite3_close(database);
	}
	void User::SelectRowsMessages(const char* dirMessages) {
		sqlite3* database;
		sqlite3_open(dirMessages, &database);
		std::string sql;

		sql = "select * from Messages where receiver = '" + login + "';";
		sqlite3_exec(database, sql.c_str(), callbackMessages, &inbox, NULL);

		sqlite3_close(database);
	}

	void User::SendMessage(const char* dirMessages, Message message) {
		message.setSender(login);
		// send message to the database
		InsertRowMessages(dirMessages, message);
	}

	void createDB(const char* dir) {
		sqlite3* database;
		sqlite3_open(dir, &database);
		sqlite3_close(database);
	}
	void createTableUsers(const char* dirUsers) {
		sqlite3* database;
		sqlite3_open(dirUsers, &database);

		std::string sql = "create table if not exists Users("
			"ID integer primary key autoincrement, "
			"login text not null, "
			"h_password integer, "
			"publicKey integer, "
			"n integer);";

		char* msgError;
		int exit = sqlite3_exec(database, sql.c_str(), NULL, NULL, &msgError);
		if (exit != SQLITE_OK) {
			Error::Write("Database::Upload", Error::Type::instantiate);
			sqlite3_free(msgError);
		}
		sqlite3_close(database);
	}
	void createTableKeys(const char* dirPrivateKeys) {
		sqlite3* database;
		sqlite3_open(dirPrivateKeys, &database);

		std::string sql = "create table if not exists Keys("
			"ID integer primary key autoincrement, "
			"login text not null, "
			"privateKey integer);";

		char* msgError;
		int exit = sqlite3_exec(database, sql.c_str(), NULL, NULL, &msgError);
		if (exit != SQLITE_OK) {
			Error::Write("Database::Upload", Error::Type::instantiate);
			sqlite3_free(msgError);
		}
		sqlite3_close(database);
	}
	void createTableMessages(const char* dirMessages) {
		sqlite3* database;
		sqlite3_open(dirMessages, &database);

		std::string sql = "create table if not exists Messages("
			"ID integer primary key autoincrement, "
			"sender text not null, "
			"receiver text not null, "
			"topic text not null, "
			"body text not null);";

		char* msgError;
		int exit = sqlite3_exec(database, sql.c_str(), NULL, NULL, &msgError);
		if (exit != SQLITE_OK) {
			Error::Write("Database::Upload", Error::Type::instantiate);
			sqlite3_free(msgError);
		}
		sqlite3_close(database);
	}
}
