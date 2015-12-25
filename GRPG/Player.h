#pragma once
#include <SFML/Window.hpp>


class Player {
public:
	Player();

	//getters
	sf::Vector2i getPos();

	//setters
	void setPos(sf::Vector2i pos); //used to placing the player exactly on the specified coordinate
	void move(sf::Vector2i movement); //used to move the player in the direction of the specified vector

private:
	sf::Vector2i pos; //game position on the overworld
};