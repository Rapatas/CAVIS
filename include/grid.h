#ifndef GRID_H
#define GRID_H

#include <SFML/Graphics.hpp>

class Grid : public sf::Drawable, public sf::Transformable {

	unsigned width;
	unsigned height;
	unsigned size;

	sf::VertexArray vertices;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const {

		states.transform *= getTransform();
		target.draw(vertices, states);
	}

	void add_horizontal(unsigned y, sf::Color color) {

		vertices.append(sf::Vertex(sf::Vector2f(0, y), color));
		vertices.append(sf::Vertex(sf::Vector2f(width, y), color));
	}

	void add_vertical(unsigned x, sf::Color color) {

		vertices.append(sf::Vertex(sf::Vector2f(x, 0), color));
		vertices.append(sf::Vertex(sf::Vector2f(x, height), color));
	}

public:

	Grid(unsigned width, unsigned height, unsigned size, sf::Color color) :
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
};

#endif // GRID_H
