#include "../header/matrix.h"
#include <math.h>
#include <stdio.h>

Matrix4x4 matrix_identity() {
Matrix4x4 m;
for (int i = 0; i < 4; i++) {
for (int j = 0; j < 4; j++) {
m.m[i][j] = (i == j) ? 1.0f : 0.0f;
}
}
return m;
}

Matrix4x4 matrix_zero() {
Matrix4x4 m;
for (int i = 0; i < 4; i++) {
for (int j = 0; j < 4; j++) {
m.m[i][j] = 0.0f;
}
}
return m;
}

Matrix4x4 matrix_multiply(Matrix4x4 a, Matrix4x4 b) {
Matrix4x4 result = matrix_zero();
for (int i = 0; i < 4; i++) {
for (int j = 0; j < 4; j++) {
for (int k = 0; k < 4; k++) {
result.m[i][j] += a.m[i][k] * b.m[k][j];
}
}
}
return result;
}

Vector matrix_multiply_vector(Matrix4x4 m, Vector v) {
float x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z + m.m[0][3];
float y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z + m.m[1][3];
float z = m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z + m.m[2][3];
float w = m.m[3][0] * v.x + m.m[3][1] * v.y + m.m[3][2] * v.z + m.m[3][3];

// Perspective divide
if (w != 0.0f) {
x /= w;
y /= w;
z /= w;
}

return create_vector(x, y, z);
}

Matrix4x4 matrix_rotation_x(float angle) {
Matrix4x4 m = matrix_identity();
float c = cosf(angle);
float s = sinf(angle);

m.m[1][1] = c;
m.m[1][2] = -s;
m.m[2][1] = s;
m.m[2][2] = c;

return m;
}

Matrix4x4 matrix_rotation_y(float angle) {
Matrix4x4 m = matrix_identity();
float c = cosf(angle);
float s = sinf(angle);

m.m[0][0] = c;
m.m[0][2] = s;
m.m[2][0] = -s;
m.m[2][2] = c;

return m;
}

Matrix4x4 matrix_rotation_z(float angle) {
Matrix4x4 m = matrix_identity();
float c = cosf(angle);
float s = sinf(angle);

m.m[0][0] = c;
m.m[0][1] = -s;
m.m[1][0] = s;
m.m[1][1] = c;

return m;
}

Matrix4x4 matrix_translation(float x, float y, float z) {
Matrix4x4 m = matrix_identity();
m.m[0][3] = x;
m.m[1][3] = y;
m.m[2][3] = z;
return m;
}

Matrix4x4 matrix_scaling(float x, float y, float z) {
Matrix4x4 m = matrix_identity();
m.m[0][0] = x;
m.m[1][1] = y;
m.m[2][2] = z;
return m;
}

Matrix4x4 matrix_projection(float fov, float aspect, float near, float far) {
Matrix4x4 m = matrix_zero();
float tan_half_fov = tanf(fov / 2.0f);

m.m[0][0] = 1.0f / (aspect * tan_half_fov);
m.m[1][1] = 1.0f / tan_half_fov;
m.m[2][2] = -(far + near) / (far - near);
m.m[2][3] = -(2.0f * far * near) / (far - near);
m.m[3][2] = -1.0f;

return m;
}

void matrix_print(Matrix4x4 m) {
printf("Matrix4x4:\n");
for (int i = 0; i < 4; i++) {
printf("[");
for (int j = 0; j < 4; j++) {
printf(" %7.3f", m.m[i][j]);
}
printf(" ]\n");
}
}
