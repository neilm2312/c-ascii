#include "../header/object.h"
#include "../header/render.h"
#include <stdlib.h>

// Create a cube mesh centered at origin
Mesh* create_cube() {
    Mesh* mesh = (Mesh*)malloc(sizeof(Mesh));
    
    // Allocate 8 vertices for cube
    mesh->vertex_count = 8;
    mesh->vertices = (Vector*)malloc(sizeof(Vector) * 8);
    
    // Define cube vertices (centered at origin, size 2x2x2)
    mesh->vertices[0] = vector_create(-1.0f, -1.0f, -1.0f);
    mesh->vertices[1] = vector_create( 1.0f, -1.0f, -1.0f);
    mesh->vertices[2] = vector_create( 1.0f,  1.0f, -1.0f);
    mesh->vertices[3] = vector_create(-1.0f,  1.0f, -1.0f);
    mesh->vertices[4] = vector_create(-1.0f, -1.0f,  1.0f);
    mesh->vertices[5] = vector_create( 1.0f, -1.0f,  1.0f);
    mesh->vertices[6] = vector_create( 1.0f,  1.0f,  1.0f);
    mesh->vertices[7] = vector_create(-1.0f,  1.0f,  1.0f);
    
    // Allocate 12 edges for cube
    mesh->edge_count = 12;
    mesh->edges = (Edge*)malloc(sizeof(Edge) * 12);
    
    // Define edges (connecting vertices)
    // Bottom face
    mesh->edges[0]  = (Edge){0, 1};
    mesh->edges[1]  = (Edge){1, 2};
    mesh->edges[2]  = (Edge){2, 3};
    mesh->edges[3]  = (Edge){3, 0};
    // Top face
    mesh->edges[4]  = (Edge){4, 5};
    mesh->edges[5]  = (Edge){5, 6};
    mesh->edges[6]  = (Edge){6, 7};
    mesh->edges[7]  = (Edge){7, 4};
    // Vertical edges
    mesh->edges[8]  = (Edge){0, 4};
    mesh->edges[9]  = (Edge){1, 5};
    mesh->edges[10] = (Edge){2, 6};
    mesh->edges[11] = (Edge){3, 7};
    
    return mesh;
}

// Free mesh memory
void free_mesh(Mesh* mesh) {
    if (mesh) {
        if (mesh->vertices) free(mesh->vertices);
        if (mesh->edges) free(mesh->edges);
        free(mesh);
    }
}

// Draw mesh edges using projected vertices
void draw_mesh(Mesh* mesh, Vector* projected) {
    for (int i = 0; i < mesh->edge_count; i++) {
        Edge edge = mesh->edges[i];
        Vector v0 = projected[edge.v0];
        Vector v1 = projected[edge.v1];
        
        // Convert from normalized coordinates to screen coordinates
        int x0 = (int)((v0.x + 1.0f) * SCREEN_WIDTH / 2.0f);
        int y0 = (int)((v0.y + 1.0f) * SCREEN_HEIGHT / 2.0f);
        int x1 = (int)((v1.x + 1.0f) * SCREEN_WIDTH / 2.0f);
        int y1 = (int)((v1.y + 1.0f) * SCREEN_HEIGHT / 2.0f);
        
        draw_line(x0, y0, x1, y1);
    }
}
