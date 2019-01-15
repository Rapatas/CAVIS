#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>
#include "cavis.h"
#include "cellular_automaton.h"

template <class CellularAutomaton>
class Window {

	sf::Clock clock;

	unsigned width;
	unsigned height;
	unsigned pixel_size;
	Cavis<CellularAutomaton> cavis;

	unsigned window_width;
	unsigned window_height;
	std::string window_name;
	sf::RenderWindow window;

	float view_speed = 50;
	float view_zoom  = 1.01;
	sf::View view;

public:

	Window(
		unsigned width,
		unsigned height,
		unsigned pixel_size,
		const  std::string &window_name
	) :
		width(width),
		height(height),
		pixel_size(pixel_size),
		cavis(width, height, pixel_size),
		window_width(width * pixel_size),
		window_height(height * pixel_size),
		window_name(window_name),
		window(sf::VideoMode(window_width, window_height), window_name),
		view(
			sf::Vector2f(window_width / 2, window_height / 2),
			sf::Vector2f(window_width, window_height)
		)
	{
		window.setVerticalSyncEnabled(true);
		cavis.add_grid(1,  sf::Color(50,50,50,255));
		cavis.add_grid(5,  sf::Color(100,100,100,255));
		cavis.add_grid(10, sf::Color(150,150,150,255));
	}

	void run() {

		while (window.isOpen()) {

			double dt = clock.restart().asSeconds();

			sf::Event event;
			while (window.pollEvent(event)) {
				if (
					event.type == sf::Event::Closed
					|| event.key.code == sf::Keyboard::Escape
				) {
					window.close();
				}
				if (event.key.code == sf::Keyboard::R) {
					view.setSize(sf::Vector2f(window_width, window_height));
					view.setCenter(
						sf::Vector2f(window_width / 2, window_height / 2)
					);
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				view.move(0, -dt * view_speed);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				view.move(0, dt * view_speed);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				view.move(-dt * view_speed, 0);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				view.move(dt * view_speed, 0);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
				view.zoom(1 / view_zoom);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				view.zoom(view_zoom);
			}

			window.setView(view);

			window.clear();
			cavis.handle_user();
			cavis.update(dt);
			window.draw(cavis);
			window.display();
		}
	}
};

#endif // WINDOW_H
