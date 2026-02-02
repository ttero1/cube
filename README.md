# cub3D

A 42-school project that implements a simple raycasting engine to render a
pseudo-3D view of a 2D map. The goal is to explore how classic first-person
engines work by tracing rays against grid-based walls and drawing textured
columns.

## Features

- Real-time raycasting renderer.
- Textured walls with color/texture parsing from a `.cub` file.
- Basic movement, strafing, and rotation controls.
- Minimap overlay for navigation.

## Requirements

- `cc` (or `clang`/`gcc`)
- `cmake`
- `make`
- GLFW dependencies required by MLX42 (varies by OS)

## Build

```bash
make
```

The build compiles `libft` and MLX42 automatically and produces the `cub3D`
executable.

## Run

```bash
./cub3D test.cub
```

Replace `test.cub` with your own map file.

## Controls

- **W / A / S / D**: Move forward / strafe left / backward / strafe right
- **Left / Right Arrow**: Rotate view
- **Mouse movement**: Rotate view
- **Esc**: Quit

## Map files (.cub)

A `.cub` file provides:

- Texture paths for each wall direction (N/S/E/W)
- Floor and ceiling colors
- A 2D map layout using `1` (wall), `0` (empty space), and a player start
  position marked by `N`, `S`, `E`, or `W`

See `test.cub` for a working example.

## Project Structure

- `main.c` and `init_*`: initialization and game setup
- `parse_*`: parsing and validation of `.cub` files
- `movement.c`, `hooks.c`: input handling and player movement
- `draw_*`, `calculate*`, `texture.c`: raycasting and rendering utilities

## Cleaning

```bash
make fclean
```

## Notes

This project uses MLX42 and libft, which are included as subdirectories.
