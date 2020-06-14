// Server.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Manager.h"



int main()
{
    
	Manager manager;

	sf::Thread listenThread(&Manager::listen, &manager);
	sf::Thread sendThread(&Manager::send, &manager);
	sf::Thread cleanUpThread(&Manager::cleanUp, &manager);

	listenThread.launch();
	sendThread.launch();
	cleanUpThread.launch();

	listenThread.wait();
	sendThread.wait();
	cleanUpThread.wait();


	return 0;
}
