#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>
#include "cavis.h"
#include "cellular_automaton.h"

class Window {

	sf::Clock clock;

	unsigned width;
	unsigned height;
	unsigned pixel_size;
	Cavis cavis;

	unsigned window_width;
	unsigned window_height;
	std::string window_name;
	sf::RenderWindow window;

public:

	Window(
		std::unique_ptr<CellularAutomaton> automaton,
		unsigned width,
		unsigned height,
		unsigned pixel_size,
		const  std::string &window_name
	);

	void run();
};

#endif // WINDOW_H
