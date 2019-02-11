#include "../include/grid.h"

void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	states.transform *= getTransform();
	target.draw(vertices, states);
}

void Grid::add_horizontal(unsigned y) {

	vertices.append(sf::Vertex(sf::Vector2f(0, y), color));
	vertices.append(sf::Vertex(sf::Vector2f(width, y), color));
}

void Grid::add_vertical(unsigned x) {

	vertices.append(sf::Vertex(sf::Vector2f(x, 0), color));
	vertices.append(sf::Vertex(sf::Vector2f(x, height), color));
}

void Grid::design_grid() {

	vertices.clear();

	for (unsigned i = 0; i < height / size + 0.5; ++i) {
		add_horizontal(i * size);
	}
	add_horizontal(height);

	for (unsigned i = 0; i < width / size + 0.5; ++i) {
		add_vertical(i * size);
	}
	add_vertical(width);
}


Grid::Grid(
	unsigned width,
	unsigned height,
	unsigned size,
	sf::Color color
) :
	width(width),
	height(height),
	size(size),
	color(color)
{
	vertices.setPrimitiveType(sf::Lines);
	design_grid();
}

void Grid::set_dimentions(sf::Vector2u dim) {

	width  = dim.x;
	height = dim.y;

	design_grid();
}
