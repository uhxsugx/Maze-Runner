# Pyramid Themed Maze Runner

*A 2D maze adventure game built with C++ and SFML.*

---

## Introduction

Pyramid Themed Maze Runner is a 2D adventure game set inside the mysterious pyramids of Ancient Egypt. Players navigate winding mazes, dodge enemies, and overcome obstacles on their way to the exit.

The game is built with **C++17** and **SFML 3.x** as part of a university programming project.

## Game Overview

Players explore Egyptian-themed mazes filled with challenges, including a health system, enemy encounters, and multiple levels. Both single-player and multiplayer modes are planned. In multiplayer, two players will share one keyboard and explore the maze together.

## Controls

### Player 1

| Key | Action |
|:---:|---|
| W | Move up |
| A | Move left |
| S | Move down |
| D | Move right |

### Player 2 (Multiplayer)

| Key | Action |
|:---:|---|
| ↑ | Move up |
| ↓ | Move down |
| ← | Move left |
| → | Move right |

### General

| Key | Action |
|:---:|---|
| ESC | Quit the game |

## Key Features

- Single-player mode
- Two-player multiplayer mode (planned)
- Player health system
- Enemies such as mummies
- Collision detection
- Multiple levels with rising difficulty
- Pharaoh boss encounter (planned)

## Technologies Used

- **C++17**
- **SFML 3.x**
- **Visual Studio 2022**
- **Git and GitHub**

## Installation and Setup

You will need Visual Studio 2022, a C++17-compatible compiler, and SFML 3.x installed and configured.

### Using Visual Studio

1. Clone the repository from GitHub.
2. Open the project in Visual Studio.
3. Link the required SFML libraries and add the DLL files.
4. Build and run the project.

### Using the Command Line

If you prefer to build from the command line, clone the repository, make sure SFML is installed and accessible to your compiler, then run the following command from the project folder:

```bash
g++ main.cpp player.cpp player2.cpp enemies.cpp map.cpp sounds.cpp menus.cpp -std=c++17 -O2 -o MazeRunner.exe -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
```

This compiles the source files and produces `MazeRunner.exe`, which you can then run directly.

## Development Team

- Muhammad Umer Saeed
- Huzaifa Mustafa
- Muhammad Kazim Raza

## Future Improvements

We plan to add computer-generated random mazes in a future update.

## Note

This project was developed for educational purposes as part of a university programming course.
