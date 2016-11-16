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

matrix * row_interchange(matrix * m, int r1, int r2) {
    if(m != NULL) {
        if(r1 > 0 && r1 <= get_rows(m) && r2 > 0 && r2 <= get_rows(m)) {
            matrix * m_r1 = get_horizontal_slice(m, r1, r1);
            matrix * m_r2 = get_horizontal_slice(m, r2, r2);

            for(int j = 0; j < get_columns(m); j++) {
                set_matrix_member(m, r2, j+1, 
                        get_matrix_member(m_r1, 1, j+1));
                set_matrix_member(m, r1, j+1,
                        get_matrix_member(m_r2, 1, j+1));
            }
            destroy_matrix(&m_r1);
            destroy_matrix(&m_r2);
        } else {
            fprintf(stderr, "either r1 or r2 are invalid indices for "
                    "row interchange r1=%d r2=%d num_rows=%d\n", 
                    r1, r2, get_rows(m));
        }
    } else {
        fprintf(stderr, "Invalid matrix pointer given\n");
    }
    return m;
}

matrix * column_interchange(matrix * m, int c1, int c2) {
    if(m != NULL) {
        if(c1 > 0 && c1 <= get_columns(m) && c2 > 0 && c2 <= get_columns(m)) {
            matrix * m_c1 = get_vertical_slice(m, c1, c1);
            matrix * m_c2 = get_vertical_slice(m, c2, c2);

            for(int j = 0; j < get_rows(m); j++) {
                set_matrix_member(m, j+1, c2, 
                        get_matrix_member(m_c1, j+1, 1));
                set_matrix_member(m, j+1, c1,
                        get_matrix_member(m_c2, j+1, 1));
            }
            destroy_matrix(&m_c1);
            destroy_matrix(&m_c2);
        } else {
            fprintf(stderr, "either c1 or c2 are invalid indices for "
                    "column interchange c1=%d c2=%d\n", c1, c2);
        }
    } else {
        fprintf(stderr, "Invalid matrix pointer given\n");
    }
    return m;
}

matrix * row_addition(matrix * m, int r1, int r2, int f1, int f2) {
    if(m != NULL) {
        if(r1 > 0 && r1 <= get_rows(m) && r2 > 0 && r2 <= get_rows(m)) {
            matrix * m_r1 = get_horizontal_slice(m, r1, r1);
            matrix * m_r2 = get_horizontal_slice(m, r2, r2);

            for(int i = 0; i < get_columns(m_r1); i++) {
                set_matrix_member(m, r2, i+1,
                        (get_matrix_member(m_r1, 1, i+1) * f1) +
                        (get_matrix_member(m_r2, 1, i+1) * f2));
            }
            destroy_matrix(&m_r1);
            destroy_matrix(&m_r2);
        } else {
            fprintf(stderr, "either r1 or r2 are invalid row indices "
                    "r1=%d r2 =%d\n",r1, r2);
        }
    } else {
        fprintf(stderr, "Invalid matrix pointer given\n");
    }
    return m;
}

matrix * gauss_elimination_ppivot(matrix * a, matrix * v, bool isFwd) {
    matrix * a_m = NULL;
    if(a != NULL && v != NULL) {
        if(get_columns(v) == 1) {
            a_m = h_concatenate(a, v);
            //Each go through a column represents a pass
            //Each time we establish a starting row which has the 
            //same indice as the current column 
            int s_col = 0, e_col = 0, e_row = 0;
            int dir = 0;
            if(isFwd) {
                s_col = 0;
                e_col = get_columns(a_m)-2;
                e_row = get_rows(a_m);
                dir = 1;
            } else {
                s_col = get_columns(a_m)-2;
                e_col = -1;
                e_row = -1;
                dir = -1;
            }
            for(int i = s_col; i != e_col; i+=(1*dir)) {
                //Establish the pivot
                elem pivot = ELEM_MIN;
                int max_row = 0;

                //Note that pivot cannot work if the max elem = 0
                //Find max row and then interchange with current starting
                //row
                for(int j = i; j != e_row; j+=(1*dir)) {
                    elem e = get_matrix_member(a_m, j+1, i+1);
                    if(e > pivot && e != 0) {
                        pivot = e;
                        max_row = j+1;
                    }
                }
                if(max_row != i+1) {
                    //For debugging row interchange indices
                    //printf("Interchanging row %d with row %d, "
                    //        "max_row=%d i=%d\n", i+1, max_row, max_row, i);
                    row_interchange(a_m, i+1, max_row);
                }

                //Perform elementry row operations to put all elements below
                //the current starting row = 0
                for(int k = i+(1*dir); k != e_row; k+=(1*dir)) {
                    elem f1 = get_matrix_member(a_m, k+1, i+1) * -1;
                    row_addition(a_m, i+1, k+1, f1, pivot);
                    //For debugging row elementry operations
                    //printf("r%d = r%d*%d + r%d*%d\n", 
                    //        k+1, i+1, f1, k+1, pivot);
                }
            }
        } else {
            fprintf(stderr, "matrix v does not only have one column: cannot "
                    "create augmented matrix. cols=%d\n", get_columns(v));
        }
    } else {
        fprintf(stderr, "invalid pointer given on matrix a or v\n");
    }
    return a_m;
}
