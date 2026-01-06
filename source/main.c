#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "../header/vector.h"
#include "../header/matrix.h"
#include "../header/render.h"
#include "../header/object.h"

#define M_PI 3.14159265358979323846

int main(void) {
    printf("=== 3D ASCII Cube Renderer ===\n");
    printf("Starting animation...\n\n");
    
    // Small delay to let user read the message
    usleep(1000000);
    
    // Create cube mesh
    Mesh* cube = create_cube();
    
    // Setup projection matrix
    float fov = M_PI / 3.0f;  // 60 degrees
    float aspect = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
    float near = 0.1f;
    float far = 100.0f;
    Matrix4x4 projection = matrix_projection(fov, aspect, near, far);
    
    // Allocate array for projected vertices
    Vector* projected = (Vector*)malloc(sizeof(Vector) * cube->vertex_count);
    
    // Animation loop - 360 frames (6 seconds at 60fps)
    int total_frames = 360;
    for (int frame = 0; frame < total_frames; frame++) {
        // Clear the screen buffer
        clear_buffer();
        
        // Calculate rotation angles
        float angle_y = (frame * 2.0f * M_PI) / 180.0f; // Rotate around Y
        float angle_x = (frame * M_PI) / 180.0f;         // Rotate around X (slower)
        
        // Create transformation matrices
        Matrix4x4 rot_y = matrix_rotation_y(angle_y);
        Matrix4x4 rot_x = matrix_rotation_x(angle_x);
        Matrix4x4 rotation = matrix_multiply(rot_y, rot_x);
        
        // Move cube away from camera
        Matrix4x4 translation = matrix_translation(0.0f, 0.0f, 5.0f);
        
        // Combine transformations
        Matrix4x4 transform = matrix_multiply(translation, rotation);
        Matrix4x4 mvp = matrix_multiply(projection, transform);
        
        // Transform and project all vertices
        for (int i = 0; i < cube->vertex_count; i++) {
            projected[i] = matrix_multiply_vector(mvp, cube->vertices[i]);
        }
        
        // Draw the mesh
        draw_mesh(cube, projected);
        
        // Display frame number in top-left corner
        char frame_info[32];
        snprintf(frame_info, sizeof(frame_info), "Frame: %d/%d", frame + 1, total_frames);
        for (int i = 0; frame_info[i] != '\0' && i < SCREEN_WIDTH; i++) {
            set_pixel(i, 0, frame_info[i]);
        }
        
        // Render the frame
        render_frame();
        
        // Sleep for ~16ms (60 FPS)
        usleep(16666);
    }
    
    // Cleanup
    free(projected);
    free_mesh(cube);
    
    printf("\n=== Animation Complete! ===\n");
    
    return 0;
}

