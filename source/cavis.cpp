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

Cavis::Cavis(CellularAutomaton *automaton) :
	automaton(automaton),
	width(automaton->get_width()),
	height(automaton->get_height()),
	pixels(width, height),
	show_grid(false)
{}

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
}
