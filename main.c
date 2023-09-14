#include <stdio.h>
#include "matrince_routines.h"

int main(int argc, char *argv[])
{
    vector *v1 = vector_create(5);
    vector *v2 = vector_add_scalar(v1, 3.14);
    vector *v3 = vector_mul_scalar(v2, 2);
    double dot = vector_dot(v2, v3);
    vector_print(*v2);
    vector_print(*v3);
    fprintf(stdout, "The dot product of v2 and v3 is %lf\n", dot);

    vector_free(v1);
    vector_free(v2);
    vector_free(v3);

    matrix *m = matrix_create(3, 2);
    matrix_print(*m);
    matrix_free(m);
    return 0;
}