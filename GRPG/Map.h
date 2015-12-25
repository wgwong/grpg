#pragma once
#include <vector>

#include <SFML/Window.hpp>

#include "View.h"
#include "OverworldObject.h"


class Map {
public:
	Map(sf::Vector2i dim);

	//getters
	sf::Vector2i getDim();
	std::vector<OverworldObject> getOverworldObjects(View view);

	//setters
	void addOverworldObject(OverworldObject obj);
		
private:
	sf::Vector2i dim;
	std::vector<OverworldObject> objList;
};