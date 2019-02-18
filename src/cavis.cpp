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
	unsigned pixel_size
) :
	width(width),
	height(height),
	pixel_size(pixel_size),
	view_width(width * pixel_size),
	view_height(height * pixel_size),
	pixels(width, height, pixel_size),
	automaton(std::move(arg_automaton)),
	view(
		{view_width / 2.0f, view_height / 2.0f},
		{(float) view_width, (float) view_height}
	)
{
	automaton->set_dimentions({width, height});
}

void Cavis::update(double dt) {

	static double accumulator = 0;
	accumulator += dt;

	while (accumulator > 1 / steps_per_sec) {
		automaton->step();
		accumulator -= 1 / steps_per_sec;
	}

	for (unsigned i = 0; i != width * height; ++i) {
		pixels.set_pixel(i, automaton->get_pixel(i));
	}

	std::vector<Agent> agents = automaton->get_agents();

	for (auto agent : agents) {
		pixels.set_pixel(agent.x + (width * agent.y), agent.color);
	}

	pixels.update();
}

void Cavis::handle_events(sf::Event event) {

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

	if (event.type == sf::Event::Resized) {

		view_width = event.size.width;
		view_height = event.size.height;

		view.setSize(view_width, view_height);
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

	grids.emplace_back(width, height, size, color, pixel_size);
}

void Cavis::set_dimentions(sf::Vector2u dim) {

	width  = dim.x;
	height = dim.y;

	automaton->set_dimentions({width, height});

	pixels.set_dimentions({width, height});

	for (auto &g : grids) {
		g.set_dimentions({width, height});
	}
}

