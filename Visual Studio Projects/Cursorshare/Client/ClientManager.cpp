#include "ClientManager.h"

ClientManager::ClientManager(){
	cursorTexture.loadFromFile("Cursor.png");

	running = true;
}

void ClientManager::send(){
	sf::Packet packet;
	while (running) {
		packet << sf::Mouse::getPosition().x << sf::Mouse::getPosition().y;
		socket.send(packet);
		packet.clear();
		sf::sleep(sf::milliseconds(10));
	}
}

void ClientManager::listen(){
	sf::Packet packet;
	while (running) {
		if (socket.receive(packet) == sf::Socket::Status::Done) {

			sf::Int32 numCursors;
			packet >> numCursors;

			std::vector<sf::Int32> ids;
			std::vector<sf::Int32> xs;
			std::vector<sf::Int32> ys;

			for (int i = 0; i < numCursors; i++) {
				sf::Int32 id;
				sf::Int32 x;
				sf::Int32 y;
				packet >> id >> x >> y;

				ids.push_back(id);
				xs.push_back(x);
				ys.push_back(y);
			}

			for (int i = 0; i < cursors.size(); i++) {
				bool shouldDelete = true;
				for (int w = 0; w < ids.size(); w++) {
					if (cursors.at(i)->getID() == (int)ids.at(w)) {
						shouldDelete = false;
					}
				}
				if (shouldDelete) {
					delete cursors.at(i);
					cursors.erase(cursors.begin() + i);
					i--;
				}
			}

			for (int i = 0; i < ids.size(); i++) {
				bool newCursor = true;
				for (int w = 0; w < cursors.size(); w++) {
					if (cursors.at(w)->getID() == ids.at(i)) {
						newCursor = false;
						cursors.at(w)->setPosition(sf::Vector2i(xs.at(i), ys.at(i)));
					}
				}
				if (newCursor) {
					DesktopCursor* newCursor = new DesktopCursor(sf::Color(rand() % 255, rand() % 255, rand() % 255, 255), cursorTexture);
					newCursor->setID(ids.at(i));
					newCursor->setPosition(sf::Vector2i(xs.at(i), ys.at(i)));
					cursors.push_back(newCursor);

				}
			}


		}
		packet.clear();
	}
}

bool ClientManager::connect(sf::IpAddress address){
	if (socket.connect(address, 25406, sf::seconds(5)) == sf::Socket::Status::Done) {
		return true;
	}
	else {
		return false;
	}
}
