#include "enter_shop.h"

int enter_shop(sf::RenderWindow * w, Player * p) {
	int width = (*w).getSize().x;
	int height = (*w).getSize().y;

	//TODO finish font initialization
	sf::Font gameFont;

	//load background for shop
	sf::Texture bgTexture;
	if (!bgTexture.loadFromFile("img/shop.png")) {
		//TODO - error
	}
	bgTexture.setSmooth(true);
	bgTexture.setRepeated(false);
	sf::Sprite bgSprite;
	bgSprite.setTexture(bgTexture);

	//set view
	View view(sf::Vector2i(0, 0), sf::Vector2i(width, height));

	//load music
	sf::Music music;
	if (!music.openFromFile("music/shop.ogg")) {
		return -1; // error
	}
	music.setLoop(true);
	music.play();

	while ((*w).isOpen()) {
		sf::Event event;

		while ((*w).pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				(*w).close();
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			std::cout << "pass";
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			return 0;
		}

		//drawing stage
		(*w).clear(sf::Color::Black);

		(*w).draw(bgSprite); //background

		(*w).display();
	}

	return 0;
}