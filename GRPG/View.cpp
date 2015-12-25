#include "View.h"

View::View(sf::Vector2i thisStart, sf::Vector2i thisDim) {
	start = thisStart;
	dim = thisDim;
}

void View::move(sf::Vector2i vector) {
	start.x += vector.x;
	start.y += vector.y;
}

sf::Vector2i View::getStart() {
	return start;
}
sf::Vector2i View::getEnd() {
	return sf::Vector2i(start.x + dim.x, start.y + dim.y);
}