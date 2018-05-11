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

Cavis::Cavis(CellularAutomaton *automaton, unsigned pixel_size) :
	automaton(automaton),
	width(automaton->get_dimentions().x),
	height(automaton->get_dimentions().y),
	pixel_size(pixel_size),
	pixels(width, height),
	show_grid(true)
{
	pixels.scale(pixel_size, pixel_size);
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

