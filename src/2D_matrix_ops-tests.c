#include "2D_matrix_ops.h"

static int transpose_test(matrix * m);
static int vert_concat_test(matrix * m);
static int horiz_concat_test(matrix * m);
static int create_row_vector_test(void);
static int get_horizontal_slice_test(matrix * m);
static int get_vertical_slice_test(matrix * m);
static int get_diag_matrix_test(void);

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

    transpose_test(m);
    vert_concat_test(m);
    horiz_concat_test(m);
    create_row_vector_test();
    get_horizontal_slice_test(m);
    get_vertical_slice_test(m);
    get_diag_matrix_test();

    destroy_matrix(m);
    return 0;

}

/*Tests whether all elements in the matrix are being transposed */
static int transpose_test(matrix * m) {
    printf("\nTransposing the result of this matrix\n");
    matrix * t_m = transpose_matrix(m);
    print_matrix(t_m);
    printf("number of rows =%d number of columns=%d\n",
            t_m->rows, t_m->columns);
    printf("member at loc 1,2 should be 4, is %d\n",
            get_matrix_member(t_m, 1, 2));
    printf("member at loc 2,2 should be 5, is %d\n",
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

/*Tests whether row vectors are being created correctly */
static int create_row_vector_test(void) {
    printf("\nTesting vertical vector creation\n");
    printf("1:10:1 -> 1,2,3,4,5,6,7,8,9,10\n");
    matrix * a = create_row_vector(1, 10, 1);
    print_matrix(a);
    printf("2:10:3 -> 2,5,8\n");
    matrix * b = create_row_vector(2, 10, 3);
    print_matrix(b);
    printf("4:9:6 -> 4\n");
    matrix * c = create_row_vector(4, 9, 6);
    print_matrix(c);
    printf("4:10:6 ->4,10\n");
    matrix * d = create_row_vector(4, 10, 6);
    print_matrix(d);

    printf("Checking if 1:10:1 can be transposed to a column vector\n");
    matrix * e = transpose_matrix(a);
    print_matrix(e);

    destroy_matrix(a);
    destroy_matrix(b);
    destroy_matrix(c);
    destroy_matrix(d);
    destroy_matrix(e);

    return 0;
}

/*Tests whether horizontal slices can be created of a matrix*/
static int get_horizontal_slice_test(matrix * m) {
    printf("\nTesting horizontal slice creation\n");
    matrix * a = get_horizontal_slice(m, 1);
    print_matrix(a);

    printf("Testing bounds testing of function\n");
    get_horizontal_slice(m, 0);
    get_horizontal_slice(m, 3);
    get_horizontal_slice(m, 5);

    destroy_matrix(a);
    return 0;
}


/*Tests whether vertical slices can be created of a matrix*/
static int get_vertical_slice_test(matrix * m) {
    printf("\nTesting vertical slice creation\n");
    matrix * a = get_vertical_slice(m, 2);
    print_matrix(a);

    printf("Testing bounds testing of function\n");
    get_vertical_slice(m, 0);
    get_vertical_slice(m, 5);

    destroy_matrix(a);
    return 0;
}

static int get_diag_matrix_test(void) {
    matrix * a = create_row_vector(1,5,1);
    matrix * b = transpose_matrix(a);
    printf("\nTesting diagonal matrix creation\n");
    printf("Matrices to apply:\n");
    print_matrix(a);
    print_matrix(b);

    printf("Diagonal matrices:\n");
    matrix * c = get_diag_matrix(a);
    matrix * d = get_diag_matrix(b);
    print_matrix(c);
    print_matrix(d);

    printf("Checking original matrices haven't been overwritten\n");
    print_matrix(a);
    print_matrix(b);

    destroy_matrix(a);
    destroy_matrix(b);
    destroy_matrix(c);
    destroy_matrix(d);

    return 0;
}
