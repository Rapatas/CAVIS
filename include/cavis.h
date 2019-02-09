#ifndef CAVIS_H
#define CAVIS_H

#include <vector>
#include <SFML/Graphics.hpp>

#include "cellular_automaton.h"
#include "pixels.h"
#include "grid.h"

template <class Automaton>
class Cavis : public sf::Drawable, public sf::Transformable {

	unsigned width;
	unsigned height;
	unsigned pixel_size;
	float steps_per_sec = 1;
	bool show_grid;

	Pixels pixels;
	std::vector<Grid> grids;

	Automaton automaton;

	unsigned view_width;
	unsigned view_height;
	float view_speed = 50;
	float view_zoom  = 1.01;
	sf::View view;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const {

		states.transform *= getTransform();

		target.setView(view);

		target.draw(pixels, states);

		if (show_grid) {
			for (const auto &g : grids) {
				target.draw(g, states);
			}
		}
	}

public:

	Cavis(
		unsigned width,
		unsigned height,
		unsigned pixel_size = 5
	) :
		width(width),
		height(height),
		pixel_size(pixel_size),
		show_grid(true),
		pixels({width, height}),
		automaton(sf::Vector2u(width, height)),
		view_width(width * pixel_size),
		view_height(height * pixel_size),
		view(
			{view_width / 2.0f, view_height / 2.0f},
			{view_width, view_height}
		)
	{
		pixels.scale(pixel_size, pixel_size);
		automaton.set_dimentions({width, height});
	}

	void update(double dt) {

		static double accumulator = 0;
		accumulator += dt;

		while (accumulator > 1 / steps_per_sec) {
			automaton.step();
			accumulator -= 1 / steps_per_sec;
		}

		for (unsigned i = 0; i != width * height; ++i) {
			pixels.set_pixel(i, automaton.get_pixel(i));
		}

		std::vector<Agent> agents = automaton.get_agents();

		for (auto agent : agents) {
			pixels.set_pixel(agent.x + (width * agent.y), agent.color);
		}

		pixels.update();
	}

	void handle_events(sf::Event event) {

		if (event.type == sf::Event::KeyPressed) {

			if (event.key.code == sf::Keyboard::G) {
				show_grid = !show_grid;
			}
		}

		if (event.key.code == sf::Keyboard::R) {
			view.setSize(sf::Vector2f(view_width, view_height));
			view.setCenter(
				sf::Vector2f(view_width / 2, view_height / 2)
			);
		}
	}

	void handle_user(double dt) {

		if (
			sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
			&& steps_per_sec < 1999
		) {
			++steps_per_sec;
		}
		if (
			sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
			&& steps_per_sec > 0
		) {
			--steps_per_sec;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			view.move(0, -dt * view_speed);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			view.move(0, dt * view_speed);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			view.move(-dt * view_speed, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			view.move(dt * view_speed, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
			view.zoom(1 / view_zoom);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			view.zoom(view_zoom);
		}
	}

	void add_grid(unsigned size, sf::Color color) {

		grids.emplace_back(width, height, size, color);

		for (auto &g : grids) {
			g.setScale(pixel_size, pixel_size);
		}
	}

	void set_dimentions(sf::Vector2u dim) {

		width  = dim.x;
		height = dim.y;

		automaton.set_dimentions({width, height});

		pixels.set_dimentions({width, height});

		for (auto &g : grids) {
			g.set_dimentions({width, height});
		}
	}
};

#endif // CAVIS_H
