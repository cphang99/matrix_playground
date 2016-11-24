#include "2D_matrix_ops.h"
#include <2D_matrix_tests.h>

///////////////////////////////////////////////////
//Static allocation of resources for tests here
//
static matrix * get_m(void);
static matrix * get_m(void) {
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
    return m;
}
////////////////////////////////////////////////////

static bool transpose_test(void);
static bool vert_concat_test(void);
static bool horiz_concat_test(void);
static bool create_row_vector_test(void);
static bool get_horizontal_slice_test(void);
static bool get_vertical_slice_test(void);
static bool get_diag_matrix_test(void);
static bool null_matrix_tests(void);
static bool set_matrix_array_test(void);
static bool getMin_getMax_test(void);

int main(void) {
    test_suite * ts = initialise_test_suite(10,
            CREATE_TEST(transpose_test),
            CREATE_TEST(vert_concat_test),
            CREATE_TEST(horiz_concat_test),
            CREATE_TEST(create_row_vector_test),
            CREATE_TEST(get_horizontal_slice_test),
            CREATE_TEST(get_vertical_slice_test),
            CREATE_TEST(get_diag_matrix_test),
            CREATE_TEST(null_matrix_tests),
            CREATE_TEST(set_matrix_array_test),
            CREATE_TEST(getMin_getMax_test));
    int outcome = run_test_suite(ts);
    print_outcome(ts);
    destroy_test_suite(&ts);
    return outcome;
}

/*Tests whether all elements in the matrix are being transposed */
static bool transpose_test(void) {
    matrix * m = get_m();
    matrix * t_m = transpose_matrix(m);
    print_matrix(t_m);
    printf("number of rows =%d number of columns=%d\n",
            get_rows(t_m), get_columns(t_m));
    bool outcome2 = compare_integers(3, get_rows(t_m));
    bool outcome3 = compare_integers(2, get_columns(t_m));
        
    matrix * res = initialise_matrix(3,2);
    elem res_arr[6] = {
        1,4,
        2,5,
        3,6
    };
    set_matrix_array(res, res_arr, 3, 2);
    bool outcome1 = compare_matrices(res, t_m);
    destroy_matrix(&res);

    destroy_matrix(&t_m);
    destroy_matrix(&m);

    return outcome1 && outcome2 && outcome3;
}

/* Tests whether 2 matrices are being concatenated vertically */
static bool vert_concat_test(void) {
    matrix * m = get_m();
    matrix * null_matrix = initialise_matrix(3, 2);
    matrix * v_combined;
    printf("Testing with two matrices of different heights...\n");
    v_combined = v_concatenate(null_matrix, m);
    bool outcome1 = compare_null(v_combined);

    printf("Testing with compatible matrices\n");
    matrix * t_m = transpose_matrix(m);
    v_combined = v_concatenate(null_matrix, t_m);
    print_matrix(v_combined);
    
    matrix * res = initialise_matrix(6,2);
    elem res_arr[12] = {
        0,0,
        0,0,
        0,0,
        1,4,
        2,5,
        3,6
    };
    set_matrix_array(res, res_arr, 6, 2);
    bool outcome2 = compare_matrices(res, v_combined);
    destroy_matrix(&res);

    destroy_matrix(&m);
    destroy_matrix(&null_matrix);
    destroy_matrix(&t_m);
    destroy_matrix(&v_combined);

    return outcome1 && outcome2;
}

/* Tests whether 2 matrices are being concatenated horizontally */
static bool horiz_concat_test(void) {
    matrix * m  = get_m();
    matrix * null_matrix = initialise_matrix(3, 2);
    matrix * h_combined;
    printf("Testing with two matrices of different widths\n");
    h_combined = h_concatenate(null_matrix, m);
    bool outcome1 = compare_null(h_combined);

    printf("Testing with compatible matrices\n");
    matrix * t_m = transpose_matrix(m);
    h_combined = h_concatenate(null_matrix, t_m);
    print_matrix(h_combined);
    matrix * res = initialise_matrix(3,4);
    elem res_arr[12] = {
        0,0,1,4,
        0,0,2,5,
        0,0,3,6
    };
    set_matrix_array(res, res_arr, 3, 4);
    bool outcome2 = compare_matrices(res, h_combined);

    destroy_matrix(&res);
    destroy_matrix(&null_matrix);
    destroy_matrix(&t_m);
    destroy_matrix(&h_combined);
    destroy_matrix(&m);

    return outcome1 && outcome2;
}

/*Tests whether row vectors are being created correctly */
static bool create_row_vector_test(void) {
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

    matrix * res1 = initialise_matrix(1,10);
    elem res_arr1[10] = {
        1,2,3,4,5,6,7,8,9,10
    };
    set_matrix_array(res1, res_arr1, 1, 10);
    bool outcome1 = compare_matrices(res1, a);
    destroy_matrix(&res1);

    matrix * res2 = initialise_matrix(1,3);
    elem res_arr2[3] = {
        2,5,8
    };
    set_matrix_array(res2, res_arr2, 1, 3);
    bool outcome2 = compare_matrices(res2, b);
    destroy_matrix(&res2);

    matrix * res3 = initialise_matrix(1,1);
    elem res_arr3[1] = {
        4
    };
    set_matrix_array(res3, res_arr3, 1, 1);
    bool outcome3 = compare_matrices(res3, c);
    destroy_matrix(&res3);

    matrix * res4 = initialise_matrix(1,2);
    elem res_arr4[2] = {
        4,10
    };
    set_matrix_array(res4, res_arr4, 1, 2);
    bool outcome4 = compare_matrices(res4, d);
    destroy_matrix(&res4);

    printf("Checking if 1:10:1 can be transposed to a column vector\n");
    matrix * e = transpose_matrix(a);
    print_matrix(e);

    matrix * res5 = initialise_matrix(10,1);
    elem res_arr5[10] = {
        1,
        2,
        3,
        4,
        5,
        6,
        7,
        8,
        9,
        10
    };
    set_matrix_array(res5, res_arr5, 10, 1);
    bool outcome5 = compare_matrices(res5, e);
    destroy_matrix(&res5);

    destroy_matrix(&a);
    destroy_matrix(&b);
    destroy_matrix(&c);
    destroy_matrix(&d);
    destroy_matrix(&e);

    return outcome1 && outcome2 && outcome3 && outcome4 && outcome5;
}

/*Tests whether horizontal slices can be created of a matrix*/
static bool get_horizontal_slice_test(void) {
    matrix * m = initialise_matrix(3,3);
    print_matrix(m);
    matrix * a = get_horizontal_slice(m, 1, 2);
    print_matrix(a);
    matrix * res = initialise_matrix(2,3);
    bool outcome1 = compare_matrices(res, a);

    printf("Testing bounds testing of function\n");
    bool outcome2 = compare_null(get_horizontal_slice(m, 0, 0));
    bool outcome3 = compare_null(get_horizontal_slice(m, 1, 0));
    bool outcome4 = compare_null(get_horizontal_slice(m, 5, 5));
    
    destroy_matrix(&res);
    destroy_matrix(&m);
    destroy_matrix(&a);
    return outcome1 && outcome2 && outcome3 && outcome4;
}


/*Tests whether vertical slices can be created of a matrix*/
static bool get_vertical_slice_test(void) {
    matrix * m = initialise_matrix(3,3);
    print_matrix(m);
    matrix * a = get_vertical_slice(m, 2 ,3);
    print_matrix(a);
    matrix * res = initialise_matrix(3,2);
    bool outcome1 = compare_matrices(res, a);

    printf("Testing bounds testing of function\n");
    bool outcome2 = compare_null(get_vertical_slice(m, 2, 67));
    bool outcome3 = compare_null(get_vertical_slice(m, 5, 5));

    destroy_matrix(&m);
    destroy_matrix(&res);
    destroy_matrix(&a);
    return outcome1 && outcome2 && outcome3;
}

/* Tests creation of diagonal matrices */
static bool get_diag_matrix_test(void) {
    matrix * a = create_row_vector(1,5,1);
    matrix * b = transpose_matrix(a);
    printf("Matrices to apply:\n");
    print_matrix(a);
    print_matrix(b);

    printf("Diagonal matrices:\n");
    matrix * c = get_diag_matrix(a);
    matrix * d = get_diag_matrix(b);
    print_matrix(c);
    print_matrix(d);

    matrix * res = initialise_matrix(5,5);
    elem res_arr[25] = {
        1,0,0,0,0,
        0,2,0,0,0,
        0,0,3,0,0,
        0,0,0,4,0,
        0,0,0,0,5
    };
    set_matrix_array(res, res_arr, 5, 5);
    bool outcome1 = compare_matrices(res, c);
    bool outcome2 = compare_matrices(res, d);
    destroy_matrix(&res);

    printf("Checking original matrices haven't been overwritten\n");
    print_matrix(a);
    print_matrix(b);

    matrix * res2 = initialise_matrix(5,1);
    elem res_arr2[5] = {
        1,
        2,
        3,
        4,
        5
    };
    set_matrix_array(res2, res_arr2, 5, 1);
    bool outcome3 = compare_matrices(res2, b);

    matrix * res3 = transpose_matrix(res2);
    bool outcome4 = compare_matrices(res3, a);
    destroy_matrix(&res2);
    destroy_matrix(&res3);


    printf("Testing identity matrix creation\n");
    matrix * e = get_identity_matrix(3);
    print_matrix(e);
    matrix * res4 = initialise_matrix(3,3);
    elem res_arr4[9] = {
        1,0,0,
        0,1,0,
        0,0,1
    };
    set_matrix_array(res4, res_arr4, 3, 3);
    bool outcome5 = compare_matrices(res4, e);
    destroy_matrix(&res4);
 
    destroy_matrix(&a);
    destroy_matrix(&b);
    destroy_matrix(&c);
    destroy_matrix(&d);
    destroy_matrix(&e);

    return outcome1 && outcome2 && outcome3 && outcome4 && outcome5;
}

/**Tests whether for all relevant functions that invalid
 * matrix pointers are being treated correctly
 */
static bool null_matrix_tests(void) {
    matrix * m = NULL;

    bool outcomes[15];
    printf("print_matrix\n");
    outcomes[0] = !print_matrix(m);
    printf("destroy_matrix\n");
    outcomes[1] = !destroy_matrix(&m);
    printf("get_matrix_member\n");
    outcomes[2] = compare_integers(0, get_matrix_member(m, 0 ,0));
    printf("set_matrix_member\n");
    outcomes[3] = compare_null(set_matrix_member(m, 0, 0, 0));
    printf("transpose_matrix\n");
    outcomes[4] = compare_null(transpose_matrix(m));
    printf("v_concatentate\n");
    outcomes[5] = compare_null(v_concatenate(m, m));
    printf("h_concatenate\n");
    outcomes[6] = compare_null(h_concatenate(m, m));
    printf("get_horizontal_slice\n");
    outcomes[7] = compare_null(get_horizontal_slice(m, 0, 0));
    printf("get_vertical_slice\n");
    outcomes[8] = compare_null(get_vertical_slice(m, 0, 0));
    printf("get_diag_matrix\n");
    outcomes[9] = compare_null(get_diag_matrix(m));
    printf("get_rows\n");
    outcomes[10] = compare_integers(0, get_rows(m));
    printf("get_columns\n");
    outcomes[11] = compare_integers(0, get_columns(m));
    printf("set_matrix_array\n");
    outcomes[12] = compare_null(set_matrix_array(m, NULL, 0, 0));
    printf("set_max\n");
    #ifdef FLOAT
        outcomes[13] = compare_float(ELEM_MIN, get_max(m).value);
    #else
        outcomes[13] = compare_integers((int)ELEM_MIN, (int)get_max(m).value);
    #endif
    printf("get_min\n");
    #ifdef FLOAT
        outcomes[14] = compare_float(ELEM_MAX, get_min(m).value);
    #else
        outcomes[14] = compare_integers((int)ELEM_MAX, (int)get_min(m).value);
    #endif

    bool final_outcome = true;
    for(int i = 0; i < 15; i++) {
        final_outcome *= outcomes[i];
        if(!outcomes[i]) {
            printf("null test %d failed\n", i);
        }
    }
    return final_outcome;
}

/* Tests array-wise assignment of a matrix */
static bool set_matrix_array_test(void) {
    elem a[6] = {
         1,2,3,
         4,5,6
    };
    
    matrix * m = initialise_matrix(2, 3);
    matrix * n = initialise_matrix(10, 10);
    matrix * o = get_m();

    set_matrix_array(m, a, 2, 3);
    print_matrix(m);
    bool outcome1 = compare_matrices(m, o);

    printf("Testing array copying that will fail due to "
        "incorrect matrix dims\n");
    bool outcome2 = compare_null(set_matrix_array(n, a, 2, 3));
    
    destroy_matrix(&m);
    destroy_matrix(&n);
    destroy_matrix(&o);

    return outcome1 && outcome2;
}

/* Tests the obtaining of  minimum, maximum values from a matrix */
static bool getMin_getMax_test(void) {
    matrix * m = get_m();
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
    bool outcome1 = compare_integers(1, (int)val_min);
    bool outcome2 = compare_integers(6, (int)val_max);
    printf("Max val %"ELEM_F " at pos %d %d \n", val_max, max.x, max.y);
    printf("Min val %"ELEM_F " at pos %d %d\n", val_min, min.x, min.y);
    destroy_matrix(&m);

    return outcome1 && outcome2;
}
