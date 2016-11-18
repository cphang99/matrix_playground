#include <2D_matrix_ops.h>

typedef struct {
    matrix * P;
    matrix * L;
    matrix * U;
    elem det;
} PLU_matrix_array;

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
matrix * row_addition(matrix * m, int r1, int r2, elem f1, elem f2);

/**
 * Performs LU decomposition on a given matrix a
 *
 * \param a     The matrix
 *
 * \returns     A set of matrices P, L and U
 */
PLU_matrix_array * LU_decomposition(matrix * a);

/**
 * Destroys a PLU matrix array
 *
 * \param PLU_ptr   A ptr to a PLU array
 */   
void destroy_PLU(PLU_matrix_array ** PLU_ptr); 
