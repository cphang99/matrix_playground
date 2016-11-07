#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
 * Initialises a matrix from a 2D integer array
 *
 * \param rows      The number of rows in the array
 * \param columns   The number of columns in the array
 * \param arr       The 2D array
 * \return          A matrix of type matrix
 */
matrix * initialise_matrix(int rows, int columns, int arr[][columns]);

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

int get_matrix_member(matrix * m, int x, int y);
