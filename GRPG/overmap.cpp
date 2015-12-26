#include "overmap.h"
#include "util.h"
#include "Player.h"
#include "Map.h"
#include "View.h"

int overmap(sf::RenderWindow * w) {
	int width = (*w).getSize().x;
	int height = (*w).getSize().y;

	//TODO finish font initialization
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
	const int viewWidthPadding = 100;
	const int viewHeightPadding = 100;

	//load map data
	//TODO load from file
	std::ifstream mapFile;
	mapFile.open("maps/basic.dat");
	int mapWidth = 0;
	int mapHeight = 0;
	//TODO, handle whitespaces, change file format
	if (mapFile.is_open()) {
		std::string objects = "";

		std::string line;
		std::deque<std::string> lines;
		while (std::getline(mapFile, line)) {
			if (line == "[end size]") {
				std::string widthLine = lines.at(1);
				int splitIndex = widthLine.find(":");
				mapWidth = stoi(widthLine.substr(splitIndex+1, widthLine.length()));

				std::string heightLine = lines.at(2);
				splitIndex = heightLine.find(":");
				mapHeight = stoi(heightLine.substr(splitIndex+1, heightLine.length()));
				lines.clear();
			}
			else if (line == "[end objects]") {
				lines.pop_front(); //pop '[objects]'
				for (int i = 0; i < lines.size(); i++) {
					
				}
			}
			else {
				lines.push_back(line);
			}
		}
	}

	Map map(sf::Vector2i(mapWidth, mapHeight));
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

	//load music
	sf::Music music;
	if (!music.openFromFile("music/overworld.ogg")) {
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

		//player movement
		const int moveSpeed = 5;
		//left
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			if (player.getPos().x - moveSpeed >= 0) {
				//TODO - in relation to below's TODO, we check against ALL collidable objects instead of only those near us
				//TODO - use different data structure to achieve log(n) search
				sf::Vector2i dest = player.getPos();
				dest.x -= moveSpeed;

				if (!checkCollision(map.getOverworldObjects(view), dest, sf::Vector2i(charWidth, charHeight), sf::Vector2i(objWidth, objHeight))) {
					player.move(sf::Vector2i(-moveSpeed, 0));
				}
			}
		}
		//right
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			if (player.getPos().x + moveSpeed <= map.getDim().x - charWidth) {
				//TODO - in relation to below's TODO, we check against ALL collidable objects instead of only those near us
				//TODO - use different data structure to achieve log(n) search
				sf::Vector2i dest = player.getPos();
				dest.x += moveSpeed;
				
				if (!checkCollision(map.getOverworldObjects(view),dest,sf::Vector2i(charWidth, charHeight),sf::Vector2i(objWidth, objHeight))) {
					player.move(sf::Vector2i(moveSpeed, 0));
				}
			}
		}
		//up
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			if (player.getPos().y - moveSpeed >= 0) {
				//TODO - in relation to below's TODO, we check against ALL collidable objects instead of only those near us
				//TODO - use different data structure to achieve log(n) search
				sf::Vector2i dest = player.getPos();
				dest.y -= moveSpeed;

				if (!checkCollision(map.getOverworldObjects(view), dest, sf::Vector2i(charWidth, charHeight), sf::Vector2i(objWidth, objHeight))) {
					player.move(sf::Vector2i(0, -moveSpeed));
				}
				else { //enter shop
					//TODO, currently enter_shop() for ALL collidable objects, but we only want to do this for shop objects
					music.pause();
					enter_shop(w, &player);
					music.play();
				}
			}
		}
		//down
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			if (player.getPos().y + moveSpeed <= map.getDim().y - charHeight) {
				//TODO - in relation to below's TODO, we check against ALL collidable objects instead of only those near us
				//TODO - use different data structure to achieve log(n) search
				sf::Vector2i dest = player.getPos();
				dest.y += moveSpeed;

				if (!checkCollision(map.getOverworldObjects(view), dest, sf::Vector2i(charWidth, charHeight), sf::Vector2i(objWidth, objHeight))) {
					player.move(sf::Vector2i(0, moveSpeed));
				}
			}
		}

		//TODO consider reputting this logic back in with keyboard movement
		//adjusts view
		//left
		if (player.getPos().x - view.getStart().x < viewWidthPadding && view.getStart().x - moveSpeed >= 0) {
			view.move(sf::Vector2i(-moveSpeed, 0));
		}
		//right
		if (view.getEnd().x - (player.getPos().x + charWidth) < viewWidthPadding && view.getEnd().x + moveSpeed <= map.getDim().x) {
			view.move(sf::Vector2i(moveSpeed, 0));
		}
		//up
		if (player.getPos().y - view.getStart().y < viewHeightPadding && view.getStart().y - moveSpeed >= 0) {
			view.move(sf::Vector2i(0, -moveSpeed));
		}
		//down
		if (view.getEnd().y - (player.getPos().y + charHeight) < viewHeightPadding && view.getEnd().y + moveSpeed <= map.getDim().y) {
			view.move(sf::Vector2i(0, moveSpeed));
		}

		//drawing stage
		(*w).clear(sf::Color::Black);

		(*w).draw(bgSprite); //background

		//overworld objects
		std::vector<OverworldObject> overObjects = map.getOverworldObjects(view); //TODO - use different data structure to achieve log(n) search
		for (auto & element : overObjects) {
			oSprite.setPosition(sf::Vector2f(element.getPos().x - view.getStart().x, element.getPos().y - view.getStart().y));
			//TODO - check that position isnt <  0,0 or > map.x, map.y
			(*w).draw(oSprite);
		}

		pSprite.setPosition(sf::Vector2f(player.getPos().x - view.getStart().x, player.getPos().y - view.getStart().y));
		(*w).draw(pSprite); //player sprite

		(*w).display();


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