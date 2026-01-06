#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"

typedef struct {
	float m[4][4];
} Matrix4x4;

// Matrix operations
Matrix4x4 matrix_identity();
Matrix4x4 matrix_multiply(Matrix4x4 a, Matrix4x4 b);
Matrix4x4 matrix_translation(float x, float y, float z);
Matrix4x4 matrix_rotation_x(float angle);
Matrix4x4 matrix_rotation_y(float angle);
Matrix4x4 matrix_rotation_z(float angle);
Matrix4x4 matrix_projection(float fov, float aspect, float near, float far);
Vector matrix_multiply_vector(Matrix4x4 m, Vector v);

#endif 
