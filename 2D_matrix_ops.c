#include "2D_matrix_ops.h"

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

int main(void) {
    int a[2][3] = {
        {1,2,3},
        {4,5,6}
    };

    matrix * m = initialise_matrix(2, 3);
    for(int i = 0; i < m->rows; i++) {
        for(int j = 0; j < m->columns; j++) {
            set_matrix_member(m, i+1, j+1, a[i][j]);
        }
    }

    print_matrix(m);
    elem_matrix_operation(&square, m);
    print_matrix(m);
    printf("number of rows =%d\n number of columns=%d\n", m->rows, m->columns);
    printf("member at loc 1,2 should be 4, is %d\n", get_matrix_member(m, 1, 2));
    printf("member at loc 2,3 should be 36, is %d\n", get_matrix_member(m, 2, 3));
    destroy_matrix(m);

    return 0;
}
