#ifndef CAVIS_H
#define CAVIS_H

#include <vector>
#include <SFML/Graphics.hpp>

#include "cellular_automaton.h"
#include "pixels.h"
#include "grid.h"

template <class Automaton>
class Cavis : public sf::Drawable, public sf::Transformable {

	unsigned width;
	unsigned height;
	unsigned pixel_size;
	float steps_per_sec = 1;
	bool show_grid;

	Pixels pixels;
	std::vector<Grid> grids;

	Automaton automaton;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const {

		states.transform *= getTransform();
		target.draw(pixels, states);

		if (show_grid) {
			for (const auto &g : grids) {
				target.draw(g, states);
			}
		}
	}

public:

	Cavis(
		unsigned width,
		unsigned height,
		unsigned pixel_size = 5
	) :
		width(width),
		height(height),
		pixel_size(pixel_size),
		show_grid(true),
		pixels({width, height}),
		automaton(sf::Vector2u(width, height))
	{
		pixels.scale(pixel_size, pixel_size);
		automaton.set_dimentions({width, height});
	}

	void update(double dt) {

		static double accumulator = 0;
		accumulator += dt;

		while (accumulator > 1 / steps_per_sec) {
			automaton.step();
			accumulator -= 1 / steps_per_sec;
		}

		for (unsigned i = 0; i != width * height; ++i) {
			pixels.set_pixel(i, automaton.get_pixel(i));
		}

		std::vector<Agent> agents = automaton.get_agents();

		for (auto agent : agents) {
			pixels.set_pixel(agent.x + (width * agent.y), agent.color);
		}

		pixels.update();
	}

	void handle_user() {

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && steps_per_sec < 999) {
			++steps_per_sec;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && steps_per_sec > 0) {
			--steps_per_sec;
		}
	}

	void add_grid(unsigned size, sf::Color color) {

		grids.emplace_back(width, height, size, color);

		for (auto &g : grids) {
			g.setScale(pixel_size, pixel_size);
		}
	}

	void set_dimentions(sf::Vector2u dim) {

		width  = dim.x;
		height = dim.y;

		automaton.set_dimentions({width, height});

		pixels.set_dimentions({width, height});

		for (auto &g : grids) {
			g.set_dimentions({width, height});
		}
	}
};

#endif // CAVIS_H
