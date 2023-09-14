#ifndef MATRICE_ROUTINES_H
#define MATRICE_ROUTINES_H

typedef struct vector
{
    double *tab;
    int size;
} vector;

typedef struct matrix
{
    vector **mat;
    int n;
} matrix;

vector *vector_create(int size);

/*
 *Function to use to free the memory of a dynamically allocated memory
 *@param  v : A pointer of type vectors
 */
void vector_free(vector *v);

/*
 *Multiply a vector by a scalar
 *@param  v : A pointer of type vectors
 */
vector *vector_mul_scalar(const vector *v, double scalar);

/*
 *Print a vector on the terminal
 *@param  v : A pointer of type vectors
 */
void vector_print(const vector *v);

/*
 *Add 2 vectors of same size
 *@param
 *v1 : A pointer of type vector
 *v2 : A pointer of type vector
 *returns : A vector of the same size or NULL if memory can't be allocated
 */

vector *vector_add(const vector *v1, const vector *v2);

/*
 *Add a vector and a scalar value.
 *the scalar is added to all the values of the vector
 *@param
 *v1 : A pointer of type vector
 *x : a scalar of type double
 *returns : A vector of the same size as v1 or NULL if memory can't be allocated
 */

vector *vector_add_scalar(const vector *v1, double x);

/*
 *Compute the dot product of 2 vectors of the same size
 *@param
 *v1 : A pointer of type vector
 *v2 : A pointer of type vector
 *returns : A vector of the same size or NULL if memory can't be allocated
 */

double vector_dot(const vector *v1, const vector *v2);

/*---------------------------------------------------------------------------------*/

/*
*Create a matrice of size mXn
*@param:
*   m: integer - Number of lignes
    n: integer - Number of columns
    Returns a matrix of the specified size
*/

matrix *matrix_create(int m, int n);

/*
 *Function to use to free the memory of a dynamically allocated memory to a matrix
 *@param  v : A pointer of type vectors
 */
void matrix_free(matrix *m);
#endif