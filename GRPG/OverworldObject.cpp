#include "OverworldObject.h"

OverworldObject::OverworldObject(sf::Vector2i thisPos) {
	pos = thisPos;
}

sf::Vector2i OverworldObject::getPos() {
	return pos;
}