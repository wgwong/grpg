#pragma once
#include <vector>

#include <SFML/Window.hpp>

#include "OverworldObject.h"

bool checkCollision(std::vector<OverworldObject> overObjects, sf::Vector2i dest, sf::Vector2i charDim, sf::Vector2i objDim);