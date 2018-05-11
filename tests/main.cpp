#include <SFML/Graphics.hpp>

#include "../include/cavis.h"
#include "langtons_ant.h"

using namespace sf;

int main() {

	// HD aspect ratio = 16:9
	unsigned height = 100;
	unsigned width = height * 16 / 9;
	unsigned pixel_size = 4;

	unsigned window_width = width * pixel_size;
	unsigned window_height = height * pixel_size;

	RenderWindow window(VideoMode(window_width, window_height), "Test CAVIS");
	window.setVerticalSyncEnabled(true);
	sf::Clock clock;

	View view(Vector2f(window_width / 2, window_height / 2), Vector2f(window_width, window_height));
	float view_speed = 50;
	float view_zoom = 1.01;

	LangtonsAnt t(width, height, 3);
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
				if (event.key.code == Keyboard::R) {
					view.setSize(Vector2f(window_width, window_height));
					view.setCenter(Vector2f(window_width / 2, window_height / 2));
				}
			}
		}

		double dt = clock.restart().asSeconds();

		if (Keyboard::isKeyPressed(Keyboard::W)) {
			view.move(0, -dt * view_speed);
		}
		if (Keyboard::isKeyPressed(Keyboard::S)) {
			view.move(0, dt * view_speed);
		}
		if (Keyboard::isKeyPressed(Keyboard::A)) {
			view.move(-dt * view_speed, 0);
		}
		if (Keyboard::isKeyPressed(Keyboard::D)) {
			view.move(dt * view_speed, 0);
		}
		if (Keyboard::isKeyPressed(Keyboard::LShift)) {
			view.zoom(1 / view_zoom);
		}
		if (Keyboard::isKeyPressed(Keyboard::Space)) {
			view.zoom(view_zoom);
		}

		window.setView(view);

		window.clear();
		c.handle_user();
		c.update(dt);
		window.draw(c);
		window.display();
	}

	return 0;
}

