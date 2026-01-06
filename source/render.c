#include "../header/render.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static char screen_buffer[SCREEN_HEIGHT][SCREEN_WIDTH];
static float depth_buffer[SCREEN_HEIGHT][SCREEN_WIDTH];

// Clear the screen buffer
void clear_buffer() {
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            screen_buffer[y][x] = ' ';
            depth_buffer[y][x] = 1000.0f; // Far away
        }
    }
}

// Set a pixel in the screen buffer
void set_pixel(int x, int y, char c) {
    if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
        screen_buffer[y][x] = c;
    }
}

// Bresenham's line drawing algorithm
void draw_line(int x0, int y0, int x1, int y1) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;
    
    char line_char = '#';
    
    while (1) {
        set_pixel(x0, y0, line_char);
        
        if (x0 == x1 && y0 == y1) break;
        
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

// Render the frame to terminal
void render_frame() {
    // Clear screen and move cursor to home
    printf("\033[2J\033[H");
    
    // Print the buffer
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            putchar(screen_buffer[y][x]);
        }
        putchar('\n');
    }
    
    fflush(stdout);
}
