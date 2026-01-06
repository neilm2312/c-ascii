# 3D ASCII Art Renderer

A complete 3D graphics renderer that displays animated ASCII art in the terminal, featuring a rotating cube with full 3D transformations.

## Features

* **Full 3D Transformation Pipeline**: Rotation, scaling, and translation
* **Perspective Projection**: Realistic 3D-to-2D projection with field of view
* **Backface Culling**: Only renders visible triangle faces
* **Z-Buffer Depth Testing**: Proper depth ordering of rendered primitives
* **Triangle Rasterization**: Filled triangle rendering with scanline algorithm
* **ASCII Shading**: Dynamic character selection based on depth for visual effect
* **Smooth Animation**: 30 FPS animation loop with 300 frames

## Project Structure

```
c-ascii/
├── header/              # Header files
│   ├── vector.h        # 3D vector operations
│   ├── matrix.h        # 4x4 matrix operations
│   ├── render.h        # Rendering and frame buffer
│   └── object.h        # 3D mesh structures
├── source/              # Source files
│   ├── vector.c        # Vector math implementation
│   ├── matrix.c        # Matrix operations (transformations, projection)
│   ├── render.c        # ASCII renderer with z-buffer
│   ├── object.c        # Cube mesh creation
│   └── main.c          # Main animation loop
├── Makefile            # Build configuration
└── README.md           # This file
```

## Building

Compile the project using the provided Makefile:

```bash
make          # Compile the project
```

This will create the `ascii3d` executable.

## Running

Execute the animation:

```bash
./ascii3d
```

The program will:
1. Clear the terminal
2. Display a rotating 3D cube rendered in ASCII characters
3. Animate for 300 frames (~10 seconds at 30 FPS)
4. Exit cleanly

## Cleaning

Remove build artifacts:

```bash
make clean
```

## Technical Details

### Graphics Pipeline

1. **Model Space**: Cube defined with 8 vertices and 12 triangular faces
2. **World Transform**: Apply rotation around X, Y, and Z axes simultaneously
3. **View Transform**: Translate cube away from camera (positioned at z=-5)
4. **Projection**: Perspective projection matrix (60° FOV)
5. **Screen Space**: Convert normalized device coordinates to 80x40 character grid
6. **Rasterization**: Fill triangles with ASCII characters
7. **Display**: Output frame buffer to terminal

### Rendering Features

* **Screen Resolution**: 80 columns × 40 rows
* **Frame Buffer**: 2D character array
* **Z-Buffer**: Per-pixel depth testing for correct occlusion
* **Shading Characters**: ` .:-=+*#%@` (ordered by depth/brightness)
* **Backface Culling**: Uses dot product of face normal with view direction

### Mathematics

* **Vectors**: 3D vectors with operations (add, subtract, multiply, dot, cross, normalize)
* **Matrices**: 4×4 homogeneous transformation matrices
* **Rotations**: Individual rotation matrices for X, Y, and Z axes
* **Projection**: Perspective projection with near/far clipping planes

## Requirements

* GCC compiler
* Math library (`-lm`)
* POSIX-compliant system (for `usleep`)
* Terminal with ANSI escape code support

## Code Quality

* Proper header guards in all header files
* Memory management with allocation and deallocation
* Edge case handling (division by zero, null pointers)
* Commented algorithms for clarity
* Modular design with separation of concerns

## Author

Created as a demonstration of 3D graphics fundamentals and ASCII art rendering.
