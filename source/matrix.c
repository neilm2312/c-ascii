#include "../header/matrix.h"
#include <math.h>
#include <string.h>

// Create identity matrix
Matrix4x4 matrix_identity() {
    Matrix4x4 result;
    memset(&result, 0, sizeof(Matrix4x4));
    result.m[0][0] = 1.0f;
    result.m[1][1] = 1.0f;
    result.m[2][2] = 1.0f;
    result.m[3][3] = 1.0f;
    return result;
}

// Multiply two 4x4 matrices
Matrix4x4 matrix_multiply(Matrix4x4 a, Matrix4x4 b) {
    Matrix4x4 result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.m[i][j] = 0.0f;
            for (int k = 0; k < 4; k++) {
                result.m[i][j] += a.m[i][k] * b.m[k][j];
            }
        }
    }
    return result;
}

// Create translation matrix
Matrix4x4 matrix_translation(float x, float y, float z) {
    Matrix4x4 result = matrix_identity();
    result.m[0][3] = x;
    result.m[1][3] = y;
    result.m[2][3] = z;
    return result;
}

// Create rotation matrix around X axis
Matrix4x4 matrix_rotation_x(float angle) {
    Matrix4x4 result = matrix_identity();
    float c = cosf(angle);
    float s = sinf(angle);
    result.m[1][1] = c;
    result.m[1][2] = -s;
    result.m[2][1] = s;
    result.m[2][2] = c;
    return result;
}

// Create rotation matrix around Y axis
Matrix4x4 matrix_rotation_y(float angle) {
    Matrix4x4 result = matrix_identity();
    float c = cosf(angle);
    float s = sinf(angle);
    result.m[0][0] = c;
    result.m[0][2] = s;
    result.m[2][0] = -s;
    result.m[2][2] = c;
    return result;
}

// Create rotation matrix around Z axis
Matrix4x4 matrix_rotation_z(float angle) {
    Matrix4x4 result = matrix_identity();
    float c = cosf(angle);
    float s = sinf(angle);
    result.m[0][0] = c;
    result.m[0][1] = -s;
    result.m[1][0] = s;
    result.m[1][1] = c;
    return result;
}

// Create perspective projection matrix
Matrix4x4 matrix_projection(float fov, float aspect, float near, float far) {
    Matrix4x4 result;
    memset(&result, 0, sizeof(Matrix4x4));
    
    float tan_half_fov = tanf(fov / 2.0f);
    
    result.m[0][0] = 1.0f / (aspect * tan_half_fov);
    result.m[1][1] = 1.0f / tan_half_fov;
    result.m[2][2] = -(far + near) / (far - near);
    result.m[2][3] = -(2.0f * far * near) / (far - near);
    result.m[3][2] = -1.0f;
    
    return result;
}

// Transform a vector by a matrix
Vector matrix_multiply_vector(Matrix4x4 m, Vector v) {
    float x = v.x * m.m[0][0] + v.y * m.m[0][1] + v.z * m.m[0][2] + m.m[0][3];
    float y = v.x * m.m[1][0] + v.y * m.m[1][1] + v.z * m.m[1][2] + m.m[1][3];
    float z = v.x * m.m[2][0] + v.y * m.m[2][1] + v.z * m.m[2][2] + m.m[2][3];
    float w = v.x * m.m[3][0] + v.y * m.m[3][1] + v.z * m.m[3][2] + m.m[3][3];
    
    // Perspective divide
    if (w != 0.0f) {
        x /= w;
        y /= w;
        z /= w;
    }
    
    return vector_create(x, y, z);
}
