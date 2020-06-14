#include "User.h"



User::~User(){
	socket->disconnect();
	delete socket;
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

void User::unpair(User * oldUser){
	for (int i = 0; i < connectedUsers.size(); i++) {
		if (connectedUsers.at(i) == oldUser) {
			connectedUsers.erase(connectedUsers.begin() + i);
			std::cout << "Erased Paired User\n";
		}
	}
}
