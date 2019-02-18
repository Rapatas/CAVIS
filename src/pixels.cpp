#include "../include/pixels.h"

void Pixels::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	target.draw(s, states);
}

void Pixels::design_pixels() {

	t.create(width, height);

	if (pixels != nullptr) { delete [] pixels; }
	pixels = new uint8_t[width * height * 4];

	for (unsigned i = 0; i != width * height; ++i) {
		set_pixel(i, sf::Color::Black);
	}
}

Pixels::Pixels(unsigned width, unsigned height, unsigned pixel_size) :
	width(width),
	height(height),
	pixels(nullptr)
{
	design_pixels();
	setScale(pixel_size, pixel_size);
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

void Pixels::set_dimentions(sf::Vector2u dim) {

	width = dim.x;
	height = dim.y;

	design_pixels();
}
