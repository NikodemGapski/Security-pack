#pragma once
#include <iostream>
#include "Message.h"
#include "DatabaseConnection.h"

class Database {
private:
	static const char* dirUsers; // users database directory
	static const char* dirPrivateKeys; // private keys directory
	static const char* dirMessages; // messages directory
public:
	static DBConnect::User currentUser; // current user's data
	static int ExistsUser(std::string l, int hash); // returns 1 if a user is found in the database,
													//0 if the password is wrong and -1 if the login is wrong
	static bool ExistsKey(); // returns true if a private key of the current user exists and false if not
	static bool ExistsReceiver(std::string l); // returns true if a user with given login exists in users.db
	static void AddUser(std::string l, int hash, _int64 publicKey, _int64 n, _int64 privateKey); // adds the given user to the database
	static void SendMessage(Message message);
	static void DisplayMessage(Message message);
	static std::string DecryptTopic(Message message);
	static void UploadMessages();
	static void Upload(); // uploads all logins and h_passwords from the database (currently just creates them with predefined data)
};