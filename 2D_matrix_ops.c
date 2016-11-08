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

matrix * transpose_matrix(matrix * m) {
    matrix * t_m = initialise_matrix(m->columns, m->rows);

    for(int i = 0; i < m->rows; i++) {
        for(int j = 0; j < m->columns; j++) {
            set_matrix_member(t_m, j+1, i+1, get_matrix_member(m, i+1, j+1));
        }
    }
    return t_m;
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

    printf("\nApplying square element wise operations to the matrix\n");
    printf("Before \n");
    print_matrix(m);
    elem_matrix_operation(&square, m);
    printf("After\n");
    print_matrix(m);
    printf("number of rows =%d number of columns=%d\n", m->rows, m->columns);
    printf("member at loc 1,2 should be 4, is %d\n", get_matrix_member(m, 1, 2));
    printf("member at loc 2,3 should be 36, is %d\n", get_matrix_member(m, 2, 3));

    printf("\nTransposing the result of this matrix\n");
    matrix * t_m = transpose_matrix(m);
    print_matrix(t_m);
    printf("number of rows =%d number of columns=%d\n", t_m->rows, t_m->columns);
    printf("member at loc 1,2 should be 16, is %d\n", get_matrix_member(t_m, 1, 2));
    printf("member at loc 2,2 should be 25, is %d\n", get_matrix_member(t_m, 2, 2));

    destroy_matrix(m);
    destroy_matrix(t_m);

    return 0;
}
