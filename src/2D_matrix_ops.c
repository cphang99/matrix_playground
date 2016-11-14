#include <2D_matrix_ops.h>
#include <2D_element_arithmetic.h>

matrix * initialise_matrix(int rows, int columns) {
    matrix * a = malloc(sizeof(matrix) + (rows * columns * sizeof(elem)));
    memset(a, 0, sizeof(matrix) + (rows * columns * sizeof(elem)));
    a->rows = rows;
    a->columns = columns;
    
    if(a == NULL) {
        fprintf(stderr, "WARNING: matrix initialisation failed\n");
    }
    return a;
}

elem get_matrix_member(matrix * m, int x, int y) {
    if(m == NULL) {
        fprintf(stderr, "Not valid matrix pointer\n");
        return 0;
    } else if(x > get_rows(m) || y > get_columns(m)) {
        fprintf(stderr, "Out of bounds\n");
        return 0;
    } else {
        return m->arr[ (x-1)* get_columns(m) +(y-1)];
    }
}

matrix * set_matrix_member(matrix * m, int x, int y, elem val) {
    if(m == NULL) {
        fprintf(stderr, "Not valid matrix pointer\n");
        return NULL;
    } else if( x > get_rows(m) || y > get_columns(m)) {
        fprintf(stderr, "Out of bounds\n");
        return NULL;
    } else {
        m->arr[ (x-1) * get_columns(m) + (y-1) ] = val;
        return m;
    }
}

matrix * set_matrix_array(matrix * m, elem * arr, int rows, int columns) {
    if(m == NULL || arr == NULL) {
        fprintf(stderr, "Invalid pointer to matrix and/or array. Abort\n");
    } else if( (get_rows(m) != rows) || (get_columns(m) != columns) ) {
        fprintf(stderr, "array dimensions do not match that of matrix. "
                "Abort\n");
    } else {
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < columns; j++) {
                set_matrix_member(m, i+1, j+1, arr[i*columns + j]);
            }
        }
    }
    return m;
}

int get_rows(matrix * m) {
    int rows = 0;
    if(m != NULL) {
        rows = m->rows;
    } else {
        fprintf(stderr, "No valid matrix to obtain rows from\n");
    }
    return rows;
}

int get_columns(matrix * m) {
    int columns = 0;
    if(m != NULL) {
        columns = m->columns;
    } else {
        fprintf(stderr, "No valid matrix to obtain columns from\n");
    }
    return columns;
}

void print_matrix(matrix * m) {
    if(m != NULL) {
        for(int i = 0; i < get_rows(m); i++) {
            for(int j = 0; j < get_columns(m); j++) {
                printf("%d ", get_matrix_member(m, i+1, j+1));
            }
            putchar('\n');
        }
        putchar('\n');
    } else {
        fprintf(stderr, "No valid matrix to print out\n");
    }
}

void destroy_matrix(matrix * m) {
    if(m != NULL) {
        free(m);
    } else {
        fprintf(stderr, "No valid matrix to free memory from\n");
    }
}

matrix * transpose_matrix(matrix * m) {
    matrix * t_m = NULL;
    if(m != NULL) {
        t_m = initialise_matrix(get_columns(m), get_rows(m));

        for(int i = 0; i < get_rows(m); i++) {
            for(int j = 0; j < get_columns(m); j++) {
                set_matrix_member(t_m, j+1, i+1, get_matrix_member(m, i+1, j+1));
            }
        }
    } else {
        fprintf(stderr, "No valid matrix to transpose\n");
    }
    return t_m;
}

matrix * h_concatenate(matrix * a, matrix * b) {

    matrix * a_b = NULL;
    if(a == NULL || b == NULL) {
        fprintf(stderr, "One or both matrices are not valid pointers, abort\n");
    } else if(get_rows(a) != get_rows(b)) {
        fprintf(stderr, "Cannot vertically concatenate matrices " 
                "of different heights\n");
    } else {
        a_b =  initialise_matrix(get_rows(a), (get_columns(a) + get_columns(b)));
        for(int i = 0; i < get_rows(a_b); i++) {
            for(int j_a = 0; j_a < get_columns(a); j_a++) {
                set_matrix_member(a_b, i+1, j_a+1, 
                        get_matrix_member(a, i+1, j_a+1));
            }
            for(int j_b = 0; j_b < get_columns(b); j_b++) {
                set_matrix_member(a_b, i+1, get_columns(a)+j_b+1, 
                        get_matrix_member(b, i+1, j_b+1));
            }
        }
    }
    return a_b;

}

matrix * v_concatenate(matrix * a, matrix * b) {
    matrix * a_b = NULL;
    if(a == NULL || b == NULL) {
        fprintf(stderr, "One or both matrices are not valid pointers, abort "
                "vertical transpose\n");
    } else if(get_columns(a) != get_columns(b)) {
        fprintf(stderr, "Cannot horizontally concatenate matrices of "
                "different widths\n");
    } else {
        a_b = initialise_matrix( (get_rows(a) + get_rows(b)), get_columns(a) );
        for(int i_a = 0; i_a < get_rows(a); i_a++) {
            for(int j_a = 0; j_a < get_columns(a_b); j_a++) {
                set_matrix_member(a_b, i_a+1, j_a+1, 
                        get_matrix_member(a, i_a+1, j_a+1));
            }
        }

        for(int i_b = 0; i_b < get_rows(b); i_b++) {
            for(int j_b = 0; j_b < get_columns(a_b); j_b++) {
                set_matrix_member(a_b, get_rows(a)+i_b+1, j_b+1, 
                        get_matrix_member(b, i_b+1, j_b+1));
            }
        }
    }
    return a_b;
}

matrix * create_row_vector(int j, int i, int k) {
    matrix * v = NULL;
    if(k > 0) {
        int numCols = ((i-j)/k) + 1;
        v = initialise_matrix(1, numCols);
        for(int l = 0; l < numCols; l++) {
            set_matrix_member(v, 1, l+1, j+(l*k));
        }
    } else {
        printf("The interval must be greater than 0\n");
    }

    return v;
}

matrix * get_horizontal_slice(matrix * m, int r_s, int r_e) {
    matrix * h_s = NULL;
    if(m == NULL) {
        fprintf(stderr, "Not valid matrix pointer\n");
    } else if(r_s > 0 && r_s <= get_rows(m)) {
        int num_rows = r_e - r_s + 1;
        if(num_rows > 0 && num_rows < get_rows(m)) {
            h_s= initialise_matrix(num_rows, get_columns(m));
            for(int i = 0; i < num_rows; i++) { 
                for(int j = 0; j < get_columns(m); j++) {
                    set_matrix_member(h_s, i+1, j+1, 
                            get_matrix_member(m, i+r_s, j+1));
                }
            }
        } else {
            fprintf(stderr, "error in subscripts passed to function. "
                    "Number of rows = %d\n", num_rows);
        }
    } else {
        printf("Slice is out of matrix row bounds\n");
    }

    return h_s;
}

matrix * get_vertical_slice(matrix * m, int c_s, int c_e) {
    matrix * v_s = NULL;
    if(m == NULL) {
        fprintf(stderr, "Not valid matrix pointer\n");
    } else if(c_s > 0 && c_s <= get_columns(m)) {
        int num_columns = c_e - c_s + 1;
        if(num_columns > 0 && num_columns < get_columns(m)) {
            v_s= initialise_matrix(get_rows(m), num_columns);
            for(int i = 0; i < get_rows(m); i++) { 
                for(int j = 0; j < num_columns; j++) {
                    set_matrix_member(v_s, i+1, j+1, 
                            get_matrix_member(m, i+1, j+c_s));
                }
            }
        } else {
            fprintf(stderr, "error in subscripts passed to function. "
                    "Number of columns = %d\n", num_columns);
        }
    } else {
        printf("Slice is out of matrix column bounds\n");
    }

    return v_s;
}

matrix * get_diag_matrix(matrix * v) {
    matrix * m = NULL;
    if(v != NULL) {
        bool hasTransposed = false;
        if(get_rows(v) > 1) {
            //Transpose if a column vector, so can treat equally
            //in the next step.
            m = initialise_matrix(get_rows(v), get_rows(v)); 
            v = transpose_matrix(v);
            hasTransposed = true;
        } else {
            m = initialise_matrix(get_columns(v), get_columns(v));
        }
        for(int i = 0; i < get_columns(v); i++) {
            set_matrix_member(m, i+1, i+1, get_matrix_member(v, 1, i+1)); 
        }
        if(hasTransposed) destroy_matrix(v);
    } else {
        fprintf(stderr, "Not valid matrix pointer\n");
    }

    return m;

}

matrix * get_identity_matrix(int n) {
    matrix * v = initialise_matrix(1, n);
    elem_matrix_operation(&fill_matrix, v, 1);

    matrix * m = get_diag_matrix(v);
    destroy_matrix(v);

    return m;
}

pos get_max(matrix * m) {
    pos max;
    max.value = 0;
    max.x = 0;
    max.y = 0;
    if(m != NULL) {
        for(int i = 0; i < get_rows(m); i++) {
            for(int j = 0; j < get_columns(m); j++) {
                elem e = get_matrix_member(m, i+1, j+1);
                if(e > max.value) {
                    max.value = e;
                    max.x = i+1;
                    max.y = j+1;
                }
            }
        }
    } else {
        fprintf(stderr, "Not valid matrix pointer\n");
    }
    return max;
}

pos get_min(matrix * m) {
    pos min;
    min.value = ELEM_MAX;
    min.x = 0;
    min.y = 0;
    if(m != NULL) {
        for(int i = 0; i < get_rows(m); i++) {
            for(int j = 0; j < get_columns(m); j++) {
                elem e = get_matrix_member(m, i+1, j+1);
                if(e < min.value) {
                    min.value = e;
                    min.x = i+1;
                    min.y = j+1;
                }
            }
        }
    } else {
        fprintf(stderr, "Not valid matrix pointer\n");
    }
    return min;
}

