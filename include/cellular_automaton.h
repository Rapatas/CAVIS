#ifndef CELLULAR_AUTOMATON
#define CELLULAR_AUTOMATON

#include <SFML/Graphics.hpp>
#include <vector>
#include "agent.h"

class CellularAutomaton {

public:

	virtual ~CellularAutomaton() {}

	virtual void step() = 0;
	virtual sf::Color get_pixel(unsigned i) = 0;

	virtual sf::Vector2u get_dimentions() = 0;
	virtual void set_dimentions(sf::Vector2u dim) = 0;

	virtual std::vector<Agent> get_agents() = 0;
};

#endif // CELLULAR_AUTOMATON
