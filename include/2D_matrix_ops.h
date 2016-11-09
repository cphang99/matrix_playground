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
 * Initialises an empty matrix
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

/*
 * Vertically concatenates two matrices together.
 * Equivalent to [A; B] in matlab
 *
 * \param a     The matrix a
 * \param b     The matrix b
 * \return      A vertically concatenated matrix of a and b
 */
matrix * v_concatenate(matrix * a, matrix * b);

/*
 * Horizontally concatenate two matrices together.
 * Equivalent to [A B] in matlab
 *
 * \param a     The matrix a
 * \param b     The matrix b
 * \return      A horizontally concatenated matrix of a and b
 */
matrix * h_concatenate(matrix * a, matrix * b);

/* Create a row vector.
 * Equivalent to j:i:k in matlab
 *
 * \param j     The lower range of the row vector
 * \param i     The upper range of the row vector
 * \param k     The interval between the row vector
 * \return      A row vector between j and i with interval k of type matrix.
 */
matrix * create_row_vector(int j, int i, int k);

/* Get a horizontal slice of a matrix
 * Equivalent to A(i,:) in matlab
 *
 * \param m     The matrix
 * \param r     A slice of the array.
 * \return      A row vector consisting of row r of matrix m
 */
matrix * get_horizontal_slice(matrix * m, int r);

/* Get a vertical slice of a matrix
 * Equivalent to A(:,i) in matlab
 *
 * \param m     The matrix
 * \param c     A slice of the array.
 * \return      A row vector consisting of column c of matrix m
 */
matrix * get_vertical_slice(matrix * m, int c);
