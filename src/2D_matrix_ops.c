#include <2D_matrix_ops.h>

int square(int x) {
    return x * x;
}

matrix * initialise_matrix(int rows, int columns) {
    matrix * a = malloc(sizeof(matrix) + (rows * columns * sizeof(int)));
    memset(a, 0, sizeof(matrix) + (rows * columns * sizeof(int)));
    a->rows = rows;
    a->columns = columns;

    return a;
}

matrix * elem_matrix_operation(int (*fp)(int), matrix * m ) {
    int i, j = 0;
    for(i = 0; i < m->rows; i++) {
        for(j =0; j < m->columns; j++) {
            m->arr[i*m->columns+j] =  (*fp)(m->arr[i*m->columns +j]);
        }
    }
    return m;
}

int get_matrix_member(matrix * m, int x, int y) {
    return m->arr[ (x-1)* m->columns +(y-1)];
}

matrix * set_matrix_member(matrix * m, int x, int y, int val) {
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

