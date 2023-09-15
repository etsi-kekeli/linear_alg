#include "matrice_routines.h"

#include <stdio.h>
#include <stdlib.h>

void mem_al_fail()
{
    perror("Vector creation unsuccessful");
}

bool is_null_vec(const vector *v)
{
    if (v == NULL)
        return true;
    return false;
}

bool is_valid_matrix(const matrix *m)
{
    if (m != NULL)
    {
        if (m->mat != NULL)
        {
            for (int i = 0; i < m->n; i++)
            {
                if (m->mat[i]->tab == NULL)
                {
                    return false;
                    printf("A tab fail\n");
                }
            }
            return true;
        }
        else
            printf("mat is not nul\n");
    }
    return false;
}

bool is_valid_vec(const vector *v)
{
    return !is_null_vec(v) && v->tab != NULL && v->size != 0;
}

bool is_same_size(matrix *m1, matrix *m2)
{
    return is_valid_matrix(m1) &&
           is_valid_matrix(m2) &&
           m1->n == m2->n &&
           m1->mat[0]->size == m2->mat[0]->size;
}

vector *vector_create(int size)
{
    if (size > 0)
    {
        double *vect = (double *)calloc(size, sizeof(double));
        if (vect != NULL)
        {
            vector *v = (vector *)malloc(sizeof(vector));
            if (v != NULL)
            {
                v->tab = vect;
                v->size = size;
                if (!push_vector(v))
                {
                    vector_free(v);
                }

                return v;
            }
            free(vect);
            vect = NULL;
        }
    }
    mem_al_fail();
    return (vector *)NULL;
}

void vector_free(vector *v)
{
    if (v != NULL)
    {
        if (v->tab != NULL)
        {
            free(v->tab);
            v->tab = NULL;
            v->size = 0;
        }
        free(v);
        v = NULL;
    }
}

void vector_print(const vector *v)
{
    if (is_valid_vec(v))
    {
        for (int i = 0; i < v->size; i++)
            fprintf(stdout, "%.4lf\t", v->tab[i]);
        fprintf(stdout, "\n");
    }
    else
        fprintf(stdout, "Null pointer\n");
}

vector *vector_mul_scalar(const vector *v, double scalar)
{
    if (v == NULL || v->size == 0)
        return (vector *)NULL;
    vector *ans = vector_create(v->size);

    if (ans == NULL)
    {
        mem_al_fail();
        return (vector *)NULL;
    }

    for (int i = 0; i < v->size; i++)
    {
        ans->tab[i] = scalar * v->tab[i];
    }
    return ans;
}

vector *vector_add(const vector *v1, const vector *v2)
{
    if (v1 == NULL || v2 == NULL)
    {
        fprintf(stderr, "Invalid parameter: null pointer is passed\n");
        return (vector *)NULL;
    }

    if (v1->size != v2->size)
    {
        fprintf(stderr, "Invalid parameters: vectors must have the same size\n");
        return (vector *)NULL;
    }

    vector *ans = vector_create(v1->size);
    if (ans == NULL)
    {
        mem_al_fail();
        return (vector *)NULL;
    }

    for (int i = 0; i < v1->size; i++)
    {
        ans->tab[i] = v1->tab[i] + v2->tab[i];
    }

    return ans;
}

vector *vector_add_scalar(const vector *v1, double x)
{
    if (!is_valid_vec(v1))
    {
        fprintf(stderr, "Invalid parameter: null pointer is passed\n");
        return (vector *)NULL;
    }

    vector *ans = vector_create(v1->size);
    if (is_null_vec(ans))
    {
        mem_al_fail();
        return (vector *)NULL;
    }

    for (int i = 0; i < v1->size; i++)
    {
        ans->tab[i] = v1->tab[i] + x;
    }
    return ans;
}

double vector_dot(const vector *v1, const vector *v2)
{
    if (is_valid_vec(v1) && is_valid_vec(v2))
    {
        if (v1->size != v2->size)
        {
            fprintf(stderr, "Invalid parameters: vectors must have the same size\n");
            return __DBL_MAX__;
        }
        double ans = 0;
        for (int i = 0; i < v1->size; i++)
        {
            ans += v1->tab[i] * v2->tab[i];
        }
        return ans;
    }
    fprintf(stderr, "Invalid parameters: vectors must not be null\n");
    return __DBL_MAX__;
}

matrix *matrix_create(int m, int n)
{
    if (m <= 0 || n <= 0)
    {
        fprintf(stderr, "Invalid size: parameters must be positive integers");
        return (matrix *)NULL;
    }

    matrix *ans = (matrix *)malloc(sizeof(matrix));
    if (ans == NULL)
    {
        mem_al_fail();
        return (matrix *)NULL;
    }

    ans->mat = (vector **)calloc(n, sizeof(vector *));
    ans->n = n;

    if (ans->mat == NULL)
    {
        mem_al_fail();
        free(ans);
        return (matrix *)NULL;
    }

    for (int i = 0; i < n; i++)
    {
        ans->mat[i] = vector_create(m);
        if (is_null_vec(ans->mat[i]))
        {
            mem_al_fail();
            matrix_free(ans);
            return (matrix *)NULL;
        }
    }

    if (!push_matrix(ans))
    {
        matrix_free(ans);
    }
    return ans;
}

matrix *matrix_create_filled_with(int m, int n, double x)
{
    matrix *ans = matrix_create(m, n);
    if (is_valid_matrix(ans))
    {
        for (int i = 0; i < ans->mat[0]->size; i++)
        {
            for (int j = 0; j < ans->n; j++)
            {
                ans->mat[j]->tab[i] = x;
            }
        }
    }
    return ans;
}

void matrix_free(matrix *m)
{
    if (m != NULL)
    {
        if (m->mat != NULL)
        {
            for (int i = 0; i < m->n; i++)
            {
                if (m->mat[i])
                {
                    vector_free(m->mat[i]);
                }
            }
            free(m->mat);
            m->mat = NULL;
        }
        free(m);
        m = (matrix *)NULL;
    }
}

void matrix_print(const matrix *m)
{
    if (is_valid_matrix(m))
    {
        for (int i = 0; i < m->mat[0]->size; i++)
        {
            for (int j = 0; j < m->n; j++)
            {
                fprintf(stdout, "%.4lf\t", m->mat[j]->tab[i]);
            }
            fprintf(stdout, "\n");
        }
    }
    else
    {
        fprintf(stderr, "Invalid matrix\n");
    }
}

matrix *matrix_add(matrix *m1, matrix *m2)
{
    if (!is_valid_matrix(m1) || !is_valid_matrix(m2))
    {
        fprintf(stderr, "Invalid parameter: invalid matrix\n");
        return (matrix *)NULL;
    }
    if (!is_same_size(m1, m2))
    {
        fprintf(stderr, "Invalid parameters: matrixes must be of the same size\n");
        return (matrix *)NULL;
    }

    matrix *ans = matrix_create(m1->mat[0]->size, m1->n);
    if (ans == NULL)
    {
        mem_al_fail();
        return (matrix *)NULL;
    }

    for (int i = 0; i < m1->mat[0]->size; i++)
    {
        for (int j = 0; j < m1->n; j++)
        {
            ans->mat[j]->tab[i] = m1->mat[j]->tab[i] + m2->mat[j]->tab[i];
        }
    }

    return ans;
}

matrix *matrix_mul_scalar(const matrix *m, double scalar)
{
    if (!is_valid_matrix(m))
    {
        fprintf(stderr, "Invalid matrix : Matrix is or contains null pointer\n");
        return (matrix *)NULL;
    }

    matrix *ans = matrix_create(m->mat[0]->size, m->n);
    if (ans == NULL)
    {
        mem_al_fail();
        return ans;
    }

    for (int i = 0; i < ans->mat[0]->size; i++)
    {
        for (int j = 0; j < ans->n; j++)
        {
            ans->mat[j]->tab[i] = m->mat[j]->tab[i] * scalar;
        }
    }

    return ans;
}

matrix *matrix_mul(matrix *m1, matrix *m2)
{
    if (!is_valid_matrix(m1) || !is_valid_matrix(m2))
    {
        fprintf(stderr, "Invalid parameter: invalid matrix\n");
        return (matrix *)NULL;
    }
    if (!is_same_size(m1, m2))
    {
        fprintf(stderr, "Invalid parameters: matrixes must be of the same size\n");
        return (matrix *)NULL;
    }

    matrix *ans = matrix_create(m1->mat[0]->size, m1->n);
    if (ans == NULL)
    {
        mem_al_fail();
        return (matrix *)NULL;
    }

    for (int i = 0; i < m1->mat[0]->size; i++)
    {
        for (int j = 0; j < m1->n; j++)
        {
            ans->mat[j]->tab[i] = m1->mat[j]->tab[i] * m2->mat[j]->tab[i];
        }
    }

    return ans;
}

matrix *matrix_dot(const matrix *m1, const matrix *m2)
{
    if (!is_valid_matrix(m1) || !is_valid_matrix(m2))
    {
        fprintf(stderr, "Invalid parameter: invalid matrix\n");
        return (matrix *)NULL;
    }

    if (m1->n != m2->mat[0]->size)
    {
        fprintf(stderr, "Invalid parameters: matrixes incompatible for dot product\n");
        return (matrix *)NULL;
    }

    matrix *ans = matrix_create(m1->mat[0]->size, m2->n);
    if (ans == NULL)
    {
        mem_al_fail();
        return ans;
    }

    for (int i = 0; i < m1->mat[0]->size; i++)
    {
        for (int j = 0; j < m2->n; j++)
        {
            for (int k = 0; k < m1->n; k++)
            {
                ans->mat[j]->tab[i] += m1->mat[k]->tab[i] * m2->mat[j]->tab[k];
            }
        }
    }

    return ans;
}

void matrix_routines_init()
{
    head = NULL;
}

bool push_matrix(matrix *m)
{
    if (m == NULL)
    {
        fprintf(stderr, "Null matrix cannot be add to the tracking list\n");
        return false;
    }
    union data *d = (union data *)calloc(1, sizeof(union data));
    if (d == NULL)
    {
        mem_al_fail();
        return false;
    }
    d->m = m;
    node *n_new = (node *)calloc(1, sizeof(node));

    if (n_new == NULL)
    {
        mem_al_fail();
        free(d);
        return false;
    }

    n_new->d = d;
    n_new->s = MATRIX;
    n_new->next = head;
    head = n_new;

    return true;
}

bool push_vector(vector *v)
{
    if (is_null_vec(v))
    {
        fprintf(stderr, "Null vector cannot be add to the stack\n");
        return false;
    }

    union data *d = (union data *)calloc(1, sizeof(union data));

    if (d == NULL)
    {
        mem_al_fail();
        return false;
    }

    node *n_new = (node *)calloc(1, sizeof(node));

    if (n_new == NULL)
    {
        mem_al_fail();
        free(d);
        return false;
    }

    d->v = v;
    n_new->d = d;
    n_new->s = VECTOR;
    n_new->next = head;
    head = n_new;

    return true;
}

/*
 * Function use to remove the vector that compose the matrix from the tracking stack.
 * This function is called after a matrix is removed from the stack.
 * @params :
 * n : Number of vector that compose the matrix that is remove from the stack.
 */
void remove_matrix_vectors(int n)
{
    node *new_head = NULL;
    for (int i = 0; i < n; i++)
    {
        new_head = head->next;
        free(head->d);
        free(head);
        head = new_head;
    }
}

void pop()
{
    if (head != NULL)
    {
        node *new_head = head->next;
        if (head->s == VECTOR)
        {
            vector_free(head->d->v);
            free(head->d);
            free(head);
            head = new_head;
        }
        else
        {
            int columns = head->d->m->n;
            matrix_free(head->d->m);
            free(head->d);
            free(head);
            head = new_head;
            remove_matrix_vectors(columns);
        }
    }
}

void matrix_routines_end()
{
    while (head != NULL)
    {
        pop();
    }
}

void print_structures()
{

    for (node *current = head; current != NULL; current = current->next)
    {
        fprintf(stdout, "Printing a %s\n", current->s == VECTOR ? "vector" : "matrix");
        if (current->s == VECTOR)
            vector_print(current->d->v);
        else
            matrix_print(current->d->m);
    }
}