#include "../include/pixels.h"

void Pixels::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(s, states);
}

Pixels::Pixels(unsigned width, unsigned height) :
	width(width),
	height(height)
{
	t.create(width, height);
	pixels = new uint8_t[width * height * 4];

	for (unsigned i = 0; i != width * height; ++i) {
		set_pixel(i, sf::Color::Black);
	}
}

Pixels::~Pixels() {
	delete [] pixels;
}

void Pixels::set_pixel(unsigned i, const sf::Color &color) {

	i *= 4;

	pixels[i + 0] = color.r;
	pixels[i + 1] = color.g;
	pixels[i + 2] = color.b;
	pixels[i + 3] = color.a;
}

void Pixels::update() {

	t.update(pixels);
	s.setTexture(t);
}

