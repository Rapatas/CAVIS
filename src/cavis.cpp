#include "../include/cavis.h"

void Cavis::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	states.transform *= getTransform();

	target.setView(view);

	target.draw(pixels, states);

	if (show_grid) {
		for (const auto &g : grids) {
			target.draw(g, states);
		}
	}
}

Cavis::Cavis(
	std::unique_ptr<CellularAutomaton> arg_automaton,
	unsigned width,
	unsigned height,
	unsigned cell_size
) :
	automaton(std::move(arg_automaton)),
	dimentions(width, height),
	cell_size(cell_size),
	view_dimentions(width * cell_size, height * cell_size),
	pixels(width, height),
	view(
		{view_dimentions.x / 2.0f, view_dimentions.y / 2.0f},
		{view_dimentions.x, view_dimentions.y}
	)
{
	automaton->set_dimentions({width, height});
	setScale(cell_size, cell_size);
}

void Cavis::update(double dt) {

	static double accumulator = 0;
	accumulator += dt;

	while (accumulator > 1 / steps_per_sec) {
		automaton->step();
		accumulator -= 1 / steps_per_sec;
	}

	for (unsigned i = 0; i != dimentions.x * dimentions.y; ++i) {
		pixels.set_pixel(i, automaton->get_pixel(i));
	}

	std::vector<Agent> agents = automaton->get_agents();

	for (auto agent : agents) {
		pixels.set_pixel(agent.x + (dimentions.x * agent.y), agent.color);
	}

	pixels.update();
}

void Cavis::handle_events(sf::Event event) {

	if (event.type == sf::Event::KeyPressed) {

		if (event.key.code == sf::Keyboard::G) {
			show_grid = !show_grid;
		}

		if (event.key.code == sf::Keyboard::R) {

			view.setSize(sf::Vector2f(view_dimentions.x, view_dimentions.y));
			view.setCenter(
				sf::Vector2f(
					dimentions.x * cell_size / 2,
					dimentions.y * cell_size / 2
				)
			);
		}
	}

	if (event.type == sf::Event::Resized) {

		view_dimentions.x = event.size.width;
		view_dimentions.y = event.size.height;

		view.setSize(view_dimentions.x, view_dimentions.y);
	}
}

void Cavis::handle_user(double dt) {

	if (
		sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
		&& steps_per_sec < 2000
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

void Cavis::add_grid(unsigned size, sf::Color color) {

	grids.emplace_back(dimentions.x, dimentions.y, size, color);
}

void Cavis::set_dimentions(sf::Vector2u new_dimentions) {

	dimentions = new_dimentions;

	automaton->set_dimentions(dimentions);

	pixels.set_dimentions(dimentions);

	for (auto &g : grids) {
		g.set_dimentions(dimentions);
	}
}

