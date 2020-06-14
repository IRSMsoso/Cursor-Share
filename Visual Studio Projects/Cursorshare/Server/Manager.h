#pragma once
#include "User.h"
#include <iostream>


class Manager{
public:
	Manager();

	void listen();
	void send();
	void cleanUp();


private:
	bool running;


	std::vector<User*> userList;
	sf::TcpListener listener;

	sf::Mutex userListMutex;
};

