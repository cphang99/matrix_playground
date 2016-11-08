#include "2D_matrix_ops.h"

static int square_element_test(matrix * m);
static int transpose_test(matrix * m);
static int vert_concat_test(matrix * m);
static int horiz_concat_test(matrix * m);

int main(void) {
    printf("Executing tests for 2D_matrix_ops.c\n");

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
    transpose_test(m);
    vert_concat_test(m);
    horiz_concat_test(m);

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

/*Tests whether all elements in the matrix are being transposed */
static int transpose_test(matrix * m) {
    printf("\nTransposing the result of this matrix\n");
    matrix * t_m = transpose_matrix(m);
    print_matrix(t_m);
    printf("number of rows =%d number of columns=%d\n",
            t_m->rows, t_m->columns);
    printf("member at loc 1,2 should be 16, is %d\n",
            get_matrix_member(t_m, 1, 2));
    printf("member at loc 2,2 should be 25, is %d\n",
            get_matrix_member(t_m, 2, 2));

    destroy_matrix(t_m);

    return 0;
}

/* Tests whether 2 matrices are being concatenated vertically */
static int vert_concat_test(matrix * m) {
    printf("\nVertically concatenating a null matrix\n");
    matrix * null_matrix = initialise_matrix(3, 2);
    matrix * v_combined;
    printf("Testing with two matrices of different heights...\n");
    v_combined = v_concatenate(null_matrix, m);

    printf("Testing with compatible matrices\n");
    matrix * t_m = transpose_matrix(m);
    v_combined = v_concatenate(null_matrix, t_m);
    print_matrix(v_combined);

    destroy_matrix(null_matrix);
    destroy_matrix(t_m);
    destroy_matrix(v_combined);

    return 0;
}

/* Tests whether 2 matrices are being concatenated horizontally */
static int horiz_concat_test(matrix * m) {
    printf("\nHorizontally concatenating a null matrix\n");
    matrix * null_matrix = initialise_matrix(3, 2);
    matrix * h_combined;
    printf("Testing with two matrices of different widths\n");
    h_combined = h_concatenate(null_matrix, m);

    printf("Testing with compatible matrices\n");
    matrix * t_m = transpose_matrix(m);
    h_combined = h_concatenate(null_matrix, t_m);
    print_matrix(h_combined);

    destroy_matrix(null_matrix);
    destroy_matrix(t_m);
    destroy_matrix(h_combined);

    return 0;
}
