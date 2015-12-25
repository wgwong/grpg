#include "init.h"

int init() {
	//intialization
	//TODO - put all this in the title screen or something later
	sf::RenderWindow window;
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8; //smoother shapes
	int width = 800;
	int height = 600;
	window.create(sf::VideoMode(width, height), "Generic RPG v0.1a ", sf::Style::Default, settings);
	window.setVerticalSyncEnabled(true);

	overmap(&window);
	//return title_screen();

	return 0;
}