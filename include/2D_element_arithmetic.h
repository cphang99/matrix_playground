#ifndef ELEMENT_OPS_H
#define ELEMENT_OPS_H

#include"2D_matrix_ops.h"
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

/**
 * Applies an element-wise operation to a horizontal slice
 * Please note that this does not create a new matrix
 * object, but modifies the existing one.
 *
 * \param fp        The element-wise matrix oepration
 * \param m         The matrix
 * \param r_s       The starting row to apply the operation from.
 * \param r_e       The finishing row to apply to operation from.
 * \param param     A user-specified parameter to pass to the fp
 * \return          The transformed array
 */
matrix * elem_row_operation(elem (*fp)(elem, float), matrix * m,
                int r_s, int r_e, float param);

/**
 * Applies an element-wise operation to a vertical slice
 * Please note that this does not create a new matrix
 * object, but modifies the existing one.
 *
 * \param fp        The element-wise matrix oepration
 * \param m         The matrix
 * \param c_s       The starting column to apply the operation from.
 * \param c_e       The finishing column to apply to operation from.
 * \param param     A user-specified parameter to pass to the fp
 * \return          The transformed array
 */
matrix * elem_column_operation(elem (*fp)(elem, float), matrix * m,
                int c_s, int c_e, float param);

/*
 * Sums all members across one matrix dimension
 * Equivalent to matlab sum(A,1) or sum(A,2) in a 2D matrix.
 *
 * \param m     The matrix
 * \param dim   The dimension to sum in
 * \return      A row or column vector with the sums
 */
matrix * sum_matrix(matrix * m, int dim);

/* Fills a matrix with a given parameter
 * Used as a substitute for ones() in matlab
 *
 * \param x     The element to be transformed
 * \param p     The element to fill with.
 * \return      A parameter p of type elem that fills the element
 */
elem fill_matrix(elem x, float p);

/*
 * Applies a power to an element in a matrix
 * Equivalent to A.^n in matlab
 *
 * \param x     The element to be transformed
 * \param p     The power to be applied
 * \return      A transformed element
 */
elem pow_elem(elem x, float p);

/*
 * Applies an nth root to an element in a matrix
 * Equivalent to A.^1/n in matlab
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

#endif
