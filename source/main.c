#include "../header/vector.h"
#include "../header/matrix.h"
#include "../header/render.h"
#include "../header/object.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

#define PI 3.14159265359f
#define NUM_FRAMES 300

// Helper function to copy mesh
Mesh* mesh_copy(Mesh* original) {
if (!original) return NULL;

Mesh* copy = (Mesh*)malloc(sizeof(Mesh));
if (!copy) return NULL;

copy->vertex_count = original->vertex_count;
copy->vertices = (Vector*)malloc(sizeof(Vector) * copy->vertex_count);

if (!copy->vertices) {
free(copy);
return NULL;
}

for (int i = 0; i < copy->vertex_count; i++) {
copy->vertices[i] = original->vertices[i];
}

copy->face_count = original->face_count;
copy->faces = (Face*)malloc(sizeof(Face) * copy->face_count);

if (!copy->faces) {
free(copy->vertices);
free(copy);
return NULL;
}

for (int i = 0; i < copy->face_count; i++) {
copy->faces[i] = original->faces[i];
}

return copy;
}

int main() {
// Initialize renderer
renderer_init();

// Create cube mesh
Mesh* cube_original = create_cube();
if (!cube_original) {
fprintf(stderr, "Failed to create cube\n");
return 1;
}

// Set up projection parameters
float fov = PI / 3.0f;  // 60 degrees
float aspect = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
float near = 0.1f;
float far = 100.0f;

Matrix4x4 projection = matrix_projection(fov, aspect, near, far);

// Animation loop
float angle = 0.0f;

for (int frame = 0; frame < NUM_FRAMES; frame++) {
// Clear the renderer
renderer_clear();

// Create a copy of the cube to transform
Mesh* cube = mesh_copy(cube_original);
if (!cube) {
fprintf(stderr, "Failed to copy cube\n");
break;
}

// Update rotation angle
angle = (float)frame * 0.05f;

// Create rotation matrices
Matrix4x4 rot_x = matrix_rotation_x(angle * 0.7f);
Matrix4x4 rot_y = matrix_rotation_y(angle);
Matrix4x4 rot_z = matrix_rotation_z(angle * 0.5f);

// Combine rotations
Matrix4x4 rotation = matrix_multiply(rot_x, rot_y);
rotation = matrix_multiply(rotation, rot_z);

// Scale the cube
Matrix4x4 scale = matrix_scaling(2.0f, 2.0f, 2.0f);

// Translation to move cube away from camera
Matrix4x4 translation = matrix_translation(0.0f, 0.0f, -5.0f);

// Combine transformations: scale -> rotate -> translate
Matrix4x4 transform = matrix_multiply(scale, rotation);
transform = matrix_multiply(transform, translation);

// Apply transformations to cube
mesh_transform(cube, transform);

// Render each triangle
for (int i = 0; i < cube->face_count; i++) {
Face face = cube->faces[i];
Vector v0 = cube->vertices[face.v0];
Vector v1 = cube->vertices[face.v1];
Vector v2 = cube->vertices[face.v2];

// Apply projection
Vector p0 = matrix_multiply_vector(projection, v0);
Vector p1 = matrix_multiply_vector(projection, v1);
Vector p2 = matrix_multiply_vector(projection, v2);

// Convert to screen coordinates
int x0 = (int)((p0.x + 1.0f) * 0.5f * SCREEN_WIDTH);
int y0 = (int)((1.0f - p0.y) * 0.5f * SCREEN_HEIGHT);

int x1 = (int)((p1.x + 1.0f) * 0.5f * SCREEN_WIDTH);
int y1 = (int)((1.0f - p1.y) * 0.5f * SCREEN_HEIGHT);

int x2 = (int)((p2.x + 1.0f) * 0.5f * SCREEN_WIDTH);
int y2 = (int)((1.0f - p2.y) * 0.5f * SCREEN_HEIGHT);

// Calculate face normal for backface culling
Vector edge1 = subtract_vector(v1, v0);
Vector edge2 = subtract_vector(v2, v0);
Vector normal = cross_vector(edge1, edge2);

// View direction (camera looks towards negative Z)
Vector view_dir = create_vector(0.0f, 0.0f, -1.0f);

// Only draw front-facing triangles
float dot = dot_vector(normal, view_dir);
if (dot < 0.0f) {
// Choose character based on depth
float avg_z = (p0.z + p1.z + p2.z) / 3.0f;
char c = '#';

if (avg_z < -0.3f) c = '@';
else if (avg_z < -0.1f) c = '%';
else if (avg_z < 0.1f) c = '#';
else if (avg_z < 0.3f) c = '*';
else if (avg_z < 0.5f) c = '+';
else if (avg_z < 0.7f) c = '=';
else c = '-';

// Draw filled triangle
renderer_draw_triangle(x0, y0, p0.z,
                      x1, y1, p1.z,
                      x2, y2, p2.z, c);
}
}

// Display the frame
renderer_display();

// Free the transformed cube
mesh_free(cube);

// Frame delay (approximately 30 FPS)
usleep(33000);  // 33 milliseconds
}

// Cleanup
mesh_free(cube_original);
renderer_cleanup();

printf("\nAnimation complete!\n");

return 0;
}
