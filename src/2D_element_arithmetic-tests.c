#include<2D_element_arithmetic.h>

static int square_element_test(matrix * m);
static int sq_root_test(matrix * m);
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

    square_element_test(m);
    sq_root_test(m);
    destroy_matrix(m);
    return 0;

}

/* Tests whether all elements in the matrix are being squared */
static int square_element_test(matrix * m) {
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

    return 0;
}

static int sq_root_test(matrix * m) {
    printf("\nApplying square element wise operations to the matrix\n");
    printf("Before \n");
    print_matrix(m);
    elem_matrix_operation(&sq_root, m);
    printf("After\n");
    print_matrix(m);
    printf("number of rows =%d number of columns=%d\n",
            m->rows, m->columns);
    printf("member at loc 1,2 should be 2, is %d\n",
            get_matrix_member(m, 1, 2));
    printf("member at loc 2,3 should be 6, is %d\n",
            get_matrix_member(m, 2, 3));

    return 0;
}



