#include <SFML/Graphics.hpp>

#include "../include/cavis.h"
#include "langtons_ant.h"

using namespace sf;

int main() {

	// HD aspect ratio = 16:9
	unsigned height = 100;
	unsigned width = height * 16 / 9;

	RenderWindow window(VideoMode(width, height), "Test CAVIS");
	window.setVerticalSyncEnabled(true);
	sf::Clock clock;

	LangtonsAntModel t(width, height, 3);
	Cavis c(&t);
	c.add_grid(1, Color(100,100,100,255));
	c.add_grid(5, Color(200,200,200,255));

	while (window.isOpen()) {

		Event event;
		while (window.pollEvent(event)) {
			if (
				event.type == Event::Closed
				|| Keyboard::isKeyPressed(Keyboard::Escape)
			) {
				window.close();
			}
		}

		double dt = clock.restart().asSeconds();

		window.clear();
		c.handle_user();
		c.update(dt);
		window.draw(c);
		window.display();
	}

	return 0;
}

