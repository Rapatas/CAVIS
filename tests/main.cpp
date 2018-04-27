#include <SFML/Graphics.hpp>

using namespace sf;

int main() {

	// HD aspect ration = 16:9
	unsigned height = 360;
	unsigned width = height * 16 / 9;

	RenderWindow window(VideoMode(width, height), "Test CAVIS");
	window.setVerticalSyncEnabled(true);

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
		window.display();
	}

	return 0;
}

