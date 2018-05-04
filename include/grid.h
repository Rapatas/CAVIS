#ifndef GRID_H
#define GRID_H

#include <SFML/Graphics.hpp>

class Grid : public sf::Drawable, public sf::Transformable {

	unsigned width;
	unsigned height;
	unsigned size;

	sf::VertexArray vertices;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void add_horizontal(unsigned y, sf::Color color);

	void add_vertical(unsigned x, sf::Color color);

public:

	Grid(unsigned width, unsigned height, unsigned size, sf::Color color);
};

#endif // GRID_H