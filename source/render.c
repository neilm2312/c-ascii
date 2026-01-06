#include "../header/render.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Frame buffer and depth buffer
static char frame_buffer[SCREEN_HEIGHT][SCREEN_WIDTH];
static float z_buffer[SCREEN_HEIGHT][SCREEN_WIDTH];

// ASCII shading characters (ordered from darkest to brightest)
static const char shading_chars[] = " .:-=+*#%@";
static const int num_shading_chars = 10;

void renderer_init() {
renderer_clear();
}

void renderer_clear() {
for (int y = 0; y < SCREEN_HEIGHT; y++) {
for (int x = 0; x < SCREEN_WIDTH; x++) {
frame_buffer[y][x] = ' ';
z_buffer[y][x] = 1e10f;  // Far away
}
}
}

void renderer_set_pixel(int x, int y, float z, char c) {
if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
return;
}

// Depth test
if (z < z_buffer[y][x]) {
frame_buffer[y][x] = c;
z_buffer[y][x] = z;
}
}

void renderer_draw_line(int x0, int y0, float z0, int x1, int y1, float z1, char c) {
// Bresenham's line algorithm with depth interpolation
int dx = abs(x1 - x0);
int dy = abs(y1 - y0);
int sx = (x0 < x1) ? 1 : -1;
int sy = (y0 < y1) ? 1 : -1;
int err = dx - dy;

int steps = (dx > dy) ? dx : dy;
if (steps == 0) steps = 1;

int x = x0, y = y0;

for (int i = 0; i <= steps; i++) {
float t = (steps > 0) ? (float)i / steps : 0.0f;
float z = z0 + t * (z1 - z0);

renderer_set_pixel(x, y, z, c);

if (x == x1 && y == y1) break;

int e2 = 2 * err;
if (e2 > -dy) {
err -= dy;
x += sx;
}
if (e2 < dx) {
err += dx;
y += sy;
}
}
}

// Helper function to swap values
static void swap_int(int* a, int* b) {
int temp = *a;
*a = *b;
*b = temp;
}

static void swap_float(float* a, float* b) {
float temp = *a;
*a = *b;
*b = temp;
}

void renderer_draw_triangle(int x0, int y0, float z0,
                           int x1, int y1, float z1,
                           int x2, int y2, float z2, char c) {
// Sort vertices by y-coordinate (y0 <= y1 <= y2)
if (y0 > y1) {
swap_int(&y0, &y1);
swap_int(&x0, &x1);
swap_float(&z0, &z1);
}
if (y0 > y2) {
swap_int(&y0, &y2);
swap_int(&x0, &x2);
swap_float(&z0, &z2);
}
if (y1 > y2) {
swap_int(&y1, &y2);
swap_int(&x1, &x2);
swap_float(&z1, &z2);
}

// Draw triangle using scanline approach
int total_height = y2 - y0;
if (total_height == 0) return;

for (int y = y0; y <= y2; y++) {
if (y < 0 || y >= SCREEN_HEIGHT) continue;

int second_half = (y > y1) || (y1 == y0);
int segment_height = second_half ? (y2 - y1) : (y1 - y0);
if (segment_height == 0) segment_height = 1;

float alpha = (float)(y - y0) / total_height;
float beta = (float)(y - (second_half ? y1 : y0)) / segment_height;

int xa = x0 + (int)((x2 - x0) * alpha);
int xb = second_half ? (x1 + (int)((x2 - x1) * beta)) : (x0 + (int)((x1 - x0) * beta));

float za = z0 + (z2 - z0) * alpha;
float zb = second_half ? (z1 + (z2 - z1) * beta) : (z0 + (z1 - z0) * beta);

if (xa > xb) {
swap_int(&xa, &xb);
swap_float(&za, &zb);
}

for (int x = xa; x <= xb; x++) {
if (x < 0 || x >= SCREEN_WIDTH) continue;

float t = (xb - xa) > 0 ? (float)(x - xa) / (xb - xa) : 0.0f;
float z = za + (zb - za) * t;

renderer_set_pixel(x, y, z, c);
}
}
}

void renderer_display() {
// Clear screen using ANSI escape codes
printf("\033[2J\033[H");

// Display frame buffer
for (int y = 0; y < SCREEN_HEIGHT; y++) {
for (int x = 0; x < SCREEN_WIDTH; x++) {
putchar(frame_buffer[y][x]);
}
putchar('\n');
}
fflush(stdout);
}

void renderer_cleanup() {
// Nothing to clean up in this simple implementation
}

// Helper function to get shading character based on depth
char get_shading_char(float depth) {
int index = (int)(depth * (num_shading_chars - 1));
if (index < 0) index = 0;
if (index >= num_shading_chars) index = num_shading_chars - 1;
return shading_chars[index];
}
