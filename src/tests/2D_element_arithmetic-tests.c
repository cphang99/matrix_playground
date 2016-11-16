#include<2D_element_arithmetic.h>

static int pow_test(matrix * m);
static int mul_div_test(matrix *m);
static int fill_matrix_test(matrix * m);
static int sum_matrix_test(matrix * m);
static int elem_row_test(void);
static int elem_column_test(void);

int main(void) {
    printf("Executing tests for 2D_element_arithmetic.c\n");

    int a[2][3] = {
        {1,2,3},
        {4,5,6}
    };

    matrix * m = initialise_matrix(2, 3);
    for(int i = 0; i < get_rows(m); i++) { 
        for(int j = 0; j < get_columns(m); j++) {
            set_matrix_member(m, i+1, j+1, a[i][j]);
        }
    }

    matrix * n = initialise_matrix(10, 10);
    pow_test(m);
    mul_div_test(m);
    fill_matrix_test(n);


    int b[3][3] = {
        {1,3,2},
        {4,2,5},
        {6,1,4}
    };

    matrix * o = initialise_matrix(3, 3);
    for(int i = 0; i < get_rows(o); i++) { 
        for(int j = 0; j < get_columns(o); j++) {
            set_matrix_member(o, i+1, j+1, b[i][j]);
        }
    }
    sum_matrix_test(o);
    sum_matrix_test(m);
    elem_row_test();
    elem_column_test();

    destroy_matrix(&o);
    destroy_matrix(&m);
    destroy_matrix(&n);
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
    printf("Number of rows=%d, number of columns=%d\n", get_rows(m), get_columns(m));

    return 0;
}

static int sum_matrix_test(matrix * m) {
    printf("\nTesting a matrix sum in both dimensions\n");
    printf("Before\n");
    print_matrix(m);
    matrix * a = sum_matrix(m, 1);
    matrix * b = sum_matrix(m, 2);
    printf("After\n");
    print_matrix(a);
    print_matrix(b);

    destroy_matrix(&a);
    destroy_matrix(&b);

    return 0;
}

static int elem_row_test(void) {
    matrix * t = initialise_matrix(3, 3);
    printf("\nTesting elem_row_operation\n");
    printf("Before\n");
    print_matrix(t);
    elem_row_operation(&fill_matrix, t, 1 ,2, 1);
    printf("After row operations\n");
    print_matrix(t);

    destroy_matrix(&t);

    return 0;
}

static int elem_column_test(void) {
    matrix * t = initialise_matrix(3, 3);
    printf("\nTesting elem_column_operation\n");
    printf("Before\n");
    print_matrix(t);
    elem_column_operation(&fill_matrix, t, 1 ,2, 1);
    printf("After column operations\n");
    print_matrix(t);

    destroy_matrix(&t);

    return 0;
}



