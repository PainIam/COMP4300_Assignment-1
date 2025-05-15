# COMP4300 - Assignment 1
### Game Programming - Dave Churchill

This assignment focuses on loading game objects (Window, Font, Circle, Rectangle) from a configuration file and rendering them using SFML.

## 🛠 Features
- Loads `Window` size from `config.txt`
- Loads a custom `Font`
- Parses and creates `Circle` and `Rectangle` objects
- Each object has:
  - Initial position
  - Speed
  - Color
  - Size (radius for circles, width/height for rectangles)
- Renders objects using SFML 2.5+
## 🚀 How to Run

1. Ensure you have **SFML 2.5+** installed
2. Build the project using your IDE or `g++`:

```bash
g++ -std=c++17 main.cpp -o app -lsfml-graphics -lsfml-window -lsfml-system
