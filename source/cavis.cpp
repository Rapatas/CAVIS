#include "../include/cavis.h"

void Cavis::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	states.transform *= getTransform();
	target.draw(pixels, states);

	if (show_grid) {
		for (const auto &g : grids) {
			target.draw(g, states);
		}
	}
}

Cavis::Cavis(
	CellularAutomaton *automaton,
	unsigned width,
	unsigned height,
	unsigned pixel_size
) :
	automaton(automaton),
	width(width),
	height(height),
	pixel_size(pixel_size),
	show_grid(true),
	pixels({width, height})
{
	pixels.scale(pixel_size, pixel_size);
	automaton->set_dimentions({width, height});
}

void Cavis::update(double dt) {

	static double accumulator = 0;
	accumulator += dt;

	while (accumulator > 1 / steps_per_sec) {
		automaton->step();
		accumulator -= 1 / steps_per_sec;
	}

	for (unsigned i = 0; i != width * height; ++i) {
		pixels.set_pixel(i, automaton->get_pixel(i));
	}

	std::vector<Agent> agents = automaton->get_agents();

	for (auto agent : agents) {
		pixels.set_pixel(agent.x + (width * agent.y), agent.color);
	}

	pixels.update();
}

void Cavis::handle_user() {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && steps_per_sec < 999) {
		++steps_per_sec;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && steps_per_sec > 0) {
		--steps_per_sec;
	}
}

void Cavis::add_grid(unsigned size, sf::Color color) {

	grids.emplace_back(width, height, size, color);

	for (auto &g : grids) {
		g.setScale(pixel_size, pixel_size);
	}
}

void Cavis::set_dimentions(sf::Vector2u dim) {

	width  = dim.x;
	height = dim.y;

	automaton->set_dimentions({width, height});

	pixels.set_dimentions({width, height});

	for (auto &g : grids) {
		g.set_dimentions({width, height});
	}
}
