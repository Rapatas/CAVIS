#include "../include/grid.h"

void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	states.transform *= getTransform();
	target.draw(vertices, states);
}

void Grid::add_horizontal(unsigned y, sf::Color color) {

	vertices.append(sf::Vertex(sf::Vector2f(0, y), color));
	vertices.append(sf::Vertex(sf::Vector2f(width, y), color));
}

void Grid::add_vertical(unsigned x, sf::Color color) {

	vertices.append(sf::Vertex(sf::Vector2f(x, 0), color));
	vertices.append(sf::Vertex(sf::Vector2f(x, height), color));
}


Grid::Grid(unsigned width, unsigned height, unsigned size, sf::Color color) :
	width(width),
	height(height),
	size(size)
{
	vertices.setPrimitiveType(sf::Lines);

	for (unsigned i = 0; i != height / size; ++i) {
		add_horizontal(i * size, color);
	}
	add_horizontal(height, color);

	for (unsigned i = 0; i != width / size; ++i) {
		add_vertical(i * size, color);
	}
	add_vertical(width, color);
}

