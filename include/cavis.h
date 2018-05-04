#ifndef CAVIS_H
#define CAVIS_H

#include <vector>
#include <SFML/Graphics.hpp>

#include "cellular_automaton.h"
#include "pixels.h"
#include "grid.h"

class Cavis : public sf::Drawable, public sf::Transformable {

	CellularAutomaton *automaton;

	unsigned width;
	unsigned height;
	unsigned pixel_size;
	float steps_per_sec = 1;

	Pixels pixels;
	std::vector<Grid> grids;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:

	Cavis(CellularAutomaton *automaton, unsigned pixel_size = 5);

	bool show_grid;

	void update(double dt);
	void handle_user();
	void add_grid(unsigned size, sf::Color color);
};

#endif // CAVIS_H
