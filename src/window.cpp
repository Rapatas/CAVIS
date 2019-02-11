#include "../include/window.h"

Window::Window(
	CellularAutomaton *automaton,
	unsigned width,
	unsigned height,
	unsigned pixel_size,
	const  std::string &window_name
) :
	width(width),
	height(height),
	pixel_size(pixel_size),
	cavis(automaton, width, height, pixel_size),
	window_width(width * pixel_size),
	window_height(height * pixel_size),
	window_name(window_name),
	window(sf::VideoMode(window_width, window_height), window_name)
{
	window.setVerticalSyncEnabled(true);
	cavis.add_grid(1,  sf::Color(50,50,50,255));
	cavis.add_grid(5,  sf::Color(100,100,100,255));
	cavis.add_grid(10, sf::Color(150,150,150,255));
}

void Window::run() {

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
			cavis.handle_events(event);
		}

		window.clear();
		cavis.handle_user(dt);
		cavis.update(dt);
		window.draw(cavis);
		window.display();
	}
}

