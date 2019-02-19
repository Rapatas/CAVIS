#include "../include/window.h"

Window::Window(
	std::unique_ptr<CellularAutomaton> automaton,
	unsigned width,
	unsigned height,
	unsigned cell_size,
	const  std::string &window_name
) :
	dimentions(width, height),
	cell_size(cell_size),
	cavis(std::move(automaton), width, height, cell_size),
	window_name(window_name),
	window(sf::VideoMode(width * cell_size, height * cell_size), window_name)
{
	window.setVerticalSyncEnabled(true);
	cavis.add_grid(1,  sf::Color(50,  50,  50,  255));
	cavis.add_grid(5,  sf::Color(100, 100, 100, 255));
	cavis.add_grid(10, sf::Color(150, 150, 150, 255));
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

