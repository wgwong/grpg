#include "Player.h"

Player::Player() {

}

sf::Vector2i Player::getPos() {
	return pos;
}

void Player::setPos(sf::Vector2i newPos) {
	pos = newPos;
}

void Player::move(sf::Vector2i vector) {
	pos.x += vector.x;
	pos.y += vector.y;
}