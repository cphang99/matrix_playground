#include <2D_matrix_ops.h>

/**
 * Adds two matrices together
 * Represents in matlab A + B
 *
 * \param a     Matrix a
 * \param b     Matrix b
 * \returns     A matrix representing the addition of matrix a and b
 */
matrix * matrix_add(matrix * a, matrix * b);


/**
 * Subtracts one matrix from another
 * Represents in matlab A - B
 *
 * \param a     Matrix a
 * \param b     Matrix b
 * \returns     A matrix representing the subtraction of matrix a from b
 */
matrix * matrix_subtract(matrix * a, matrix * b);
