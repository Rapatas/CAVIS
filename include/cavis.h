#ifndef CAVIS_H
#define CAVIS_H

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

#include "cellular_automaton.h"
#include "pixels.h"
#include "grid.h"

class Cavis : public sf::Drawable, public sf::Transformable {

	float steps_per_sec = 5;
	float view_speed    = 100;
	float view_zoom     = 1.01;
	bool show_grid      = true;

	std::unique_ptr<CellularAutomaton> automaton;
	sf::Vector2u dimentions;
	unsigned cell_size;
	sf::Vector2f view_dimentions;
	Pixels pixels;
	sf::View view;
	std::vector<Grid> grids;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:

	Cavis(
		std::unique_ptr<CellularAutomaton> automaton,
		unsigned width,
		unsigned height,
		unsigned pixel_size = 5
	);

	void update(double dt);

	void handle_events(sf::Event event);

	void handle_user(double dt);

	void add_grid(unsigned size, sf::Color color);

	void set_dimentions(sf::Vector2u dim);
};

#endif // CAVIS_H
