#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct {
    int rows;
    int columns;
    int arr[]; //Note flexible array member
} matrix;

/*
 * Squares an individual element in an array
 */
int square(int x);

/**
 * Initialises a matrix
 *
 * \param rows      The number of rows in the array
 * \param columns   The number of columns in the array
 * \param arr       The 2D array
 * \return          A matrix of type matrix
 */
matrix * initialise_matrix(int rows, int columns);

/**
 * Applies an element-wise matrix operation
 *
 * \param fp    The element-wise matrix operation
 * \param arr   The matrix
 * \return      The transformed array
 */
matrix * elem_matrix_operation(int (*fp)(int), matrix * m) ;

/**
 * Prints the matrix to stdout
 *
 * \param m     The matrix
 */
void print_matrix(matrix * m); 

/**
 * Frees the memory allocated to the matrix
 *
 * \param m     The matrix
 */
void destroy_matrix(matrix * m);

/**
 * Returns a matrix member at a specific location
 * Please note that indexing starts from *1*
 *
 * \param m     The matrix
 * \param x     The 'x' (row) coordinate
 * \param y     The 'y' (column) coordinate
 * \return      The matrix member
 */
int get_matrix_member(matrix * m, int x, int y);

/**
 * Updates a matrix member at a specific location
 * Please note that indexing starts from *1*
 *
 * \param m     The matrix
 * \param x     The 'x' (row) coordinate
 * \param y     The 'y' (column) coordinate
 * \param val   The value to update the matrix member with
 * \return      The updated matrix
 */
matrix * set_matrix_member(matrix * m, int x, int y, int val);

/*
 * Transposes a matrix. Equivalent to A.' in matlab
 *
 * \param m     The matrix
 * \return      A transposed matrix of type matrix
 */
matrix * transpose_matrix(matrix * m);
