# CAVIS
Cellular Automaton View in SFML

# Langtons Ant
![Preview](https://i.imgur.com/3lk8FZU.png "Langtons Ant")

# Usage
- Implement a cellular automaton using the provided interface.
- Pass it as an argument to the Cavis constructor.
- Drop it in your project.

```c++
LangtonsAntModel t(width, height, 3);
Cavis c(&t, pixel_size);
c.add_grid(1, Color(50,50,50,255));
c.add_grid(5, Color(100,100,100,255));
c.add_grid(10, Color(150,150,150,255));

// == //

c.handle_user();
c.update(dt);
window.draw(c);
```
