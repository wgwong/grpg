#include "overmap.h"
#include "Player.h"
#include "Map.h"
#include "View.h"

int overmap() {
	//intialization
	//TODO - put all this in the title screen or something later
	sf::RenderWindow window;
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8; //smoother shapes
	int width = 800;
	int height = 600;
	window.create(sf::VideoMode(width, height), "Generic RPG v0.1a ", sf::Style::Default, settings);
	window.setVerticalSyncEnabled(true);

	//TODO finish initialization
	sf::Font gameFont;
	
	//load background for overmap
	sf::Texture bgTexture;
	if (!bgTexture.loadFromFile("img/overworld.png")) {
		//TODO - error
	}
	bgTexture.setSmooth(true);
	bgTexture.setRepeated(false);
	sf::Sprite bgSprite;
	bgSprite.setTexture(bgTexture);

	//load player sprite
	sf::Texture pTexture;
	const int charWidth = 32;
	const int charHeight = 32;
	if (!pTexture.loadFromFile("img/player_spritesheet.png", sf::IntRect(0, 0, charWidth, charHeight))) {
		//TODO - error
	}
	pTexture.setSmooth(true);
	pTexture.setRepeated(false);
	sf::Sprite pSprite;
	pSprite.setTexture(pTexture);

	//set view
	View view(sf::Vector2i(0, 0), sf::Vector2i(width, height));
	const int viewWidthPadding = 50;
	const int viewHeightPadding = 50;

	//load map data
	//TODO load from file
	Map map(sf::Vector2i(1000, 1000));
	//invariant - overworld objects must not overlap!
	map.addOverworldObject(OverworldObject(sf::Vector2i(10, 10)));
	map.addOverworldObject(OverworldObject(sf::Vector2i(500, 500)));
	map.addOverworldObject(OverworldObject(sf::Vector2i(900, 900)));
	sf::Texture oTexture;
	const int objWidth = 50;
	const int objHeight = 50;
	if (!oTexture.loadFromFile("img/house_spritesheet.png", sf::IntRect(0, 0, objWidth, objHeight))) {
		//TODO - error
	}
	sf::Sprite oSprite;
	oSprite.setTexture(oTexture);

	//load player data
	//TODO finish
	Player player;
	player.setPos(sf::Vector2i(200, 12));

	bool changed = false; //debug

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		//player movement
		const int moveSpeed = 5;
		//left
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			if (player.getPos().x - moveSpeed >= 0) {
				//TODO current collision alg is slightly inaccurate because we prevent movement if movement will put us inside object
				//but if moveSpeed > 1 and player is not touching object, we will never move to TOUCH the object. we just stop
				//fix this, keep track of largest permittible movement within collidable objects
				bool willCollide = false;
				//TODO - in relation to below's TODO, we check against ALL collidable objects instead of only those near us
				std::vector<OverworldObject> overObjects = map.getOverworldObjects(view); //TODO - use different data structure to achieve log(n) search
				sf::Vector2i dest = player.getPos();
				dest.x -= moveSpeed;
				for (auto & element : overObjects) {

					/*
					std::cout << "dest: " << dest.x << ", " << dest.y << std::endl; //debug
					std::cout << "dest end: " << dest.x + charWidth << ", " << dest.y + charHeight << std::endl; //debug
					std::cout << "element: " << element.getPos().x << ", " << element.getPos().y << std::endl; //debug
					std::cout << "element end: " << element.getPos().x + objWidth << ", " << element.getPos().y + objHeight << std::endl; //debug
					std::cout << (dest.x > element.getPos().x && dest.x < element.getPos().x + objWidth) << std::endl;
					std::cout << (dest.x + charWidth > element.getPos().x && dest.x + charWidth < element.getPos().x + objWidth) << std::endl;
					std::cout << (dest.y > element.getPos().y && dest.y < element.getPos().y + objHeight) << std::endl;
					std::cout << (dest.y + charHeight > element.getPos().y && dest.y + charHeight < element.getPos().y + objHeight) << std::endl;
					std::cout << std::endl;
					*/

					if ((dest.x > element.getPos().x && dest.x < element.getPos().x + objWidth
						|| dest.x + charWidth > element.getPos().x && dest.x + charWidth < element.getPos().x + objWidth)
						&& (dest.y > element.getPos().y && dest.y < element.getPos().y + objHeight
						|| dest.y + charHeight > element.getPos().y && dest.y + charHeight < element.getPos().y + objHeight)) {
						willCollide = true;
					}
				}
				if (!willCollide) {
					player.move(sf::Vector2i(-moveSpeed, 0));
					changed = true;
				}
			}
		}
		//right
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			if (player.getPos().x + moveSpeed <= map.getDim().x - charWidth) {
				bool willCollide = false;
				//TODO - in relation to below's TODO, we check against ALL collidable objects instead of only those near us
				std::vector<OverworldObject> overObjects = map.getOverworldObjects(view); //TODO - use different data structure to achieve log(n) search
				sf::Vector2i dest = player.getPos();
				dest.x += moveSpeed;
				for (auto & element : overObjects) {
					if ((dest.x > element.getPos().x && dest.x < element.getPos().x + objWidth
						|| dest.x + charWidth > element.getPos().x && dest.x + charWidth < element.getPos().x + objWidth)
						&& (dest.y > element.getPos().y && dest.y < element.getPos().y + objHeight
						|| dest.y + charHeight > element.getPos().y && dest.y + charHeight < element.getPos().y + objHeight)) {
						willCollide = true;
					}
				}
				if (!willCollide) {
					player.move(sf::Vector2i(moveSpeed, 0));
					changed = true;
				}
			}
		}
		//up
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			if (player.getPos().y - moveSpeed >= 0) {
				bool willCollide = false;
				//TODO - in relation to below's TODO, we check against ALL collidable objects instead of only those near us
				std::vector<OverworldObject> overObjects = map.getOverworldObjects(view); //TODO - use different data structure to achieve log(n) search
				sf::Vector2i dest = player.getPos();
				dest.y -= moveSpeed;
				for (auto & element : overObjects) {
					if ((dest.x > element.getPos().x && dest.x < element.getPos().x + objWidth
						|| dest.x + charWidth > element.getPos().x && dest.x + charWidth < element.getPos().x + objWidth)
						&& (dest.y > element.getPos().y && dest.y < element.getPos().y + objHeight
						|| dest.y + charHeight > element.getPos().y && dest.y + charHeight < element.getPos().y + objHeight)) {
						willCollide = true;
					}
				}
				if (!willCollide) {
					player.move(sf::Vector2i(0, -moveSpeed));
					changed = true;
				}
			}
		}
		//down
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			if (player.getPos().y + moveSpeed <= map.getDim().y - charHeight) {
				bool willCollide = false;
				//TODO - in relation to below's TODO, we check against ALL collidable objects instead of only those near us
				std::vector<OverworldObject> overObjects = map.getOverworldObjects(view); //TODO - use different data structure to achieve log(n) search
				sf::Vector2i dest = player.getPos();
				dest.y += moveSpeed;
				for (auto & element : overObjects) {
					if ((dest.x > element.getPos().x && dest.x < element.getPos().x + objWidth
						|| dest.x + charWidth > element.getPos().x && dest.x + charWidth < element.getPos().x + objWidth)
						&& (dest.y > element.getPos().y && dest.y < element.getPos().y + objHeight
						|| dest.y + charHeight > element.getPos().y && dest.y + charHeight < element.getPos().y + objHeight)) {
						willCollide = true;
					}
				}
				if (!willCollide) {
					player.move(sf::Vector2i(0, moveSpeed));
					changed = true;
				}
			}
		}

		//TODO consider reputting this logic back in with keyboard movement
		//adjusts view
		//left
		if (player.getPos().x - view.getStart().x < viewWidthPadding && view.getStart().x - moveSpeed >= 0) {
			view.move(sf::Vector2i(-moveSpeed, 0));
			changed = true;
		}
		//right
		if (view.getEnd().x - (player.getPos().x + charWidth) < viewWidthPadding && view.getEnd().x + moveSpeed <= map.getDim().x) {
			view.move(sf::Vector2i(moveSpeed, 0));
			changed = true;
		}
		//up
		if (player.getPos().y - view.getStart().y < viewHeightPadding && view.getStart().y - moveSpeed >= 0) {
			view.move(sf::Vector2i(0, -moveSpeed));
			changed = true;
		}
		//down
		if (view.getEnd().y - (player.getPos().y + charHeight) < viewHeightPadding && view.getEnd().y + moveSpeed <= map.getDim().y) {
			view.move(sf::Vector2i(0, moveSpeed));
			changed = true;
		}

		//drawing stage
		window.clear(sf::Color::Black);

		window.draw(bgSprite); //background

		//overworld objects
		std::vector<OverworldObject> overObjects = map.getOverworldObjects(view); //TODO - use different data structure to achieve log(n) search
		for (auto & element : overObjects) {
			oSprite.setPosition(sf::Vector2f(element.getPos().x - view.getStart().x, element.getPos().y - view.getStart().y));
			//TODO - check that position isnt <  0,0 or > map.x, map.y
			window.draw(oSprite);
		}

		pSprite.setPosition(sf::Vector2f(player.getPos().x - view.getStart().x, player.getPos().y - view.getStart().y));
		window.draw(pSprite); //player sprite

		window.display();


		//debug
		/*
		if (changed) {
			std::cout << "-------------------------------------";
			std::cout << "\n\tview padding: " << viewWidthPadding << ", " << viewHeightPadding; //debug
			std::cout << "\n\tplayer position: " << player.getPos().x << ", " << player.getPos().y; //debug
			std::cout << "\n\tview at: " << view.getStart().x << ", " << view.getStart().y << " - " << view.getEnd().x << ", " << view.getEnd().y; //debug
			std::cout << "\nRIGHT: " << "view.getEnd().x - (player.getPos().x + charWidth) < 50"; //debug
			std::cout << "\nRIGHT: " << (view.getEnd().x) << " - " << (player.getPos().x) << " + " << charWidth << " < " << viewWidthPadding; //debug
			std::cout << "\nRIGHT: " << (view.getEnd().x) << " - " << (player.getPos().x + charWidth) << " < " << viewWidthPadding; //debug
			std::cout << "\nRIGHT: " << (view.getEnd().x - (player.getPos().x + charWidth)) << " < " << viewWidthPadding; //debug
			std::cout << "\n\ttherefore, player rendered at position: " << (player.getPos().x - view.getStart().x) << ", " << (player.getPos().y - view.getStart().y); //debug
			std::cout << "\n-------------------------------------";
			changed = false;
		}
		*/
	}

	return 0;
}