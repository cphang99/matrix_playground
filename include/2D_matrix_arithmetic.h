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

/**
 * Perform row addition adding r1*f to r2*f in matrix m
 * 
 * \param m     The matrix
 * \param r1    The row to add
 * \param r2    The row to be added to
 * \param f     A factor of r1 to apply
 * \param f2    A factor of r2 to apply
 *
 * \return      Matrix m with row addition applied
 */
matrix * row_addition(matrix * m, int r1, int r2, int f1, int f2);

/**
 * Perform a gauss elimination with partial pivoting on an augmented matrix
 *
 * \param a    The matrix
 * \param v    A column vector
 *
 * \returns    The solution to the linear equations posed by the 
 *             augmented matrix
 */
matrix * gauss_elimination_ppivot(matrix * a, matrix * v);
