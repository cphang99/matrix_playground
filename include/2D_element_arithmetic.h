#include<2D_matrix_ops.h>
#include<math.h>

/**
 * Applies an element-wise matrix operation
 *
 * \param fp    The element-wise matrix operation
 * \param arr   The matrix
 * \return      The transformed array
 */
matrix * elem_matrix_operation(int (*fp)(int), matrix * m) ;

/*
 * Squares an individual element in an array
 */
int square(int x);


