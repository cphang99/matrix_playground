#include<2D_matrix_ops.h>
#include<math.h>

/**
 * Compares two integers to whether they are equal or not
 *
 * \param a     Integer a
 * \param b     Integer b
 * \return      True if the same, False if not.
 */
bool compare_integers(int a, int b);

/**
 * Compares whether a pointer is NULL or not
 *
 * \param a     A pointer
 * \return      True if NULL, False if not.
 */
bool compare_null(void * a);

/**
 * Test method for test_suite. Always returns true
 *
 * \return      True
 */
bool alwaysTrue(void);

/**
 * Test method for test_suite. Always returns false
 *
 * \return      False
 */
bool alwaysFalse(void);

/**
 * Determines whether two matrices are equal or not
 *
 * Matrices are equal iff dimensions of a == dimensions of b AND
 * if every value of a at coordinate (x,y) is equal to every value of b
 * at coordinate (x,y)
 *
 * \param a     Matrix a
 * \param b     Matrix b
 * \returns     A boolean whether matrix a == matrix b
 */
bool compare_matrices(matrix * a, matrix * b);
