#ifndef CAVIS_H
#define CAVIS_H

#include <SFML/Graphics.hpp>

#include "cellular_automaton.h"

class Cavis : public sf::Drawable, public sf::Transformable {

	CellularAutomaton *automaton;

	unsigned width;
	unsigned height;
	float steps_per_sec = 100;

	uint8_t *pixels;
	sf::Texture t;
	sf::Sprite s;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:

	Cavis(CellularAutomaton *automaton);
	Cavis(CellularAutomaton *automaton, unsigned width, unsigned height);

	void set_pixel(unsigned i, const sf::Color &color);

	void update(double dt);
};

#endif // CAVIS_H
