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

/**
 * Multiply two matrices together
 * Represents in matlab A * B
 *
 * \param a     Matrix a
 * \param b     Matrix b
 * \returns     A matrix representing the matrix multiplication of 
 *              matrix a and b
 */
matrix * matrix_multiplication(matrix * a, matrix * b);

/**
 * Interchange two matrix rows
 *
 * \param m     The matrix
 * \param r1    The index for the first row
 * \param r2    The index for the second row
 * \returns     A matrix with rows r1 and r2 interchanged
 *
 */
matrix * row_interchange(matrix * m, int r1, int r2);

/**
 * Interchange two matrix columns
 *
 * \param m     The matrix
 * \param r1    The index for the first column
 * \param r2    The index for the second column
 * \returns     A matrix with columns c1 and c2 interchanged
 *
 */
matrix * column_interchange(matrix * m, int c1, int c2);
