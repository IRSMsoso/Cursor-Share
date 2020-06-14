#include "DesktopCursor.h"

DesktopCursor::DesktopCursor(sf::Color color, sf::Texture& texture): window(sf::VideoMode(12, 19), "", sf::Style::None){
	cursorSprite.setTexture(texture);
	cursorSprite.setColor(color);

	window.clear(sf::Color::Transparent);
	window.draw(cursorSprite);
	window.display();
	
	SetWindowLong(window.getSystemHandle(), GWL_STYLE, WS_POPUP | WS_VISIBLE);
	DwmExtendFrameIntoClientArea(window.getSystemHandle(), &margins);
}

void DesktopCursor::setPosition(sf::Vector2i newPos){

	window.setPosition(newPos);
}
