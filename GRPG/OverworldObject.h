#pragma once
#include <iostream>

#include <SFML/Window.hpp>

class OverworldObject {
public:
	OverworldObject(sf::Vector2i pos);
	sf::Vector2i getPos();

private:
	sf::Vector2i pos;
	//event
	//event params
};