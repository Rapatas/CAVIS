#ifndef AGENT_H
#define AGENT_H

#include <SFML/Graphics.hpp>

class Agent {

public:

	unsigned x;
	unsigned y;
	sf::Color color;

	Agent(unsigned x, unsigned y, sf::Color color) :
		x(x),
		y(y),
		color(color)
	{}
};

#endif // AGENT_H
