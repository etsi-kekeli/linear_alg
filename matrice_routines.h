#ifndef MATRICE_ROUTINES_H
#define MATRICE_ROUTINES_H

#include <stdbool.h>

enum structures
{
    VECTOR,
    MATRIX
};

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

union data
{
    vector *v;
    matrix *m;
};

typedef struct node
{
    union data *d;
    struct node *next;
    enum structures s;
} node;

vector *vector_create(int size);

/*
 *Function to use to free the memory of a dynamically allocated memory
 *@param  v : A pointer of type vectors
 */
void vector_free(vector *v);

/*
 *Multiply a vector by a scalar
 *@params:
 *  v : A pointer of type vector
 *  scalar: a real number
 */
vector *vector_mul_scalar(const vector *v, double scalar);

/*
 *Print a vector on the terminal
 *@param  v : A vector
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
*@params:
*   m: integer - Number of lignes
    n: integer - Number of columns
    Returns a matrix of the specified size filled with zeros
*/

matrix *matrix_create(int m, int n);

/*
*Create a matrice of size mXn filled with the specified values
*@params:
*   m: integer - Number of lignes
    n: integer - Number of columns
    x: double - The value of all the elements of the resulting matrix
    Returns a matrix of the specified size filled with x
*/

matrix *matrix_create_filled_with(int m, int n, double x);

/*
 *Function to use to free the memory of a dynamically allocated memory to a matrix
 *@param  v : A pointer of type vectors
 */
void matrix_free(matrix *m);

/*
 *Print a matrix on the terminal
 *@param  m : A matrix
 */
void matrix_print(const matrix *m);

/*
 *Function to add two matrices of the same size
 *@params:
 *  m1: matrix
 *  m2: matrix
 * Returns a matrix of the same size as m1 and m2
 */
matrix *matrix_add(matrix *m1, matrix *m2);

/*
 *Multiply a vector by a matrix
 *@params:
 *  m : A pointer of type matrix
 *  scalar: a real number
 */
matrix *matrix_mul_scalar(const matrix *m, double scalar);

/*
 *Function to multiply two matrices of the same size
 *@params:
 *  m1: matrix
 *  m2: matrix
 * Returns a matrix of the same size as m1 and m2
 */
matrix *matrix_mul(matrix *m1, matrix *m2);

/*
 *Compute the dot product two matrices
 *@params:
 *  m1: matrix
 *  m2: matrix
 * Returns a matrix of the same size as m1 and m2
 */
matrix *matrix_dot(const matrix *m1, const matrix *m2);

/*----------------------------------------------------------------------------*/
// The routines of this block are define to track allocated memory and free it.

// The head of the stack that will be used to track dynamically allocated vectors or matrixes
node *head;

/*
 * Routine for initializing the tracking
 */
void matrix_routines_init();

/*
 * Add a matrix to the stack. It actually embbeds it inside of a structure that is pushed into the stack
 * @params :
 * m the address of the matrix
 * Returns true if the matrix was successfully pushed on top of the stack and false otherwise.
 */
bool push_matrix(matrix *m);

/*
 * Add a vector to the stack. It actually embbeds it inside of a structure that is pushed into the stack
 * @params :
 * v the address of the vector
 * Returns true if the vector was successfully pushed on top of the stack and false otherwise.
 */
bool push_vector(vector *v);

/*
 * Remove the head of the stack and free all the memory that is allocated to it recursively
 */
void pop();

/*
 * Free all the memory allocated by the creation of a vector and a matrix since the call of
 * matrix_routines_int() and all the structures allocated to support the tracking
 *
 */
void matrix_routines_end();
void print_structures();

#endif