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
    printf("number of rows =%d number of columns=%d\n", 
            m->rows, m->columns);
    printf("member at loc 1,2 should be 4, is %d\n", 
            get_matrix_member(m, 1, 2));
    printf("member at loc 2,3 should be 36, is %d\n", 
            get_matrix_member(m, 2, 3));

    printf("\nTransposing the result of this matrix\n");
    matrix * t_m = transpose_matrix(m);
    print_matrix(t_m);
    printf("number of rows =%d number of columns=%d\n", 
            t_m->rows, t_m->columns);
    printf("member at loc 1,2 should be 16, is %d\n", 
            get_matrix_member(t_m, 1, 2));
    printf("member at loc 2,2 should be 25, is %d\n", 
            get_matrix_member(t_m, 2, 2));

    printf("\nVertically concatenating a null matrix\n");
    matrix * null_matrix = initialise_matrix(3, 2);
    matrix * v_combined;
    printf("Testing with two matrices of different heights...\n");
    v_combined = v_concatenate(null_matrix, m);

    printf("Testing with compatible matrices\n");
    v_combined = v_concatenate(null_matrix, t_m);
    print_matrix(v_combined);

    printf("\nHorizontally concatenating a null matrix\n");
    matrix * h_combined;
    printf("Testing with two matrices of different widths\n");
    h_combined = h_concatenate(null_matrix, m);

    printf("Testing with compatible matrices\n");
    h_combined = h_concatenate(null_matrix, t_m);
    print_matrix(h_combined);


    destroy_matrix(m);
    destroy_matrix(t_m);
    destroy_matrix(null_matrix);
    destroy_matrix(h_combined);
    destroy_matrix(v_combined);

    return 0;
}
