#include "../header/vector.h"
#include <math.h>
#include <stdio.h>

Vector vector(float x, float y, float z){
	Vector v = {x, y, z};
	return v;
}

Vector add_vector(Vector a, Vector b){
	return vector(
		a.x + b.x,
		a.y + b.y,
		a.z + b.z);	
}

Vector subtract_vector(Vector a, Vector b){
	return vector(
		a.x - b.x,
		a.y - b.y,
		a.z - b.z);
}
	
Vector multiply_vector(Vector v, float scalar) {
	return vector(
		v.x * scalar,
		v.y * scalar,
		v.z * scalar) 
}

float dot_vector(Vector a, Vector b){
	return vector(
		a.x * b.x +
		a.y * b.y +
		a.z * b.z)
}

Vector cross_vector(Vector a, Vector b){
	return vector(
		a.y * b.z - a.z * b.y,
       		a.z * b.x - a.x * b.z,
        	a.x * b.y - a.y * b.x)
}

float length(Vector v){
	return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vector normalize_vector(Vector v){
	float len = length(v);
	if (len > 0.0f) {
		return (multiply_vector(v, 1.0f / len));
	}
	return v
}

void print_vector(Vector v) {
	printf("Vector(%.2f, %.2f, %.2f)\n", v.x, v.y, v.z);
}
	
