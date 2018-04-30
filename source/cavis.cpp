#include "../include/cavis.h"

#include <iostream>

void Cavis::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(pixels, states);
}

Cavis::Cavis(CellularAutomaton *automaton) :
	automaton(automaton),
	width(automaton->get_width()),
	height(automaton->get_height()),
	pixels(width, height)
{}

void Cavis::update(double dt) {

	static double accumulator = 0;
	accumulator += dt;
	unsigned counter = 0;

	while (accumulator > 1 / steps_per_sec) {
		++counter;
		automaton->step();
		accumulator -= 1 / steps_per_sec;
	}
	std::cout << counter << '\n';

	for (unsigned i = 0; i != width * height; ++i) {
		pixels.set_pixel(i, automaton->get_pixel(i));
	}

	pixels.update();
}

