#ifndef RENDER_H
#define RENDER_H

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 40

// Rendering functions
void clear_buffer();
void set_pixel(int x, int y, char c);
void draw_line(int x0, int y0, int x1, int y1);
void render_frame();

#endif
