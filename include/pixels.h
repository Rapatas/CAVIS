#ifndef PIXELS_H
#define PIXELS_H

#include <SFML/Graphics.hpp>

class Pixels : public sf::Drawable, public sf::Transformable {

	unsigned width;
	unsigned height;

	uint8_t *pixels;
	sf::Texture t;
	sf::Sprite s;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void design_pixels();

public:

	Pixels(unsigned width, unsigned height);
	~Pixels();

	void set_pixel(unsigned i, const sf::Color &color);

	void update();

	void set_dimentions(sf::Vector2u dim);
};

#endif // PIXELS_H
