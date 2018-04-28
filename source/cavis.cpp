#include "../include/cavis.h"

void Cavis::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(s, states);
}

Cavis::Cavis(CellularAutomaton *automaton) :
	automaton(automaton),
	width(automaton->get_width()),
	height(automaton->get_height())
{
	t.create(width, height);
	pixels = new uint8_t[width * height * 4];

	for (unsigned i = 0; i != width * height; ++i) {
		set_pixel(i, sf::Color::Black);
	}
}

Cavis::Cavis(CellularAutomaton *automaton, unsigned width, unsigned height) :
	automaton(automaton),
	width(width),
	height(height)
{
	t.create(width, height);
	pixels = new uint8_t[width * height * 4];

	for (unsigned i = 0; i != width * height; ++i) {
		set_pixel(i, sf::Color::Black);
	}
}

void Cavis::set_pixel(unsigned i, const sf::Color &color) {

	i *= 4;

	pixels[i + 0] = color.r;
	pixels[i + 1] = color.g;
	pixels[i + 2] = color.b;
	pixels[i + 3] = color.a;
}

void Cavis::update(double dt) {

	static double accumulator = 0;
	accumulator += dt;

	while (accumulator > 1 / steps_per_sec) {
		automaton->step();
		accumulator -= 1 / steps_per_sec;
	}

	for (unsigned i = 0; i != width * height; ++i) {
		set_pixel(i, automaton->get_pixel(i));
	}

	t.update(pixels);
	s.setTexture(t);
}

