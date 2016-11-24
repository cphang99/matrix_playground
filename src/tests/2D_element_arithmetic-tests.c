#include<2D_element_arithmetic.h>
#include<2D_matrix_tests.h>

///////////////////////////////////////////////////
//Static allocation of resources for tests here

static matrix * get_m(void);
static matrix * get_m(void) {
    elem a[2][3] = {
        {1,2,3},
        {4,5,6}
    };

    matrix * m = initialise_matrix(2, 3);
    for(int i = 0; i < get_rows(m); i++) { 
        for(int j = 0; j < get_columns(m); j++) {
            #ifdef FIXED
                #ifdef FLOAT
                    elem val = fix16_from_float(a[i][j]);
                #else
                    elem val = fix16_from_int(a[i][j]);
                #endif
            #else
                elem val = a[i][j];
            #endif
            set_matrix_member(m, i+1, j+1, val);
        }
    }

    return m;
}
static matrix * get_o(void);
static matrix * get_o(void) {
    elem b[3][3] = {
        {1,3,2},
        {4,2,5},
        {6,1,4}
    };

    matrix * o = initialise_matrix(3, 3);
    for(int i = 0; i < get_rows(o); i++) { 
        for(int j = 0; j < get_columns(o); j++) {
            #ifdef FIXED
                #ifdef FLOAT
                    elem val = fix16_from_float(b[i][j]);
                #else
                    elem val = fix16_from_int(b[i][j]);
                #endif
            #else
                elem val = b[i][j];
            #endif
            set_matrix_member(o, i+1, j+1, val);
        }
    }

    return o;
}
////////////////////////////////////////////////////

static bool pow_test(void);
static bool mul_div_test(void);
static bool fill_matrix_test(void);
static bool sum_matrix_test(void);
static bool elem_row_test(void);
static bool elem_column_test(void);

int main(void) {
    test_suite * ts = initialise_test_suite(6,
            CREATE_TEST(pow_test),
            CREATE_TEST(mul_div_test),
            CREATE_TEST(fill_matrix_test),
            CREATE_TEST(sum_matrix_test),
            CREATE_TEST(elem_row_test),
            CREATE_TEST(elem_column_test));
    int outcome = run_test_suite(ts);
    print_outcome(ts);
    destroy_test_suite(&ts);
    return outcome;
}

/* Tests whether all elements in the matrix are being squared */
static bool pow_test(void) {
    matrix * m = get_m();
    printf("Cubing all elements in the matrix\n");
    printf("Before \n");
    print_matrix(m);
    elem_matrix_operation(&pow_elem, m, 3);
    printf("After\n");
    print_matrix(m);
    matrix * res = initialise_matrix(2,3);
    elem res_arr[6] = {
        1,8,27,
        64,125,216
    };
    set_matrix_array(res, res_arr, 2, 3);
    bool outcome1 = compare_matrices(res, m);
    destroy_matrix(&res);

    printf("Applying the third root to all elements in the matrix\n");
    #ifndef FIXED
        elem_matrix_operation(&sqroot_elem, m, 3);
        elem res_arr2[6] = {
            1,2,3,
            4,5,6
        };
        matrix * res2 = initialise_matrix(2,3);
        set_matrix_array(res2, res_arr2, 2, 3);
        bool outcome2 = compare_matrices(res2, m);
        destroy_matrix(&res2);
    #else
        fprintf(stderr, "Square roots only supported with fixed vals "
                "Ignoring test\n");
        bool outcome2 = true;
    #endif

    print_matrix(m);
    destroy_matrix(&m);

    return outcome1 && outcome2;
}

static bool mul_div_test(void) {
    matrix * m = get_m();
    printf("Multiplying all elements by 10\n");
    printf("Before\n");
    print_matrix(m);
    elem_matrix_operation(&multiply_elem, m, 10);
    printf("After\n");
    print_matrix(m);
    matrix * res = initialise_matrix(2,3);
    elem res_arr[6] = {
        10,20,30,
        40,50,60
    };
    set_matrix_array(res, res_arr, 2, 3);
    bool outcome1 = compare_matrices(res, m);
    destroy_matrix(&res);

    printf("Dividing all elements by the same amount\n");
    elem_matrix_operation(&divide_elem, m, 10);
    elem res_arr2[6] = {
        1,2,3,
        4,5,6
    };
    matrix * res2 = initialise_matrix(2,3);
    set_matrix_array(res2, res_arr2, 2, 3);
    bool outcome2 = compare_matrices(res2, m);
    destroy_matrix(&res2);
    print_matrix(m);
    destroy_matrix(&m);

    return outcome1 && outcome2;
}

static bool fill_matrix_test(void) {
    matrix * m = initialise_matrix(3,3);
    printf("Before\n");
    print_matrix(m);
    elem_matrix_operation(&fill_matrix,m, 1);
    printf("After\n");
    print_matrix(m);
    elem res_arr[9] = {
        1,1,1,
        1,1,1,
        1,1,1
    };
    matrix * res = initialise_matrix(3,3);
    set_matrix_array(res, res_arr, 3, 3);
    bool outcome1 = compare_matrices(res, m);
    destroy_matrix(&res);

    printf("Number of rows=%d, number of columns=%d\n", get_rows(m), get_columns(m));
    bool outcome2 = compare_integers(get_rows(m), 3);
    bool outcome3 = compare_integers(get_columns(m), 3);
    destroy_matrix(&m);
    return outcome1 && outcome2 && outcome3;
}

static bool sum_matrix_test(void) {
    matrix * o = get_o();
    printf("Before\n");
    print_matrix(o);
    matrix * a = sum_matrix(o, 1);
    matrix * b = sum_matrix(o, 2);
    printf("After\n");
    print_matrix(a);
    print_matrix(b);
    elem res_arr[3] = {
        11,6,11
    };
    matrix * res = initialise_matrix(1,3);
    set_matrix_array(res, res_arr, 1, 3);
    bool outcome1 = compare_matrices(res, a);
    destroy_matrix(&res);

    elem res_arr2[3] = {
        6,
        11,
        11
    };
    matrix * res2 = initialise_matrix(3,1);
    set_matrix_array(res2, res_arr2, 3, 1);
    bool outcome2 = compare_matrices(res2, b);
    destroy_matrix(&res2);

    destroy_matrix(&a);
    destroy_matrix(&b);
    destroy_matrix(&o);
    return outcome1 && outcome2;
}

static bool elem_row_test(void) {
    matrix * t = initialise_matrix(3, 3);
    printf("\nTesting elem_row_operation\n");
    printf("Before\n");
    print_matrix(t);
    elem_row_operation(&fill_matrix, t, 1 ,2, 1);
    printf("After row operations\n");
    print_matrix(t);
    elem res_arr[9] = {
        1,1,1,
        1,1,1,
        0,0,0
    };
    matrix * res = initialise_matrix(3,3);
    set_matrix_array(res, res_arr, 3, 3);
    bool outcome1 = compare_matrices(res, t);
    destroy_matrix(&res);

    destroy_matrix(&t);

    return outcome1;
}

static bool elem_column_test(void) {
    matrix * t = initialise_matrix(3, 3);
    printf("\nTesting elem_column_operation\n");
    printf("Before\n");
    print_matrix(t);
    elem_column_operation(&fill_matrix, t, 1 ,2, 1);
    printf("After column operations\n");
    print_matrix(t);
    elem res_arr[9] = {
        1,1,0,
        1,1,0,
        1,1,0
    };
    matrix * res = initialise_matrix(3,3);
    set_matrix_array(res, res_arr, 3, 3);
    bool outcome1 = compare_matrices(res, t);
    destroy_matrix(&res);

    destroy_matrix(&t);

    return outcome1;
}



