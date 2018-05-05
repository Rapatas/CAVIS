#ifndef LANGTONS_ANT_H
#define LANGTONS_ANT_H

#include <vector>
#include <random>
#include <iostream>

#include <flat_matrix/flat_matrix.h>

#include "../include/cellular_automaton.h"

using namespace std;

class LangtonsAnt : public CellularAutomaton {

private:

	struct Ant {

		enum class Direction {
			up, right, down, left
		};

		unsigned x;
		unsigned y;
		Direction direction;

		Ant() = default;

		Ant(unsigned x, unsigned y) :
			x(x),
			y(y),
			direction(Direction::up)
		{}

		void turn_right() {

			switch (direction) {

			case Direction::up:
				direction = Direction::right;
				break;
			case Direction::right:
				direction = Direction::down;
				break;
			case Direction::down:
				direction = Direction::left;
				break;
			case Direction::left:
				direction = Direction::up;
				break;
			}
		}

		void turn_left() {

			switch (direction) {

			case Direction::up:
				direction = Direction::left;
				break;
			case Direction::right:
				direction = Direction::up;
				break;
			case Direction::down:
				direction = Direction::right;
				break;
			case Direction::left:
				direction = Direction::down;
				break;
			}
		}

		void move(unsigned height, unsigned width) {

			switch(direction) {

			case Direction::up:
				y = y == height - 1
					? 0
					: y + 1;
				break;
			case Direction::right:
				x = x == width - 1
					? 0
					: x + 1;
				break;
			case Direction::down:
				y = y == 0
					? height - 1
					: y - 1;
				break;
			case Direction::left:
				x = x == 0
					? width - 1
					: x - 1;
				break;
			}
		}
	};

	unsigned width;
	unsigned height;
	flat_matrix<bool> state;
	flat_matrix<bool> next_state;
	unsigned num_of_ants;
	vector<Ant> ants;

	default_random_engine generator;
	uniform_int_distribution<unsigned> distribution_x;
	uniform_int_distribution<unsigned> distribution_y;

	void initialize_states() {

		for (unsigned i = 0; i != width * height; ++i) {
			state[i] = false;
			next_state[i] = false;
		}
	}

	void place_ant_rand() {

		unsigned x_pos = distribution_x(generator);
		unsigned y_pos = distribution_y(generator);

		ants.push_back({x_pos, y_pos});
	}

public:

	LangtonsAnt(unsigned width, unsigned height, unsigned num_of_ants) :
		width(width),
		height(height),
		state(flat_matrix<bool>(width, height)),
		next_state(flat_matrix<bool>(width, height)),
		num_of_ants(num_of_ants),
		distribution_x(uniform_int_distribution<unsigned>(0, width - 1)),
		distribution_y(uniform_int_distribution<unsigned>(0, height - 1))
	{
		generator.seed(random_device()());

		initialize_states();

		for (unsigned i = 0; i != num_of_ants; ++i) {
			place_ant_rand();
		}
	}

	void step() {

		for (unsigned i = 0; i != num_of_ants; ++i) {

			// Yes, I'm lazy.
			Ant &ant = ants[i];

			next_state(ant.x, ant.y) = !state(ant.x, ant.y);

			if (state(ant.x, ant.y)) {
				ant.turn_right();
			} else {
				ant.turn_left();
			}

			ant.move(height, width);
		}

		state = next_state;
	}

	sf::Vector2u get_dimentions() {
		return {width, height};
	}

	void set_dimentions(sf::Vector2u dim) {

		width = dim.x;
		height = dim.y;

		distribution_x = uniform_int_distribution<unsigned>(0, width - 1);
		distribution_y = uniform_int_distribution<unsigned>(0, height - 1);

		state = flat_matrix<bool>(width, height);
		next_state = flat_matrix<bool>(width, height);
		initialize_states();

		ants.clear();
		for (unsigned i = 0; i != num_of_ants; ++i) {
			place_ant_rand();
		}
	}

	sf::Color get_pixel(unsigned i) {
		return state[i]
			? sf::Color::Cyan
			: sf::Color::Black;
	}
};

#endif // LANGTONS_ANT_H
