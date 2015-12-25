#include "Map.h"

Map::Map(sf::Vector2i thisDim) {
	dim = thisDim;
}

sf::Vector2i Map::getDim() {
	return dim;
}

std::vector<OverworldObject> Map::getOverworldObjects(View view) {
	//TODO filter
	return objList;
}

void Map::addOverworldObject(OverworldObject obj) {
	objList.push_back(obj);
}