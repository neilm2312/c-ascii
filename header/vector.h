#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
    float x, y, z;
} Vector;

// Vector operations
Vector vector_create(float x, float y, float z);
Vector add_vector(Vector a, Vector b);
Vector subtract_vector(Vector a, Vector b);
Vector multiply_vector(Vector v, float scalar);
float dot_vector(Vector a, Vector b);
Vector cross_vector(Vector a, Vector b);
float length(Vector v);
Vector normalize_vector(Vector v);
void print_vector(Vector v);

#endif

