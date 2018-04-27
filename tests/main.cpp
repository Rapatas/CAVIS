#include <SFML/Graphics.hpp>

#include "../include/cavis.h"
#include "testable_ca.h"

using namespace sf;

int main() {

	// HD aspect ration = 16:9
	unsigned height = 360;
	unsigned width = height * 16 / 9;

	RenderWindow window(VideoMode(width, height), "Test CAVIS");
	window.setVerticalSyncEnabled(true);

	TestableCA t(width, height);
	Cavis c(&t);

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

		window.clear();
		c.update();
		window.draw(c);
		window.display();
	}

	return 0;
}

