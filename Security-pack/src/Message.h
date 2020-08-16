#pragma once
#include <iostream>


class Message {
private:
	std::string topic; // topic of the message
	std::string body; // body of the message
	std::string sender; // sender's login
	std::string receiver; // receiver's login
public:
	std::string getTopic();
	std::string getBody();
	std::string getSender();
	std::string getReceiver();
	bool Create();
	void Display();
	bool AssignReceiver();
	void setTopic(std::string data);
	void setBody(std::string data);
	void setSender(std::string login);
	void setReceiver(std::string login);
};