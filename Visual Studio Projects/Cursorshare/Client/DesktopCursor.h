#pragma once
#include "SFML/Graphics.hpp"
#include <Windows.h>
#include <dwmapi.h>

#pragma comment (lib, "Dwmapi.lib")

class DesktopCursor{
public:
	
	DesktopCursor(sf::Color, sf::Texture&);

	void setPosition(sf::Vector2i);

	sf::RenderWindow* getWindow() { return &window; }


private:
	sf::RenderWindow window;
	sf::Sprite cursorSprite;

	MARGINS margins;
};
