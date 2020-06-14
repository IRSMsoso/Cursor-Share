// Client.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "ClientManager.h"


void initializeCursor(DesktopCursor&, MARGINS&);


int main()
{
	MARGINS margins;

	ClientManager manager;

	std::cout << "Please enter the IP Address of a server to connect to.\n";

	bool done = false;

	while (!done) {
		std::string intAddress;
		std::cin >> intAddress;

		sf::IpAddress address(intAddress);

		done = manager.connect(address);
	}

	std::cout << "Connected!\n";


	

	std::system("pause");
	return 0;

}

void initializeCursor(DesktopCursor& cursor, MARGINS& margins) {
	SetWindowLong(cursor.getWindow()->getSystemHandle(), GWL_STYLE, WS_POPUP | WS_VISIBLE);
	DwmExtendFrameIntoClientArea(cursor.getWindow()->getSystemHandle(), &margins);
}