#include <2D_matrix_ops.h>

matrix * initialise_matrix(int rows, int columns) {
    matrix * a = malloc(sizeof(matrix) + (rows * columns * sizeof(elem)));
    memset(a, 0, sizeof(matrix) + (rows * columns * sizeof(elem)));
    a->rows = rows;
    a->columns = columns;

    return a;
}

elem get_matrix_member(matrix * m, int x, int y) {
    return m->arr[ (x-1)* m->columns +(y-1)];
}

matrix * set_matrix_member(matrix * m, int x, int y, elem val) {
    m->arr[ (x-1) * m->columns + (y-1) ] = val;
    return m;
}

void print_matrix(matrix * m) {
    for(int i = 0; i < m->rows; i++) {
        for(int j = 0; j < m->columns; j++) {
            printf("%d ",m->arr[i*m->columns +j]);
        }
        putchar('\n');
    }
    putchar('\n');
}

void destroy_matrix(matrix * m) {
    free(m);
}

matrix * transpose_matrix(matrix * m) {
    matrix * t_m = initialise_matrix(m->columns, m->rows);

    for(int i = 0; i < m->rows; i++) {
        for(int j = 0; j < m->columns; j++) {
            set_matrix_member(t_m, j+1, i+1, get_matrix_member(m, i+1, j+1));
        }
    }
    return t_m;
}

matrix * h_concatenate(matrix * a, matrix * b) {

    matrix * a_b = NULL;
    if(a->rows != b->rows) {
        printf("Cannot vertically concatenate matrices of different heights\n");
    } else {
        a_b =  initialise_matrix(a->rows, (a->columns + b->columns));
        for(int i = 0; i < a_b->rows; i++) {
            for(int j_a = 0; j_a < a->columns; j_a++) {
                set_matrix_member(a_b, i+1, j_a+1, 
                        get_matrix_member(a, i+1, j_a+1));
            }
            for(int j_b = 0; j_b < b->columns; j_b++) {
                set_matrix_member(a_b, i+1, a->columns+j_b+1, 
                        get_matrix_member(b, i+1, j_b+1));
            }
        }
    }
    return a_b;

}

matrix * v_concatenate(matrix * a, matrix * b) {
    matrix * a_b = NULL;
    if(a->columns != b->columns) {
        printf("Cannot horizonatlly concatenate matrices of different widths\n");
    } else {
        a_b = initialise_matrix( (a->rows + b->rows), a->columns );
        for(int i_a = 0; i_a < a->rows; i_a++) {
            for(int j_a = 0; j_a < a_b->columns; j_a++) {
                set_matrix_member(a_b, i_a+1, j_a+1, 
                        get_matrix_member(a, i_a+1, j_a+1));
            }
        }

        for(int i_b = 0; i_b < b->rows; i_b++) {
            for(int j_b = 0; j_b < a_b->columns; j_b++) {
                set_matrix_member(a_b, a->rows+i_b+1, j_b+1, 
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

matrix * get_horizontal_slice(matrix * m, int r) {
    matrix * v = NULL;
    if(r > 0 && r <= m->rows) {
        v= initialise_matrix(1, m->columns);
        for(int i = 0; i < m->columns; i++) {
            set_matrix_member(v, 1, i+1, get_matrix_member(m, r, i+1));
        }
    } else {
        printf("Slice is out of matrix row bounds\n");
    }

    return v;
}

matrix * get_vertical_slice(matrix * m, int c) {
    matrix * v = NULL;
    if(c > 0 && c <= m->columns) {
        v= initialise_matrix(m->rows, 1);
        for(int i = 0; i < m->rows; i++) {
            set_matrix_member(v, i+1, 1, get_matrix_member(m, i+1, c));
        }
    } else {
        printf("Slice is out of matrix column bounds\n");
    }

    return v;
}

matrix * get_diag_matrix(matrix * v) {
    matrix * m = NULL;
    bool hasTransposed = false;
    if(v->rows > 1) {
        //Transpose if a column vector, so can treat equally
        //in the next step.
        m = initialise_matrix(v->rows, v->rows); 
        v = transpose_matrix(v);
        hasTransposed = true;
    } else {
        m = initialise_matrix(v->columns, v->columns);
    }
    for(int i = 0; i < v->columns; i++) {
        set_matrix_member(m, i+1, i+1, get_matrix_member(v, 1, i+1)); 
    }
    if(hasTransposed) destroy_matrix(v);

    return m;

}
