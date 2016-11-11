#include <2D_matrix_arithmetic.h>

matrix * matrix_add(matrix * a, matrix * b) {
    matrix * a_b = NULL;
    if( (get_rows(a) != get_rows(b)) || (get_columns(a) != get_columns(b)) ) {
        printf("Matrices do not have identical dimensions");
        printf(" Abort calculation\n");
    } else {
        a_b = initialise_matrix(get_rows(a), get_columns(a));
        for(int i = 0; i < get_rows(a); i++) {
            for(int j = 0; j < get_columns(a); j++) {
                elem val = get_matrix_member(a, i+1, j+1) + 
                    get_matrix_member(b, i+1, j+1);
                set_matrix_member(a_b, i+1, j+1, val);
            }
        }
    }

    return a_b;
}


matrix * matrix_subtract(matrix * a, matrix * b) {
    matrix * a_b = NULL;
    if( (get_rows(a) != get_rows(b)) || (get_columns(a) != get_columns(b)) ) {
        printf("Matrices do not have identical dimensions");
       printf(" Abort calculation\n");
    } else {
        a_b = initialise_matrix(get_rows(a), get_columns(a));
        for(int i = 0; i < get_rows(a); i++) {
            for(int j = 0; j < get_columns(a); j++) {
                elem val = get_matrix_member(a, i+1, j+1) - 
                    get_matrix_member(b, i+1, j+1);
                set_matrix_member(a_b, i+1, j+1, val);
            }
        }
    }

    return a_b;
}

matrix * matrix_multiplication(matrix * a, matrix *b) {
    matrix * a_b = NULL;
    if( (get_columns(a) != get_rows(b)) ) {
        printf("Matrices do not have suitable dimensions");
        printf(" Abort calculation\n");
    } else {
        a_b = initialise_matrix(get_rows(a), get_columns(b));
        for(int i = 0; i < get_rows(a_b); i++) {
            for(int j = 0; j < get_columns(a_b); j++) {
                elem val = 0;
                for(int k = 0; k < get_columns(a); k++) {
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
