#pragma once
#include <SFML/Window.hpp>

class View {
public:
	View(sf::Vector2i start, sf::Vector2i dim);

	//setters
	void move(sf::Vector2i movement);

	//getters
	sf::Vector2i getStart();
	sf::Vector2i getEnd();

private:
	sf::Vector2i start;
	sf::Vector2i dim;
};