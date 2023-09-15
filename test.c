#include <stdio.h>
#include "matrice_routines.h"

int main(int argc, char *argv[])
{
    matrix_routines_init();
    vector *v1 = vector_create(5);
    vector *v2 = vector_add_scalar(v1, 3.14);
    vector *v3 = vector_mul_scalar(v2, 2);
    double dot = vector_dot(v2, v3);
    // vector_print(v2);
    // vector_print(v3);
    fprintf(stdout, "The dot product of v2 and v3 is %lf\n", dot);

    // vector_free(v1);
    // vector_free(v2);
    // vector_free(v3);

    matrix *m1 = matrix_create_filled_with(3, 2, 1.9);
    matrix *m2 = matrix_create_filled_with(2, 2, 0.4);
    matrix *m = matrix_dot(m1, m2);
    matrix *menos_m = matrix_mul_scalar(m, -0.4);
    // matrix_print(m);
    // matrix_print(menos_m);

    // matrix_free(m1);
    // matrix_free(m2);
    // matrix_free(m);
    // matrix_free(menos_m);
    print_structures();
    matrix_routines_end();
    return 0;
}