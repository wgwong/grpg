#include "util.h"

//TODO current collision alg is slightly inaccurate because we prevent movement if movement will put us inside object
//but if moveSpeed > 1 and player is not touching object, we will never move to TOUCH the object. we just stop
//fix this, keep track of largest permittible movement within collidable objects
bool checkCollision(std::vector<OverworldObject> overObjects, sf::Vector2i dest, sf::Vector2i charDim, sf::Vector2i objDim) {
	bool willCollide = false;

	for (auto & element : overObjects) {
		if ((dest.x > element.getPos().x && dest.x < element.getPos().x + objDim.x
			|| dest.x + charDim.x > element.getPos().x && dest.x + charDim.x < element.getPos().x + objDim.x)
			&& (dest.y > element.getPos().y && dest.y < element.getPos().y + objDim.y
				|| dest.y + charDim.y > element.getPos().y && dest.y + charDim.y < element.getPos().y + objDim.y)) {
			willCollide = true;
		}
	}

	return willCollide;
}