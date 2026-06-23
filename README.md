# Cub3D

A simple 3D raycasting engine inspired by **Wolfenstein 3D**, developed in C as part of the 42 curriculum.

The project renders a first-person view from a 2D `.cub` map using **MLX42**, textures, player movement and collision detection.

## About

`cub3D` simulates a 3D environment using the raycasting technique.  
The map is stored as a 2D grid, and for each vertical column of the screen the program casts a ray from the player position until it hits a wall.

The distance to the wall is then used to draw a vertical slice with the correct height and texture, creating the illusion of depth.

## Features

- Raycasting engine
- First-person player movement
- Player rotation
- Wall collision detection
- `.cub` map parsing
- Map validation
- Floor and ceiling colors
- Textured walls for each direction: `NO`, `SO`, `WE`, `EA`
- Real-time rendering with MLX42

## How Raycasting Works

For each frame:

1. The player position and direction are updated.
2. A ray is cast for each screen column.
3. The ray moves through the map grid until it hits a wall.
4. The wall distance is calculated.
5. A vertical textured slice is drawn.
6. Repeating this for all columns creates a 3D perspective.

## Map Format

Maps use the `.cub` extension and must contain:

- North texture path: `NO`
- South texture path: `SO`
- West texture path: `WE`
- East texture path: `EA`
- Floor RGB color: `F`
- Ceiling RGB color: `C`
- A valid closed map
- One player starting position: `N`, `S`, `E` or `W`

Example:

```txt
NO ./textures/no.png
SO ./textures/so.png
WE ./textures/we.png
EA ./textures/ea.png

F 2,51,0
C 225,30,0

111111
100001
1000N1
100001
111111
```

Map characters:

| Character | Meaning |
|----------|---------|
| `1` | Wall |
| `0` | Empty space |
| `N` | Player facing north |
| `S` | Player facing south |
| `E` | Player facing east |
| `W` | Player facing west |
| ` ` | Space / outside map area |

## Controls

| Key | Action |
|----|--------|
| `W` | Move forward |
| `S` | Move backward |
| `A` | Move left |
| `D` | Move right |
| `←` | Rotate left |
| `→` | Rotate right |
| `ESC` | Exit |

## Project Structure

```txt
.
├── include/        # Header files and main structures
├── src_exec/       # Raycasting, rendering, movement and controls
├── srcs_parser/    # File parsing and map validation
├── textures/       # Wall textures
├── tests/          # Example .cub maps
├── MLX42/          # Graphics library
├── Makefile
└── README.md
```

## Compilation

Compile the project:

```bash
make
```

This creates the executable:

```bash
./cub3D
```

Clean object files:

```bash
make clean
```

Remove object files, executable and MLX42 build files:

```bash
make fclean
```

Recompile everything:

```bash
make re
```

## Usage

Run the program with a valid `.cub` map:

```bash
./cub3D tests/valid.cub
```

## Requirements

- C compiler
- Make
- CMake
- MLX42
- GLFW
- OpenGL

On Linux, you may need to install GLFW and OpenGL development packages:

```bash
sudo apt install cmake libglfw3-dev libgl1-mesa-dev xorg-dev
```

## What I Learned

Through this project I practiced:

- Raycasting fundamentals
- Basic 3D rendering from a 2D map
- Vector-based movement and rotation
- Texture loading and drawing
- Collision detection
- File parsing and validation
- Structuring a larger C project
- Working with MLX42
- Debugging graphical programs

## Technologies

- C
- MLX42
- GLFW
- OpenGL
- Makefile
- Raycasting

## Notes

This project is part of the 42 curriculum.  
It is mainly focused on understanding how early 3D engines worked internally, without using a full game engine.

If you are also a 42 student, use this repository only as a reference. The best way to learn `cub3D` is to understand the raycasting, parsing and rendering logic by yourself.

## Authors

- **Juan-AGN / juan-ant**
- **Luis Ángel Álvarez Gil / luialvar**

42 Málaga
