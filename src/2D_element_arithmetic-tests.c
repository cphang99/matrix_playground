#include<2D_element_arithmetic.h>

static int pow_test(matrix * m);
static int mul_div_test(matrix *m);
static int fill_matrix_test(matrix * m);

int main(void) {
    printf("Executing tests for 2D_element_arithmetic.c\n");

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

    matrix * n = initialise_matrix(10, 10);
    pow_test(m);
    mul_div_test(m);
    fill_matrix_test(n);
    destroy_matrix(m);
    destroy_matrix(n);
    return 0;

}

/* Tests whether all elements in the matrix are being squared */
static int pow_test(matrix * m) {
    printf("\nCubing all elements in the matrix\n");
    printf("Before \n");
    print_matrix(m);
    elem_matrix_operation(&pow_elem, m, 3);
    printf("After\n");
    print_matrix(m);

    printf("Applying the third root to all elements in the matrix\n");
    elem_matrix_operation(&sqroot_elem, m, 3);
    print_matrix(m);

    return 0;
}

static int mul_div_test(matrix *m) {
    printf("\nMultiplying all elements in the matrix\n");
    printf("Before\n");
    print_matrix(m);
    elem_matrix_operation(&multiply_elem, m, 10);
    printf("After\n");
    print_matrix(m);

    printf("Dividing all elements by the same amount\n");
    elem_matrix_operation(&divide_elem, m, 10);
    print_matrix(m);

    return 0;
}

static int fill_matrix_test(matrix * m) {
    printf("\nFilling all elements in the matrix\n");
    printf("Before\n");
    print_matrix(m);
    elem_matrix_operation(&fill_matrix,m, 1);
    printf("After\n");
    print_matrix(m);
    printf("Number of rows=%d, number of columns=%d\n", m->rows, m->columns);

    return 0;
}


