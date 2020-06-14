#pragma once
#include "DesktopCursor.h"
#include <SFML/Network.hpp>

class ClientManager{
public:
	ClientManager();

	void send();
	void listen();

	bool connect(sf::IpAddress);

private:
	std::vector<DesktopCursor*> cursors;
	sf::Texture cursorTexture;

	sf::TcpSocket socket;

	bool running;
};

