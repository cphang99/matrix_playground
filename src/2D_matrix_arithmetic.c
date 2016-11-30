#include <2D_matrix_arithmetic.h>

static PLU_matrix_array * gauss_elimination_ppivot(matrix * a, matrix * v, bool isFwd);
static matrix * back_sub_solver(matrix * a, matrix * x);

matrix * matrix_add(matrix * a, matrix * b) {
    matrix * a_b = NULL;
    if( (get_rows(a) != get_rows(b)) || (get_columns(a) != get_columns(b)) ) {
        printf("Matrices do not have identical dimensions");
        printf(" Abort calculation\n");
    } else {
        a_b = initialise_matrix(get_rows(a), get_columns(a));
        for(int i = 0; i < get_rows(a); i++) {
            for(int j = 0; j < get_columns(a); j++) {
                #ifdef FIXED
                    elem val = fix16_add(get_matrix_member(a, i+1, j+1),
                            get_matrix_member(b, i+1, j+1));
                #else
                    elem val = get_matrix_member(a, i+1, j+1) +
                        get_matrix_member(b, i+1, j+1);
                #endif
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
                #ifdef FIXED
                    elem val = fix16_sub(get_matrix_member(a, i+1, j+1),
                            get_matrix_member(b, i+1, j+1));
                #else
                    elem val = get_matrix_member(a, i+1, j+1) -
                        get_matrix_member(b, i+1, j+1);
                #endif
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
                    #ifdef FIXED
                        val += fix16_mul(get_matrix_member(a, i+1, k+1),
                                get_matrix_member(b, k+1, j+1));
                    #else
                        val += get_matrix_member(a, i+1, k+1) *
                            get_matrix_member(b, k+1, j+1);
                    #endif
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

matrix * row_addition(matrix * m, int r1, int r2, float f1, float f2) {
    if(m != NULL) {
        if(r1 > 0 && r1 <= get_rows(m) && r2 > 0 && r2 <= get_rows(m)) {
            matrix * m_r1 = get_horizontal_slice(m, r1, r1);
            matrix * m_r2 = get_horizontal_slice(m, r2, r2);

            for(int i = 0; i < get_columns(m_r1); i++) {
                #ifdef FIXED
                    elem v1 = fix16_mul(get_matrix_member(m_r1, 1, i+1),
                            fix16_from_float(f1));
                    elem v2 = fix16_mul(get_matrix_member(m_r2, 1, i+1),
                            fix16_from_float(f2));
                    elem val = fix16_add(v1, v2);
                    set_matrix_member(m, r2, i+1, val);
                #else
                    set_matrix_member(m, r2, i+1,
                            (get_matrix_member(m_r1, 1, i+1) * f1) +
                            (get_matrix_member(m_r2, 1, i+1) * f2));
                #endif
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

float get_determinant(matrix * a) {
    if(a != NULL) {
        PLU_matrix_array * PLU = gauss_elimination_ppivot(a, NULL, true);
        float det = PLU->det;
        destroy_PLU(&PLU);
        return det;
    } else {
        fprintf(stderr, "Invalid matrix pointer given. Determinant not found\n");
        return 0;
    }
}

PLU_matrix_array * LU_decomposition(matrix * a) {
    #ifndef FLOAT
        #ifndef FIXED
            fprintf(stderr, "Integer elements being used will result"
                    " in an inaccurate PLU array being generated\n");
        #endif
    #endif
    return gauss_elimination_ppivot(a, NULL, true);
}

void destroy_PLU(PLU_matrix_array ** PLU_ptr) {
    PLU_matrix_array * PLU = *PLU_ptr;
    if(PLU->P != NULL && PLU->L != NULL && PLU->U !=NULL) {
        destroy_matrix(&(PLU->P));
        destroy_matrix(&(PLU->L));
        destroy_matrix(&(PLU->U));
        free(PLU);
        *PLU_ptr = NULL;
    } else {
        fprintf(stderr, "PLU array does not contain valid matrix pointers\n");
    }

}

matrix * solve_matrix_eq(matrix * a, matrix * x) {
    matrix * b = NULL;
    #if defined(FIXED) || defined(FLOAT)
        PLU_matrix_array * PLU = gauss_elimination_ppivot(a, x, true);
        matrix * U_extracted = get_vertical_slice(PLU->U, 1,
                                                  get_columns(PLU->U)-1);
        matrix * x_extracted = get_vertical_slice(PLU->U,
                                  get_columns(PLU->U), get_columns(PLU->U));
        if(PLU->det) {
            b = back_sub_solver(U_extracted, x_extracted);
            destroy_matrix(&U_extracted);
            destroy_matrix(&x_extracted);
        } else {
            fprintf(stderr,
                    "An inverse cannot be determined for this matrix\n");
        }
        destroy_PLU(&PLU);
    #else
        fprintf(stderr, "Solving equations is not supported for matrices "
                "of integer type, use FIXED or FLOAT types\n");
    #endif
    return b;
}

/**
 * Perform a gauss elimination with partial pivoting on an augmented matrix
 * derived from matrices a and v
 *
 * The gaussian elimination can either proceed 'forwards' or 'backwards':
 *     - forwards yields an upper triangular matrix
 *     - backwards yields a lower triangular matrix
 *
 * \param a         The matrix
 * \param v         A column vector. If NULL, gauss elimination
 *                  will be performed on matrix a only.
 * \param isFwd     Whether to proceed forwards or backwards on the
 *                  gaussian elimination.
 *
 * \returns         A augmented or ordinary matrix in row echelon form 
 *                  either in an upper or lower triangular form
 */
static PLU_matrix_array * gauss_elimination_ppivot(matrix * a, matrix * v, 
        bool isFwd) {
    PLU_matrix_array  * PLU = calloc(1, sizeof(PLU_matrix_array));
    matrix * U  = NULL;
    int detFactorChange = 1;
    if(a == NULL) {
        fprintf(stderr, "invalid pointer given on matrix a \n");
    } else if (v != NULL && get_columns(v) != 1) {
        fprintf(stderr, "matrix v does not only have one column: cannot "
                "create augmented matrix. cols=%d\n", get_columns(v));
    } else {

        //Setup of row and column boundaries 
        //Depends on whether 1) forward or backward gauss elimination 
        //is occuring and 2) if there is an augmented matrix.
        //If we don't have an augmented matrix, we want to consider
        //the whole matrix.
        int s_col = 0, e_col = 0, e_row = 0;
        int dir = 0;
        if(v != NULL) {
            U = h_concatenate(a, v);
        } else {
            U = initialise_matrix(get_rows(a), get_columns(a));
            memcpy(U->arr, a->arr, 
                    get_rows(U)*get_columns(U)*sizeof(elem));
            if(isFwd) {
                e_col++;
            } else {
                s_col++;
            }
        }
        #if !defined(FLOAT) && !defined(FIXED)
            matrix * fixed_U = initialise_matrix(get_rows(U), get_columns(U));
            for(int i = 0; i < get_rows(U); i++) {
                for(int j = 0; j < get_columns(U); j++) {
                    set_matrix_member(fixed_U, i+1, j+1,
                            fix16_from_int(get_matrix_member(U, i+1, j+1)));
                }
            }
            destroy_matrix(&U);
            U = fixed_U;
        #endif
        PLU->U = U;

        if(isFwd) {
            s_col = 0;
            e_col += get_columns(U)-2;
            e_row = get_rows(U);
            dir = 1;
        } else {
            s_col += get_columns(U)-2;
            e_col = -1;
            e_row = -1;
            dir = -1;
        }
        matrix * P = PLU->P = get_identity_matrix(get_rows(a));
        matrix * L = PLU->L =  get_identity_matrix(get_rows(a));
        //Each go through a column represents a pass
        //Each time we establish a starting row which has the 
        //same indice as the current column
        for(int i = s_col; i != e_col; i+=(1*dir)) {
            //Establish the pivot
            elem pivot = ELEM_MIN;
            int max_row = 0;

            //Note that pivot cannot work if the max elem = 0
            //Find max row and then interchange with current starting
            //row
            for(int j = i; j != e_row; j+=(1*dir)) {
                elem e = get_matrix_member(U, j+1, i+1);
                if(e > pivot && e != 0) {
                    pivot = e;
                    max_row = j+1;
                }
            }

            if(max_row != i+1) {
                //For debugging row interchange indices
                //printf("Interchanging row %d with row %d, "
                //        "max_row=%d i=%d\n", i+1, max_row, max_row, i);
                row_interchange(U, i+1, max_row);
                row_interchange(P, i+1, max_row);
                detFactorChange *= -1;
            }

            //Perform elementry row operations to put all elements below
            //the current starting row = 0
            for(int k = i+(1*dir); k != e_row; k+=(1*dir)) {
                elem f1 = get_matrix_member(U, k+1, i+1) * -1;
                #ifdef FLOAT
                    row_addition(U, i+1, k+1, f1/pivot, 1);
                #else
                    float f = fix16_to_float(fix16_div(f1,pivot));
                    row_addition(U, i+1, k+1, f, 1);
                #endif

                #ifndef FLOAT
                    set_matrix_member(L, k+1, i+1,
                            fix16_mul(fix16_div(f1, pivot),
                                      fix16_from_int(-1)));
                #else
                    set_matrix_member(L, k+1, i+1, f1/pivot * -1);
                #endif
                //For debugging row elementry operations
                //printf("r%d = r%d*%"ELEM_F" + r%d*%"ELEM_F"\n",
                //        k+1, i+1, f1, k+1, pivot);
            }
        }

        PLU->det = 1;
        #ifndef FLOAT
            elem det_fixed_pt = fix16_one;
        #endif
        for(int k = 0; k < get_rows(U); k++) {
            #ifndef FLOAT
               det_fixed_pt = fix16_mul(det_fixed_pt,
                       get_matrix_member(U, k+1, k+1));
            #else
               PLU->det *= get_matrix_member(U, k+1, k+1);
            #endif
        }
        #ifndef FLOAT
            PLU->det = fix16_to_float(det_fixed_pt);
        #endif
        PLU->det /= detFactorChange;
    }
     
    return PLU;
}
/* Performs back substitution */
static matrix * back_sub_solver(matrix * a, matrix * x) {
    matrix * b = NULL;
    print_matrix(a);
    print_matrix(x);
    #if defined(FLOAT) || defined(FIXED)
        if( (get_rows(a) == get_columns(a)) && (get_columns(x) == 1) ) {
            b = initialise_matrix(get_rows(a), 1);
            #ifdef FLOAT
                elem b_initial = get_matrix_member(x, get_rows(a), 1) /
                    get_matrix_member(a, get_rows(a), get_columns(a));
            #else
                elem b_initial = fix16_div(get_matrix_member(x, get_rows(a), 1),
                    get_matrix_member(a, get_rows(a), get_columns(a)));
            #endif
            set_matrix_member(b, get_rows(a), 1, b_initial);
            for(int i = get_rows(a)-1; i > 0; i--) {
                elem y = get_matrix_member(x, i, 1);
                for(int j = get_columns(a); j > i; j--) {
                    #ifdef FLOAT
                        y -= get_matrix_member(b, j, 1) * get_matrix_member(a, i, j);
                    #else
                        y -= fix16_mul(get_matrix_member(b, j, 1),
                                get_matrix_member(a, i ,j));
                    #endif
                    //printf("%"ELEM_F" ", y);
                }
                //printf("\n");
                #ifdef FLOAT
                    elem b_mem = y / get_matrix_member(a, i, i);
                #else
                    elem b_mem = fix16_div(y, get_matrix_member(a, i, i));
                #endif
                set_matrix_member(b, i, 1, b_mem);
            }
       } else {
           fprintf(stderr, "Dimensions of matrix a and/or x are not suitable"
                   " to perform back substitution\n");
       }
  #else
       fprintf(stderr,
                "Back substitution not supported for integer types\n");
  #endif
  return b;
}
