# CAVIS (Cellular Automaton View in SFML)
CAVIS provides a simple way of displaying your cellular automaton. It comes in two flavors: Window and Widget. Use the Widget to display the automaton on your own projects. Alternatively use the Window and get started fast!

# Contents
- [Features](#features)
- [Use cases](#use-cases)
    - [Langton's Ant](#langtons-ant)
    - [Predator & Prey](#predator--prey)
- [Installation](#installation)
    - [Dependencies](#dependencies)
    - [CAVIS (Linux)](#cavis-linux)
- [Usage](#usage)

# Features:
* Move the view with WASD.
* Reset view with R.
* Control zoom with LShift & Space.
* Control steps per second up with Up & Down arrows.
* Show/Hide the grid with G.

# Use cases:

### [Langton's Ant](https://github.com/Rapatas/langtons_ant_sfml)

[![Preview](https://i.imgur.com/348YuU3.gif "3 ants on a torus")](https://github.com/Rapatas/langtons_ant_sfml)

### [Predator & Prey](https://github.com/Rapatas/predator_and_prey_sfml)

[![Preview](https://i.imgur.com/LzmDeJM.gif "Preditor & Prey")](https://github.com/Rapatas/predator_and_prey_sfml)

# Installation

## Dependencies
CAVIS is based on [SFML (Simple & Fast Multimedia Library)](https://www.sfml-dev.org/index.php). Follow SFML's documentation to install it. 

For Ubuntu simply ```apt install libsfml-dev```

## CAVIS (Linux)
```bash
git clone https://github.com/Rapatas/CAVIS.git
mkdir CAVIS/build
cd CAVIS/build
cmake ..
make install # As root
```

# Usage
- Implement a cellular automaton using the provided interface ([cellular_automaton.h](include/cellular_automaton.h)).
- Pass it as a std::unique_ptr to the Cavis or Window constructor.

```c++
#include <CAVIS/window.h>
#include "predator_and_prey.h"

int main() {

    // HD aspect ratio = 16:9
    unsigned height = 100;
    unsigned width = height * 16 / 9;
    unsigned cell_size = 4;

    Window window(
        std::make_unique<PredatorAndPrey>(), 
        width, 
        height, 
        cell_size, 
        "Predator & Prey"
    );

    window.run();

    return 0;
}
```
