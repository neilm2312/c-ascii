#include <stdio.h>
#include "../header/vector.h"

int main(void) {
    printf("=== Vector Math Test ===\n\n");
    
    // Create vectors
    Vector v1 = vector_create(1.0f, 2.0f, 3.0f);
    Vector v2 = vector_create(4.0f, 5.0f, 6.0f);
    
    printf("Vector 1: ");
    print_vector(v1);
    
    printf("Vector 2: ");
    print_vector(v2);
    
    // Test add
    printf("\nAdd: ");
    Vector result_add = add_vector(v1, v2);
    print_vector(result_add);
    
    // Test subtract
    printf("Subtract: ");
    Vector result_sub = subtract_vector(v1, v2);
    print_vector(result_sub);
    
    // Test multiply
    printf("Multiply v1 by 2.0: ");
    Vector result_mul = multiply_vector(v1, 2.0f);
    print_vector(result_mul);
    
    // Test dot product
    float dot = dot_vector(v1, v2);
    printf("Dot product: %.2f\n", dot);
    
    // Test cross product
    printf("Cross product: ");
    Vector result_cross = cross_vector(v1, v2);
    print_vector(result_cross);
    
    // Test length
    float len = length(v1);
    printf("Length of v1: %.2f\n", len);
    
    // Test normalize
    printf("Normalized v1: ");
    Vector result_norm = normalize_vector(v1);
    print_vector(result_norm);
    printf("Length of normalized v1: %.2f\n", length(result_norm));
    
    printf("\n=== All vector operations working! ===\n");
    
    return 0;
}
