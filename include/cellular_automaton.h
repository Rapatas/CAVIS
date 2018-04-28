#ifndef CELLULAR_AUTOMATON
#define CELLULAR_AUTOMATON

#include <SFML/Graphics.hpp>

class CellularAutomaton {

public:

	virtual ~CellularAutomaton() {}

	virtual void step() = 0;
	virtual sf::Color get_pixel(unsigned i) = 0;

	virtual unsigned get_width() = 0;
	virtual unsigned get_height() = 0;
};

#endif // CELLULAR_AUTOMATON
