#ifndef CAVIS_H
#define CAVIS_H

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

#include "cellular_automaton.h"
#include "pixels.h"
#include "grid.h"

class Cavis : public sf::Drawable, public sf::Transformable {

	unsigned width;
	unsigned height;
	unsigned pixel_size;
	float steps_per_sec = 1;
	bool show_grid;

	Pixels pixels;
	std::vector<Grid> grids;

	std::unique_ptr<CellularAutomaton> automaton;

	unsigned view_width;
	unsigned view_height;
	float view_speed = 50;
	float view_zoom  = 1.01;
	sf::View view;

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
