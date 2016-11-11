#ifndef MATRIX_OPS_H
#define MATRIX_OPS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

typedef int32_t elem;

typedef struct {
    int rows;
    int columns;
    elem arr[]; //Note flexible array member
} matrix;

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
elem get_matrix_member(matrix * m, int x, int y);

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
matrix * set_matrix_member(matrix * m, int x, int y, elem val);

/**
 * Updates a matrix member on an array level
 * Please note that the array passed must be a 1D array, formatted
 * so that members can be accessed via arr[i*columns + j]
 * 
 * Failure to do so will result in undefined behaviour.
 *
 * \param m         The matrix
 * \param arr       An array of type elem
 * \param rows      The rows in the array
 * \param columns   The columns in the array
 * \return          A matrix with a updated array. Will
 *                  return an untransformed matrix (or NULL)
 *                  if this is unsuccessful
 */
matrix * set_matrix_array(matrix * m, elem * arr, int rows, int columns);

/**
 * Gives the number of rows in the matrix
 * Returns 0 and warning if no valid matrix found
 *
 * \param m     The matrix
 * \return      The number of rows, or 0 and a warning if no matrix present
 */
int get_rows(matrix * m);

/**
 * Gives the number of columns in the matrix
 * Returns 0 and warning if no valid matrix found
 *
 * \param       The matrix
 * \return      The number of columns, or 0 and a warning if no matrix present
 */
int get_columns(matrix * m);

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

/* Create a n x n diagonal matrix from a vector of length n
 * Equivalent to diag(v) in matlab
 *
 * \param v     The vector to create the matrix from
 * \return      A n x n diagonal matrix
 */
matrix * get_diag_matrix(matrix * v);

/* Create an identity matrix of n x n size
 * Equivalent to eye(n) in matlab
 *
 * \param n     The length of both dims in the identity matrix
 * \return      An n x n identity matrix
 */
matrix * get_identity_matrix(int n);

#endif
