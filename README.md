# CAVIS (Cellular Automaton View in SFML)
CAVIS provides a simple way of displaying your cellular automaton. It comes in two flavors: Window and Widget. Use the Widget to display the automaton on your own projects. Alternatively use Window to take advantage of its built-in features:
* Move the view with WASD
* Control the zoom with SHIFT & SPACE
* Control the speed up with UP & DOWN ARROWS


# Use cases: 

### [Langton's Ant](https://github.com/Rapatas/langtons_ant_sfml)

![Preview](https://i.imgur.com/3lk8FZU.png "Langtons Ant")

### [Predator & Prey](https://github.com/Rapatas/predator_and_prey_sfml)

![Preview](https://i.imgur.com/QzlzzWK.png "Preditor & Prey")

### Usage
- Implement a cellular automaton using the provided interface.
- Pass it as a template argument to the Cavis or Window constructor.

```c++
#include <CAVIS/window.h>
#include "predator_and_prey.h"

int main() {

	// HD aspect ratio = 16:9
	unsigned height = 100;
	unsigned width = height * 16 / 9;
	unsigned pixel_size = 4;

	Window<PredatorAndPrey> window(width, height, pixel_size, "Predator & Prey");
	window.run();

	return 0;
}
```
