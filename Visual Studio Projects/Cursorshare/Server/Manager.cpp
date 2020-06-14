#include "Manager.h"

Manager::Manager(){
	if (listener.listen(25406) != sf::Socket::Done) {
		std::cout << "Could not bind port\n";
	}

	running = true;
}

void Manager::listen(){

	srand(time(NULL));

	sf::SocketSelector selector;
	
	while (running) {

		selector.add(listener);

		userListMutex.lock();
		for (int i = 0; i < userList.size(); i++) {
			selector.add(*userList.at(i)->getSocket());
		}
		userListMutex.unlock();

		if (selector.wait(sf::seconds(60))) {
			if (selector.isReady(listener)) {
				std::cout << "New Connection\n";
				User* newUser = new User;
				sf::TcpSocket* newSocket = new sf::TcpSocket;
				listener.accept(*newSocket);
				newUser->setSocket(newSocket);
				std::cout << "IP Address: " << newSocket->getRemoteAddress() << std::endl;

				bool newIDUnique = false;
				int newID;
				while (!newIDUnique) {
					newID = (rand() % 99999) + 1;
					std::cout << "NEW ID: " << newID << std::endl;
					newIDUnique = true;
					for (int i = 0; i < userList.size(); i++) {
						if (userList.at(i)->getID() == newID)
							newIDUnique = false;
					}
				}
				newUser->setID(newID);
				std::cout << "ID: " << newIDUnique << std::endl;

				userListMutex.lock();
				userList.push_back(newUser);
				userListMutex.unlock();
			}

			userListMutex.lock();
			for (int i = 0; i < userList.size(); i++) {
				if (selector.isReady(*userList.at(i)->getSocket())) {
					userList.at(i)->receive();
				}
			}
			userListMutex.unlock();

		}
		selector.clear();
	}
}

void Manager::send(){
	while (running) {
		userListMutex.lock();
		for (int i = 0; i < userList.size(); i++) {
			sf::Packet packet;
			packet << (sf::Int32)userList.at(i)->getPairedList()->size();
			for (int w = 0; w < userList.at(i)->getPairedList()->size(); w++) {
				User* associatedUser = userList.at(i)->getPairedList()->at(w);
				packet << (sf::Int32)associatedUser->getID() << (sf::Int32)associatedUser->getLocation().x << (sf::Int32)associatedUser->getLocation().y;
			}
			userList.at(i)->getSocket()->send(packet);
			packet.clear();
		}
		userListMutex.unlock();

		sf::sleep(sf::milliseconds(10));
	}
}

void Manager::cleanUp(){
	while (running) {
		userListMutex.lock();
		for (int i = 0; i < userList.size(); i++) {
			if (userList.at(i)->getTimeoutTime() > sf::seconds(10)) {
				std::cout << "Deleted user with ID: " << userList.at(i)->getID() << " due to timeout\n";

				for (int w = 0; w < userList.size(); w++) {
					userList.at(w)->unpair(userList.at(i));
				}

				delete userList.at(i);
				userList.erase(userList.begin() + i);
			}
		}
		userListMutex.unlock();

		userListMutex.lock();
		if (userList.size() > 1) {
			int first = rand() % userList.size();
			int second = rand() % userList.size();
			while (second == first) {
				second = rand() % userList.size();
			}
			User* firstUser = userList.at(first);
			User* secondUser = userList.at(second);
			if (!firstUser->isPairedWith(secondUser) && firstUser->canPair() && secondUser->canPair()) {
				firstUser->pair(secondUser);
				secondUser->pair(firstUser);
				std::cout << "Paired User: " << firstUser->getID() << " with User: " << secondUser->getID() << std::endl;
			}
		}
		userListMutex.unlock();

		sf::sleep(sf::seconds(2));
	}
}
