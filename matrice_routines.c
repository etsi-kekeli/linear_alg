#include "matrince_routines.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
    return !is_null_vec(v) && v->tab != NULL;
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
                return v;
            }
            free(vect);
        }
    }
    return (vector *)NULL;
}

void vector_free(vector *v)
{
    if (v != NULL)
    {
        if (v->tab != NULL)
            free(v->tab);
        free(v);
    }
}

void vector_print(vector v)
{
    if (is_valid_vec(&v))
    {
        for (int i = 0; i < v.size; i++)
            fprintf(stdout, "%.4lf\t", v.tab[i]);
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
                if (m->mat[i]->tab != NULL)
                    free(m->mat[i]->tab);
            }
            free(m->mat);
        }
        free(m);
    }
}

void matrix_print(matrix m)
{
    if (is_valid_matrix(&m))
    {
        for (int i = 0; i < m.mat[0]->size; i++)
        {
            for (int j = 0; j < m.n; j++)
            {
                fprintf(stdout, "%.4lf\t", m.mat[j]->tab[i]);
            }
            fprintf(stdout, "\n");
        }
    }
    else
    {
        fprintf(stderr, "Invalid matrix\n");
    }
}