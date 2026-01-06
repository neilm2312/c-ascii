#ifndef OBJECT_H
#define OBJECT_H

#include "vector.h"

typedef struct {
	int v0, v1; // Vertex indices
} Edge;

typedef struct {
	Vector* vertices;
	int vertex_count;
	Edge* edges;
	int edge_count;
} Mesh;

// Object functions
Mesh* create_cube();
void free_mesh(Mesh* mesh);
void draw_mesh(Mesh* mesh, Vector* projected);

#endif
