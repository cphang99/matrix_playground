#include<2D_matrix_ops.h>
#include<math.h>

/**
 * Applies an element-wise matrix operation
 *
 * \param fp    The element-wise matrix operation
 * \param arr   The matrix
 * \return      The transformed array
 */
matrix * elem_matrix_operation(elem (*fp)(elem, float), matrix * m, 
        float param);

/*
 * Applies a power to an element in a matrix
 *
 * \param x     The element to be transformed
 * \param p     The power to be applied
 * \return      A transformed element
 */
elem pow_elem(elem x, float p);

/*
 * Applies an nth root to an element in a matrix
 *
 * \param x     The element to be transformed
 * \param p     The root to be applied
 * \return      The transformed element
 */
elem sqroot_elem(elem x, float p);
