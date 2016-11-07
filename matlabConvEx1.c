#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matrix_ops.h"

typedef struct {
    int rows;
    int columns;
    int ** arr;
} array;

int mydist4(array *  X);

//From matlab
//[m,n] = size(A) returns the number of rows and columns when A is a matrix.
void size(array * X, int * dim);

int square(x);

int main (int argc, char * argv[]) {
    int D = 0; 
    int arr[2][2] = {
        {0,7},
        {6,0}
    };
    array X = initialise_array(rows, columns, arr);


    D = mydist4(array * X);
    printf("Euclidean distance = %d\n", D);
    return 0;
}

int mydist4(array *  X) {
    if(X->columns < 2) {
        printf("Number of points should be greater than one\n");
        exit(1);
    }
    int n = X->columns;
    int m = X->rows;

    int p_squared = matrix_operation(arr, &square);
    int q_squared = matrix_operation(arr, &square);

    return sqrt(p^2 + q^2 -2pq);
}

void size(array * X, int * dim) {
    dim[0] = X.rows;
    dim[1] = X.columns;
}

int square(x) {
    return x * x;
}
