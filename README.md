# C-ASCII 3D Renderer

A lightweight 3D ASCII art renderer written in C that displays a rotating cube in your terminal.

## Features

- **3D Vector Mathematics**: Complete vector operations (add, subtract, multiply, dot, cross, normalize)
- **4x4 Matrix Transformations**: Identity, translation, rotation (X/Y/Z axes), and perspective projection
- **ASCII Rendering Engine**: 80x40 character buffer with Bresenham line drawing
- **3D Mesh System**: Vertex and edge data structures for defining 3D objects
- **Smooth Animation**: 60 FPS rotating cube with real-time frame counter

## Demo

```
Frame: 180/360                                                                    
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                               ##################                               
                               ##              ##                               
                               # #            # #                               
                               #  ############  #                               
                               #  #          #  #                               
                               #  #          #  #                               
                               #  #          #  #                               
                               #  #          #  #                               
                               #  #          #  #                               
                               #  #          #  #                               
                               #  #          #  #                               
                               #  #          #  #                               
                               #  ############  #                               
                               # #            # #                               
                               ##              ##                               
                               ##################                               
                                                                                
                                                                                
                                                                                
```

## Building

Requires GCC and make:

```bash
make
```

This compiles all source files and links them with the math library (`-lm`) to create the `ascii3d` executable.

## Running

Execute the compiled program:

```bash
./ascii3d
```

The program will display a rotating 3D cube for 360 frames (approximately 6 seconds) and then exit cleanly.

## Project Structure

```
c-ascii/
├── header/
│   ├── vector.h      # 3D vector operations
│   ├── matrix.h      # 4x4 matrix transformations
│   ├── render.h      # Screen buffer and drawing functions
│   └── object.h      # 3D mesh data structures
├── source/
│   ├── vector.c      # Vector implementation
│   ├── matrix.c      # Matrix implementation
│   ├── render.c      # Rendering implementation
│   ├── object.c      # 3D object implementation
│   └── main.c        # Main animation loop
├── Makefile          # Build configuration
└── README.md         # This file
```

## Technical Details

### Rendering Approach

- **Screen Buffer**: 80x40 character array representing the terminal display
- **Line Drawing**: Bresenham's algorithm for efficient line rasterization
- **3D Pipeline**: Vertex transformation → Matrix multiplication → Perspective projection → Screen mapping
- **Terminal Control**: ANSI escape sequences (`\033[2J\033[H`) for screen clearing

### Transformations

The renderer applies the following transformation pipeline:

1. **Model Transform**: Rotation matrices combine X and Y axis rotations
2. **View Transform**: Translation matrix moves the cube away from camera (Z=5)
3. **Projection**: Perspective projection with 60° FOV maps 3D to 2D
4. **Screen Mapping**: Normalized coordinates convert to screen space (0-79, 0-39)

### Terminal Requirements

- Supports ANSI escape sequences (most modern terminals)
- Minimum size: 80x40 characters recommended
- Works best with monospace fonts

## Cleanup

Remove compiled files:

```bash
make clean
```

## Future Improvements

- [ ] Add multiple 3D shapes (pyramid, sphere, torus)
- [ ] Implement depth-based shading with gradient characters (` .:-=+*#%@`)
- [ ] Add user controls (keyboard input for rotation speed/direction)
- [ ] Support dynamic terminal resizing
- [ ] Implement backface culling for performance
- [ ] Add lighting and simple shading models
- [ ] Create scene graph for multiple objects
- [ ] Export animation frames to file

## License

This project is provided as-is for educational purposes.
