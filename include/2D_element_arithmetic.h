#include<2D_matrix_ops.h>
#include<math.h>

/**
 * Applies an element-wise matrix operation
 * Please note that this does not create a new matrix
 * object, but modifies the existing one.
 *
 * \param fp        The element-wise matrix operation
 * \param m         The matrix
 * \param param     A user-specified parameter to pass to the fp
 * \return          The transformed array
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

/*
 * Multiplies an element by a factor
 * Equivalent to A.*n in matlab
 *
 * \param x     The element to be transformed
 * \param p     The factor
 * \return      The transformed element
 */
elem multiply_elem(elem x, float p); 

/*
 * Divides an element by a factor
 * Equivalent to A./n in matlab
 *
 * \param x     The element to be transformed
 * \param p     The factor
 * \return      The transformed element
 */
elem divide_elem(elem x, float p);
