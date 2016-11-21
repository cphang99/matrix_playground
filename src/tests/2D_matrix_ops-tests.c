#include "2D_matrix_ops.h"

static int transpose_test(matrix * m);
static int vert_concat_test(matrix * m);
static int horiz_concat_test(matrix * m);
static int create_row_vector_test(void);
static int get_horizontal_slice_test(matrix * m);
static int get_vertical_slice_test(matrix * m);
static int get_diag_matrix_test(void);
static int null_matrix_tests(void);
static int set_matrix_array_test(void);
static int getMin_getMax_test(matrix * m);

int main(void) {
    printf("Executing tests for 2D_matrix_ops.c\n");

    int a[2][3] = {
        {1,2,3},
        {4,5,6}
    };

    matrix * m = initialise_matrix(2, 3);
    for(int i = 0; i < get_rows(m); i++) {
        for(int j = 0; j < get_columns(m); j++) {
            #ifdef FIXED
                elem val = fix16_from_int(a[i][j]);
            #else
                elem val = a[i][j];
            #endif
            set_matrix_member(m, i+1, j+1, val);
        }
    }
    matrix * b = initialise_matrix(3,3);

    transpose_test(m);
    vert_concat_test(m);
    horiz_concat_test(m);
    create_row_vector_test();
    get_horizontal_slice_test(b);
    get_vertical_slice_test(b);
    get_diag_matrix_test();
    null_matrix_tests();
    set_matrix_array_test();
    getMin_getMax_test(m);

    destroy_matrix(&m);
    destroy_matrix(&b);
    return 0;

}

/*Tests whether all elements in the matrix are being transposed */
static int transpose_test(matrix * m) {
    printf("\nTransposing the result of this matrix\n");
    matrix * t_m = transpose_matrix(m);
    print_matrix(t_m);
    printf("number of rows =%d number of columns=%d\n",
            get_rows(t_m), get_columns(t_m));
    #ifdef FIXED
        printf("member at loc 1,2 should be 4, is %"ELEM_F"\n",
                convert_fixed_member(t_m, 1, 2));
        printf("member at loc 2,2 should be 5, is %"ELEM_F"\n",
                convert_fixed_member(t_m, 2, 2));
    #else
        printf("member at loc 1,2 should be 4, is %"ELEM_F"\n",
                get_matrix_member(t_m, 1, 2));
        printf("member at loc 2,2 should be 5, is %"ELEM_F"\n",
                get_matrix_member(t_m, 2, 2));
    #endif

    destroy_matrix(&t_m);

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

    destroy_matrix(&null_matrix);
    destroy_matrix(&t_m);
    destroy_matrix(&v_combined);

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

    destroy_matrix(&null_matrix);
    destroy_matrix(&t_m);
    destroy_matrix(&h_combined);

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

    destroy_matrix(&a);
    destroy_matrix(&b);
    destroy_matrix(&c);
    destroy_matrix(&d);
    destroy_matrix(&e);

    return 0;
}

/*Tests whether horizontal slices can be created of a matrix*/
static int get_horizontal_slice_test(matrix * m) {
    printf("\nTesting horizontal slice creation\n");
    print_matrix(m);
    matrix * a = get_horizontal_slice(m, 1, 2);
    print_matrix(a);

    printf("Testing bounds testing of function\n");
    get_horizontal_slice(m, 0, 0);
    get_horizontal_slice(m, 1, 0);
    get_horizontal_slice(m, 5, 5);

    destroy_matrix(&a);
    return 0;
}


/*Tests whether vertical slices can be created of a matrix*/
static int get_vertical_slice_test(matrix * m) {
    printf("\nTesting vertical slice creation\n");
    print_matrix(m);
    matrix * a = get_vertical_slice(m, 2 ,3);
    print_matrix(a);

    printf("Testing bounds testing of function\n");
    get_vertical_slice(m, 2, 67);
    get_vertical_slice(m, 5, 5);

    destroy_matrix(&a);
    return 0;
}

/* Tests creation of diagonal matrices */
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

    printf("Testing identity matrix creation\n");
    matrix * e = get_identity_matrix(10);
    print_matrix(e);
    
    destroy_matrix(&a);
    destroy_matrix(&b);
    destroy_matrix(&c);
    destroy_matrix(&d);
    destroy_matrix(&e);

    return 0;
}

/**Tests whether for all relevant functions that invalid
 * matrix pointers are being treated correctly
 */
static int null_matrix_tests(void) {
    printf("\nTesting that null matrices are treated correctly " 
            "by all functions\n");
    matrix * m = NULL;
    printf("print_matrix\n");
    print_matrix(m);
    printf("destroy_matrix\n");
    destroy_matrix(&m);
    printf("get_matrix_member\n");
    get_matrix_member(m, 0 ,0);
    printf("set_matrix_member\n");
    set_matrix_member(m, 0, 0, 0);
    printf("transpose_matrix\n");
    transpose_matrix(m);
    printf("v_concatentate\n");
    v_concatenate(m, m);
    printf("h_concatenate\n");
    h_concatenate(m, m);
    printf("get_horizontal_slice\n");
    get_horizontal_slice(m, 0, 0);
    printf("get_vertical_slice\n");
    get_vertical_slice(m, 0, 0);
    printf("get_diag_matrix\n");
    get_diag_matrix(m);
    printf("get_rows\n");
    get_rows(m);
    printf("get_columns\n");
    get_columns(m);
    printf("set_matrix_array\n");
    set_matrix_array(m, NULL, 0, 0);
    printf("set_max\n");
    get_max(m);
    printf("get_min\n");
    get_min(m);


    return 0;
}

/* Tests array-wise assignment of a matrix */
static int set_matrix_array_test(void) {
    elem a[6] = {
         1,2,3,
         4,5,6
    };
    #ifdef FIXED
        for(int i = 0; i < 2; i++) {
            for(int j = 0; j < 3; j++) {
                a[i*3+j] = fix16_from_int(a[i*3+j]);
            }
        }
    #endif
    
    matrix * m = initialise_matrix(2, 3);
    matrix * n = initialise_matrix(10, 10);

    printf("\nTesting array wise copying to matrix struct\n");
    set_matrix_array(m, a, 2, 3);
    print_matrix(m);

    printf("Testing array copying that will fail due to "
        "incorrect matrix dims\n");
    set_matrix_array(n, a, 2, 3);
    
    destroy_matrix(&m);
    destroy_matrix(&n);

    return 0;
}

/* Tests the obtaining of  minimum, maximum values from a matrix */
static int getMin_getMax_test(matrix * m) {
    printf("\nTesting getMin() and getMax() functions\n");
    printf("matrix to be tested\n");
    print_matrix(m);
    pos max = get_max(m);
    pos min = get_min(m);
    #ifdef FIXED
        float val_max = fix16_to_float(max.value);
        float val_min = fix16_to_float(min.value);
    #else
        elem val_max = max.value;
        elem val_min = min.value;
    #endif
    printf("Max val %"ELEM_F " at pos %d %d \n", val_max, max.x, max.y);
    printf("Min val %"ELEM_F " at pos %d %d\n", val_min, min.x, min.y);

    return 0;
}
