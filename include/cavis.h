#ifndef CAVIS_H
#define CAVIS_H

#include <SFML/Graphics.hpp>

#include "cellular_automaton.h"
#include "pixels.h"

class Cavis : public sf::Drawable, public sf::Transformable {

	CellularAutomaton *automaton;

	unsigned width;
	unsigned height;
	float steps_per_sec = 1;

	Pixels pixels;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:

	Cavis(CellularAutomaton *automaton);

	void update(double dt);

	void handle_user();
};

#endif // CAVIS_H
