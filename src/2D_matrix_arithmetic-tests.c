#include <2D_matrix_arithmetic.h>

int matrix_add_test(matrix * a, matrix * b);
int matrix_subtract_test(matrix * a, matrix * b);
int matrix_arithmetic_fail_test(void);
int matrix_multiply_test(matrix * a, matrix * b);

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

    int b[2][3] = {
        {1,2,3},
        {4,5,6}
    };
    matrix * n = initialise_matrix(2, 3);
    for(int i = 0; i < n->rows; i++) { 
        for(int j = 0; j < n->columns; j++) {
            set_matrix_member(n, i+1, j+1, b[i][j]);
        }
    }

    matrix_add_test(m, n);
    matrix_subtract_test(m,n);
    matrix_arithmetic_fail_test();
    matrix_multiply_test(m,n);

    destroy_matrix(m);
    destroy_matrix(n);
    return 0;
}

int matrix_add_test(matrix * a, matrix * b) {
    printf("\nTesting matrix add\n");
    matrix * c = matrix_add(a,b);
    print_matrix(a);
    printf("+ \n");
    print_matrix(b);
    printf("= \n");
    print_matrix(c);

    destroy_matrix(c);
    return 0;
}


int matrix_subtract_test(matrix * a, matrix * b) {
    printf("\nTesting matrix subtract\n");
    matrix * c = matrix_subtract(a,b);
    print_matrix(a);
    printf("- \n");
    print_matrix(b);
    printf("= \n");
    print_matrix(c);

    destroy_matrix(c);

    return 0;
}

int matrix_arithmetic_fail_test(void) {
    printf("\nTesting failure conditions of matrix arithmetic\n");
    matrix * a = initialise_matrix(2,3);
    matrix * b = initialise_matrix(3,2);

    printf("Matrix add\n");
    matrix_add(a,b);
    printf("Matrix subtract\n");
    matrix_subtract(a,b);
    printf("Matrix multiply\n");
    matrix_multiplication(a,a);

    destroy_matrix(a);
    destroy_matrix(b);
    return 0;
}

int matrix_multiply_test(matrix * a, matrix * b) {
    printf("\nTesting matrix multiply\n");
    matrix * b_t = transpose_matrix(b);
    matrix * c = matrix_multiplication(a,b_t);
    print_matrix(a);
    printf("* \n");
    print_matrix(b_t);
    printf("= \n");
    print_matrix(c);

    destroy_matrix(b_t);
    destroy_matrix(c);

    return 0;
}
