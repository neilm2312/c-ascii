#ifndef RENDER_H
#define RENDER_H

#include "vector.h"

// Screen dimensions
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 40

// Renderer functions
void renderer_init();
void renderer_clear();
void renderer_set_pixel(int x, int y, float z, char c);
void renderer_draw_line(int x0, int y0, float z0, int x1, int y1, float z1, char c);
void renderer_draw_triangle(int x0, int y0, float z0, 
                           int x1, int y1, float z1,
                           int x2, int y2, float z2, char c);
void renderer_display();
void renderer_cleanup();

#endif
