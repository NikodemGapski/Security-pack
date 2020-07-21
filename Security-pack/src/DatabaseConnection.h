#pragma once
#include <iostream>
#include <vector>
#include "Message.h"

namespace DBConnect {
	// User class containing login, hashed password and RSA values (used as an object for communicating with the database)
	class User {
	private:
		std::string login;
		int h_password;
		_int64 publicKey;
		_int64 n;
		_int64 privateKey;

		void setLogin(std::string _login);
		void setH_Password(int _h_password);
		void setPublicKey(_int64 _publicKey);
		void setN(_int64 _n);
		void setPrivateKey(_int64 _privateKey);
		// create another message in Messages table (only in messages.db!)
		void InsertRowMessages(const char* dirMessages, Message message);
	public:
		std::vector<Message> inbox;
		std::vector<Message> outbox;

		std::string getLogin();
		int getH_Password();
		_int64 getPublicKey();
		_int64 getN();
		_int64 getPrivateKey();
		// create another user in Users table (only in users.db!)
		void InsertRowUsers(const char* dirUsers);
		// select a row in the database where the given login is found (only in users.db!)
		void SelectRowUsers(const char* dirUsers, std::string _login);
		// create another user in Keys table (only in privateKeys.db!)
		void InsertRowKeys(const char* dirPrivateKeys);
		// select a row in the database where the login of this class is found (only in privateKeys.db!)
		bool SelectRowKeys(const char* dirPrivateKeys);

		// select rows in the database where the login of this class is found (isInbox == true -> as a receiver, false -> as a sender)
		//(only in messages.db!)
		void SelectRowsMessages(const char* dirMessages);

		void SendMessage(const char* dirMessages, Message message);
		User(std::string _login, int _hash, _int64 _publicKey, _int64 n, _int64 privateKey);
		User();
	};
	// create a database if it doesn't exist
	void createDB(const char* dir);
	// create a table Users in the database if one doesn't exist (only in users.db!)
	void createTableUsers(const char* dirUsers);
	// create a table Keys in the database if one doesn't exist (only in privateKeys.db!)
	void createTableKeys(const char* dirPrivateKeys);
	// create a table Keys in the database if one doesn't exist (only in messages.db!)
	void createTableMessages(const char* dirMessages);
}