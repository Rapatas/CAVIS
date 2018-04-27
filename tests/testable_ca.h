#ifndef TESTABLE_CA_H
#define TESTABLE_CA_H

#include "../include/cellular_automaton.h"

class TestableCA : public CellularAutomaton {

	unsigned width;
	unsigned height;

public:

	TestableCA(unsigned width, unsigned height) :
		width(width),
		height(height)
	{}

	void step() {}

	sf::Color get_pixel(unsigned i) {

		// Some shade of red
		return sf::Color(i % 255, 0, 0, 255);
	}

	unsigned get_width() { return width; }
	unsigned get_height() { return height; }

	void set_width(unsigned new_width) { width = new_width; }
	void get_height(unsigned new_height) { height = new_height; }
};

#endif // TESTABLE_CA_H
