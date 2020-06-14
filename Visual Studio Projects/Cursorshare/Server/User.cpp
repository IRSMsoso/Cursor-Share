#include "User.h"



User::~User(){
	delete socket;
	for (int i = 0; i < connectedUsers.size(); i++) {
		delete connectedUsers.at(i);
	}
}

void User::receive(){
	sf::Packet packet;
	if (socket->receive(packet) == sf::Socket::Status::Done) {
		packet >> location.x >> location.y;
		timeoutClock.restart();
	}
	
}

bool User::isPairedWith(User* other){

	for (int i = 0; i < connectedUsers.size(); i++) {
		if (connectedUsers.at(i) == other) {
			return true;
		}
	}

	return false;
}

bool User::canPair(){
	if (connectedUsers.size() >= 3)
		return false;
	else
		return true;
}
