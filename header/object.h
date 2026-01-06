#ifndef OBJECT_H
#define OBJECT_H

#include "vector.h"
#include "matrix.h"

// Triangle face structure
typedef struct {
	int v0, v1, v2;  // Vertex indices
} Face;

// Mesh structure
typedef struct {
	Vector* vertices;
	int vertex_count;
	Face* faces;
	int face_count;
} Mesh;

// Mesh operations
Mesh* create_cube();
void mesh_transform(Mesh* mesh, Matrix4x4 transform);
void mesh_free(Mesh* mesh);

#endif
