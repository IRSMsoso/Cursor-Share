#pragma once
#include <SFML/Network.hpp>
#include <iostream>


class User{
public:
	~User();

	sf::TcpSocket* getSocket() { return socket; }
	void setSocket(sf::TcpSocket* newSocket) { socket = newSocket; }

	void receive();

	int getID() { return id; }
	void setID(int newID) { id = newID; }

	std::vector<User*>* getPairedList() { return &connectedUsers; }

	sf::Vector2i getLocation() { return location; }

	sf::Time getTimeoutTime() { return timeoutClock.getElapsedTime(); }

	bool isPairedWith(User*);

	bool canPair();

	void pair(User* newUser) { connectedUsers.push_back(newUser); }
	void unpair(User* oldUser);

private:
	sf::TcpSocket* socket;
	sf::Vector2i location;
	std::vector<User*> connectedUsers;
	sf::Int32 id;
	sf::Clock timeoutClock;
};

