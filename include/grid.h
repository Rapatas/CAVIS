#ifndef GRID_H
#define GRID_H

#include <SFML/Graphics.hpp>

class Grid : public sf::Drawable, public sf::Transformable {

	unsigned width;
	unsigned height;
	unsigned size;

	sf::Color color;
	sf::VertexArray vertices;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void add_horizontal(unsigned y);

	void add_vertical(unsigned x);

	void design_grid();

public:

	Grid(
		unsigned width,
		unsigned height,
		unsigned size,
		sf::Color color,
		unsigned pixel_size
	);

	void set_dimentions(sf::Vector2u dim);
};

#endif // GRID_H
