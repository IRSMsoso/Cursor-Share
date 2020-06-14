// Client.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "DesktopCursor.h"


void initializeCursor(DesktopCursor&, MARGINS&);


int main()
{
	sf::Texture cursorTexture;
	cursorTexture.loadFromFile("Cursor.png");

	std::vector<DesktopCursor> cursors;


	MARGINS margins;



	int currentPos = 0;
	while (true) {
		sf::sleep(sf::milliseconds(10));
		dude.setPosition(sf::Vector2i(currentPos + 1, 0));
		currentPos += 1;
	}

	std::system("pause");
	return 0;

}

void initializeCursor(DesktopCursor& cursor, MARGINS& margins) {
	SetWindowLong(cursor.getWindow()->getSystemHandle(), GWL_STYLE, WS_POPUP | WS_VISIBLE);
	DwmExtendFrameIntoClientArea(cursor.getWindow()->getSystemHandle(), &margins);
}