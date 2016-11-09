#include<2D_matrix_ops.h>
#include<math.h>

/**
 * Applies an element-wise matrix operation
 *
 * \param fp    The element-wise matrix operation
 * \param arr   The matrix
 * \return      The transformed array
 */
matrix * elem_matrix_operation(elem (*fp)(elem), matrix * m) ;

/*
 * Squares an individual element in an array
 */
elem square(elem x);

/*
 * Calculates the square root of an element.
 * Note that this takes the floor value (where integers are involved).
 *
 * \param x     The element to be transformed
 * \return      The transformed element.
 */
elem sq_root(elem x);


