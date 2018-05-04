#include <SFML/Graphics.hpp>

#include "../include/cavis.h"
#include "langtons_ant.h"

using namespace sf;

int main() {

	// HD aspect ratio = 16:9
	unsigned height = 100;
	unsigned width = height * 16 / 9;
	unsigned pixel_size = 4;

	RenderWindow window(VideoMode(width * pixel_size, height * pixel_size), "Test CAVIS");
	window.setVerticalSyncEnabled(true);
	sf::Clock clock;

	LangtonsAntModel t(width, height, 3);
	Cavis c(&t, pixel_size);
	c.add_grid(1, Color(50,50,50,255));
	c.add_grid(5, Color(100,100,100,255));
	c.add_grid(10, Color(150,150,150,255));

	while (window.isOpen()) {

		Event event;
		while (window.pollEvent(event)) {
			if (
				event.type == Event::Closed
				|| Keyboard::isKeyPressed(Keyboard::Escape)
			) {
				window.close();
			}
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::G) {
					c.show_grid = !(c.show_grid);
				}
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

