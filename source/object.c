#include "../header/object.h"
#include <stdlib.h>
#include <stdio.h>

Mesh* create_cube() {
Mesh* mesh = (Mesh*)malloc(sizeof(Mesh));
if (!mesh) return NULL;

// A cube has 8 vertices
mesh->vertex_count = 8;
mesh->vertices = (Vector*)malloc(sizeof(Vector) * 8);

if (!mesh->vertices) {
free(mesh);
return NULL;
}

// Define cube vertices (centered at origin, size 1x1x1)
mesh->vertices[0] = create_vector(-0.5f, -0.5f, -0.5f);  // Back bottom left
mesh->vertices[1] = create_vector( 0.5f, -0.5f, -0.5f);  // Back bottom right
mesh->vertices[2] = create_vector( 0.5f,  0.5f, -0.5f);  // Back top right
mesh->vertices[3] = create_vector(-0.5f,  0.5f, -0.5f);  // Back top left
mesh->vertices[4] = create_vector(-0.5f, -0.5f,  0.5f);  // Front bottom left
mesh->vertices[5] = create_vector( 0.5f, -0.5f,  0.5f);  // Front bottom right
mesh->vertices[6] = create_vector( 0.5f,  0.5f,  0.5f);  // Front top right
mesh->vertices[7] = create_vector(-0.5f,  0.5f,  0.5f);  // Front top left

// A cube has 12 triangles (2 per face, 6 faces)
mesh->face_count = 12;
mesh->faces = (Face*)malloc(sizeof(Face) * 12);

if (!mesh->faces) {
free(mesh->vertices);
free(mesh);
return NULL;
}

// Define cube faces (triangles)
// Back face
mesh->faces[0] = (Face){0, 1, 2};
mesh->faces[1] = (Face){0, 2, 3};

// Front face
mesh->faces[2] = (Face){5, 4, 7};
mesh->faces[3] = (Face){5, 7, 6};

// Left face
mesh->faces[4] = (Face){4, 0, 3};
mesh->faces[5] = (Face){4, 3, 7};

// Right face
mesh->faces[6] = (Face){1, 5, 6};
mesh->faces[7] = (Face){1, 6, 2};

// Top face
mesh->faces[8] = (Face){3, 2, 6};
mesh->faces[9] = (Face){3, 6, 7};

// Bottom face
mesh->faces[10] = (Face){4, 5, 1};
mesh->faces[11] = (Face){4, 1, 0};

return mesh;
}

void mesh_transform(Mesh* mesh, Matrix4x4 transform) {
if (!mesh || !mesh->vertices) return;

for (int i = 0; i < mesh->vertex_count; i++) {
mesh->vertices[i] = matrix_multiply_vector(transform, mesh->vertices[i]);
}
}

void mesh_free(Mesh* mesh) {
if (!mesh) return;

if (mesh->vertices) {
free(mesh->vertices);
}
if (mesh->faces) {
free(mesh->faces);
}
free(mesh);
}
