#include <2D_matrix_arithmetic.h>

matrix * matrix_add(matrix * a, matrix * b) {
    matrix * a_b = NULL;
    if( (a->rows != b->rows) || (a->columns != b->columns) ) {
        printf("Matrices do not have identical dimensions");
        printf(" Abort calculation\n");
    } else {
        a_b = initialise_matrix(a->rows, a->columns);
        for(int i = 0; i < a->rows; i++) {
            for(int j = 0; j < a->columns; j++) {
                int val = get_matrix_member(a, i+1, j+1) + 
                    get_matrix_member(b, i+1, j+1);
                set_matrix_member(a_b, i+1, j+1, val);
            }
        }
    }

    return a_b;
}


matrix * matrix_subtract(matrix * a, matrix * b) {
    matrix * a_b = NULL;
    if( (a->rows != b->rows) || (a->columns != b->columns) ) {
        printf("Matrices do not have identical dimensions");
       printf(" Abort calculation\n");
    } else {
        a_b = initialise_matrix(a->rows, a->columns);
        for(int i = 0; i < a->rows; i++) {
            for(int j = 0; j < a->columns; j++) {
                int val = get_matrix_member(a, i+1, j+1) - 
                    get_matrix_member(b, i+1, j+1);
                set_matrix_member(a_b, i+1, j+1, val);
            }
        }
    }

    return a_b;
}

matrix * matrix_multiplication(matrix * a, matrix *b) {
    matrix * a_b = NULL;
    if( (a->columns != b->rows) ) {
        printf("Matrices do not have suitable dimensions");
        printf(" Abort calculation\n");
    } else {
        a_b = initialise_matrix(a->rows, b->columns);
        for(int i = 0; i < a_b->rows; i++) {
            for(int j = 0; j < a_b->columns; j++) {
                int val = 0;
                for(int k = 0; k < a->columns; k++) {
                    //Debug statement for matrix multiplication
                    /*printf("(A%d%d * B%d%d)\n", i+1, k+1,
                            k+1, j+1);*/
                    val += get_matrix_member(a, i+1, k+1) * 
                        get_matrix_member(b, k+1, j+1);
                }
                set_matrix_member(a_b, i+1, j+1, val);
            }
        }
    }
    return a_b;
}
