#include <2D_matrix_arithmetic.h>
#include <2D_element_arithmetic.h>
#include <2D_matrix_tests.h>

///////////////////////////////////////////////////
//Static allocation of resources for tests here

static matrix * init_m_from_a(void);
static matrix * init_m_from_a(void) {
    const elem a[2][3] = {
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

static matrix * init_n_from_b(void);
static matrix * init_n_from_b(void) {
    const elem b[2][3] = {
        {1,2,3},
        {4,5,6}
    };
    matrix * n = initialise_matrix(2, 3);
    for(int i = 0; i < get_rows(n); i++) { 
        for(int j = 0; j < get_columns(n); j++) {
            #ifdef FIXED
                #ifdef FLOAT
                    elem val = fix16_from_float(b[i][j]);
                #else
                    elem val = fix16_from_int(b[i][j]);
                #endif
            #else
                elem val = b[i][j];
            #endif
            set_matrix_member(n, i+1, j+1, val);
        }
    }
    return n;
}
////////////////////////////////////////////////////

bool matrix_add_test(void);
bool matrix_subtract_test(void);
bool matrix_arithmetic_fail_test(void);
bool matrix_multiply_test(void);
bool matrix_interchange_test(void);
bool matrix_row_addition_test(void);
bool LU_decomposition_test(void);
bool determinant_test(void);
bool eq_solver_test(void);
bool inv_det_test(void);

int main(void) {
    test_suite * ts = initialise_test_suite(10,
            CREATE_TEST(matrix_add_test),
            CREATE_TEST(matrix_subtract_test),
            CREATE_TEST(matrix_arithmetic_fail_test),
            CREATE_TEST(matrix_multiply_test),
            CREATE_TEST(matrix_interchange_test),
            CREATE_TEST(matrix_row_addition_test),
            CREATE_TEST(LU_decomposition_test),
            CREATE_TEST(determinant_test),
            CREATE_TEST(eq_solver_test),
            CREATE_TEST(inv_det_test));
    int outcome = run_test_suite(ts);
    print_outcome(ts);
    destroy_test_suite(&ts);
    return outcome;
}

bool matrix_add_test(void) {
    matrix * m = init_m_from_a();
    matrix * n = init_n_from_b();
    matrix * c = matrix_add(m,n);
    print_matrix(m);
    printf("+ \n");
    print_matrix(n);
    printf("= \n");
    print_matrix(c);

    matrix * res = initialise_matrix(2,3);
    elem res_arr[6] = {
        2,4,6,
        8,10,12
    };
    set_matrix_array(res, res_arr, 2, 3);
    bool outcome = compare_matrices(c, res);

    destroy_matrix(&c);
    destroy_matrix(&res);
    destroy_matrix(&m);
    destroy_matrix(&n);
    return outcome;
}


bool matrix_subtract_test(void) {
    matrix * m = init_m_from_a();
    matrix * n = init_n_from_b();
    matrix * c = matrix_subtract(m,n);
    print_matrix(m);
    printf("- \n");
    print_matrix(n);
    printf("= \n");
    print_matrix(c);

    matrix * res = initialise_matrix(2,3);
    bool outcome = compare_matrices(c, res);

    destroy_matrix(&c);
    destroy_matrix(&res);
    destroy_matrix(&m);
    destroy_matrix(&n);

    return outcome;
}

bool matrix_arithmetic_fail_test(void) {
    matrix * a = initialise_matrix(2,3);
    matrix * b = initialise_matrix(3,2);

    printf("Matrix add\n");
    bool outcome1 = compare_null(matrix_add(a,b));
    printf("Matrix subtract\n");
    bool outcome2 = compare_null(matrix_subtract(a,b));
    printf("Matrix multiply\n");
    bool outcome3 = compare_null(matrix_multiplication(a,a));

    destroy_matrix(&a);
    destroy_matrix(&b);
    return outcome1 && outcome2 && outcome3;
}

bool matrix_multiply_test(void) {
    matrix * m = init_m_from_a();
    matrix * n = init_n_from_b();
    matrix * b_t = transpose_matrix(n);
    matrix * c = matrix_multiplication(m,b_t);
    print_matrix(m);
    printf("* \n");
    print_matrix(b_t);
    printf("= \n");
    print_matrix(c);

    matrix * res = initialise_matrix(2,2);
    elem res_arr[6] = {
        14,32,
        32,77
    };
    set_matrix_array(res, res_arr, 2, 2);
    bool outcome = compare_matrices(c, res);


    destroy_matrix(&b_t);
    destroy_matrix(&c);
    destroy_matrix(&m);
    destroy_matrix(&n);
    destroy_matrix(&res);
    return outcome;
}

bool matrix_interchange_test(void) {
    matrix * a = create_row_vector(1,3,1);
    matrix * b = create_row_vector(4,6,1);
    matrix * c = create_row_vector(7,9,1);
    matrix * d = v_concatenate(a, b);
    matrix * e = v_concatenate(d, c);

    printf("Before row interchange\n");
    print_matrix(e);
    row_interchange(e, 1, 3);
    printf("After row interchange (rows 1 and 3) "
            "but before column interchange\n");
    print_matrix(e);
    column_interchange(e, 2, 3);
    printf("After column interchange (columns 2 and 3)\n");
    print_matrix(e);

    matrix * res = initialise_matrix(3,3);
    elem res_arr[9] = {
        7,9,8,
        4,6,5,
        1,3,2
    };
    set_matrix_array(res, res_arr, 3, 3);
    bool outcome = compare_matrices(e, res);

    destroy_matrix(&a);
    destroy_matrix(&b);
    destroy_matrix(&c);
    destroy_matrix(&d);
    destroy_matrix(&e);
    destroy_matrix(&res);

    return outcome;
}

bool matrix_row_addition_test(void) {
    printf("\nTesting matrix_interchanages\n");
    matrix * a = create_row_vector(1,3,1);
    matrix * b = create_row_vector(4,6,1);
    matrix * c = create_row_vector(7,9,1);
    matrix * d = v_concatenate(a, b);
    matrix * e = v_concatenate(d, c);

    printf("Testing row addition: r3= 2*r1 + r3*2\n");
    print_matrix(e);
    row_addition(e, 1, 3, 2, 2);
    print_matrix(e);

    matrix * res = initialise_matrix(3,3);
    elem res_arr[9] = {
        1,2,3,
        4,5,6,
        16,20,24
    };
    set_matrix_array(res, res_arr, 3, 3);
    bool outcome1 = compare_matrices(e, res);

    printf("Testing erroneous input: one row = -1\n");
    row_addition(e, 1, -1, 10, 10);
    bool outcome2 = compare_matrices(e, res);

    destroy_matrix(&a);
    destroy_matrix(&b);
    destroy_matrix(&c);
    destroy_matrix(&d);
    destroy_matrix(&e);
    destroy_matrix(&res);

    return outcome1 && outcome2;
}

bool LU_decomposition_test(void) {
    printf("\nLU decomposition:1\n");
    elem a_arr[9] = {
        3, 2, -4,
        2, 3, 3,
        5, -3, 1
    };
    
    matrix * a = initialise_matrix(3,3);
    set_matrix_array(a, a_arr, 3, 3);
    print_matrix(a);
   
    printf("Result of LU decomposition\n");
    PLU_matrix_array * PLU_a = LU_decomposition(a);
    print_matrix(PLU_a->P);
    print_matrix(PLU_a->L);
    print_matrix(PLU_a->U);

    printf("Testing by multiplying matrices P, L and U\n");
    matrix * PL = matrix_multiplication(PLU_a->P, PLU_a->L);
    matrix * PLU_mat = matrix_multiplication(PL, PLU_a->U);
    printf("Determinant =%.2f\n", PLU_a->det);
    #if defined(FIXED) || defined(FLOAT)
        bool outcome = compare_integers(146, (int)ceil(PLU_a->det));
    #else
        fprintf(stderr, "LU decomposition cannot be performed on integer types "
                "use float or fixed types\n");
        bool outcome = true;
    #endif
    
    print_matrix(PLU_mat);

    destroy_matrix(&a);
    destroy_matrix(&PL);
    destroy_matrix(&PLU_mat);
    destroy_PLU(&PLU_a);
    fprintf(stderr, "Note that only determinants were only checked here\n");

    return outcome;
}

bool determinant_test(void) {
    elem a_arr[4] = {
        2, 5,
        7, 9
    };
    matrix * a = initialise_matrix(2,2);
    set_matrix_array(a, a_arr, 2, 2);
    float det1 = get_determinant(a);
    bool outcome1 = compare_integers(-17, (int)rintf(det1));
    printf("Determinant of matrix a: expected %d, got %d\n", -17, (int)rintf(det1));

    destroy_matrix(&a);

    elem b_arr[16] = {
        1,2,5,6,
        -9,5,-7,2,
        15,100,-9,32,
        1,2,3,4
    };
    matrix * b = initialise_matrix(4,4);
    set_matrix_array(b, b_arr, 4,4);
    float det2 = get_determinant(b);
    bool outcome2 = compare_integers(-1324, (int)rintf(det2));
    printf("Determinant of matrix a: expected %d, got %d\n", -1324, (int)rintf(det2));
    destroy_matrix(&b);

    bool outcome3 = compare_integers(0, (int)get_determinant(NULL));
    return outcome1 && outcome2 && outcome3;
}

bool eq_solver_test(void) {
    #if defined(FIXED) || defined(FLOAT)
        printf("Testing consistent matrix\n");
        elem a_arr[16] = {
            1,2,1,-1,
            3,2,4,4,
            4,4,3,4,
            2,0,1,5,
        };
        matrix * a = initialise_matrix(4,4);
        set_matrix_array(a, a_arr, 4,4);
        print_matrix(a);
        printf("*\n");
        elem b_arr[4] = {
            5,
            16,
            22,
            15
        };
        matrix * b = initialise_matrix(4,1);
        set_matrix_array(b, b_arr, 4, 1);
        print_matrix(b);
        matrix * c = solve_matrix_eq(a, b);

        elem res_arr[4] = {
            16,
            -6,
            -2,
            -3
        };
        matrix * res = initialise_matrix(4,1);
        set_matrix_array(res, res_arr, 4, 1);
        bool outcome = compare_matrices(c, res);
        printf("Solution =\n");
        print_matrix(c);
        destroy_matrix(&a);
        destroy_matrix(&b);
        destroy_matrix(&c);
        destroy_matrix(&res);

        printf("Testing inconsistent matrix\n");
        elem i_arr[9] = {
            3,2,-5,
            1,1,-2,
            5,3,-8
        };
        matrix * i = initialise_matrix(3,3);
        set_matrix_array(i, i_arr, 3,3);
        print_matrix(i);
        printf("*\n");
        elem i_res_arr[3] = {
            4,
            1,
            6
        };
        matrix * i_res = initialise_matrix(3,1);
        set_matrix_array(i_res, i_res_arr, 3, 1);
        print_matrix(i_res);
        matrix * i_outcome = solve_matrix_eq(i, i_res);
        bool outcome2 = compare_null(i_outcome);
        destroy_matrix(&i);
        destroy_matrix(&i_res);

        printf("Testing dependent matrix\n");
        elem d_arr[9] = {
            8,5,11,
            -1,-4,2,
            2,-1,5
        };
        matrix * d = initialise_matrix(3,3);
        set_matrix_array(d, d_arr, 3,3);
        print_matrix(d);
        printf("*\n");
        elem d_res_arr[3] = {
            30,
            3,
            12
        };
        matrix * d_res = initialise_matrix(3,1);
        set_matrix_array(d_res, d_res_arr, 3, 1);
        print_matrix(d_res);
        matrix * d_outcome = solve_matrix_eq(d, d_res);
        bool outcome3 = compare_null(d_outcome);
        destroy_matrix(&d);
        destroy_matrix(&d_res);
        return outcome && outcome2 && outcome3;
   #else
        fprintf(stderr, "Equation test not run for integer types\n");
        return true;
   #endif
}

bool inv_det_test(void) {
    #if defined(FLOAT) || defined (FIXED)
        printf("Testing invertible matrix\n");
        elem a_arr[16] = {
            1,2,1,-1,
            3,2,4,4,
            4,4,3,4,
            2,0,1,5,
        };
        matrix * a = initialise_matrix(4,4);
        set_matrix_array(a, a_arr, 4,4);
        print_matrix(a);
        matrix * a_inv = get_inverse(a);
        matrix * id = get_identity_matrix(4);
        matrix * id_create = matrix_multiplication(a, a_inv);
        bool outcome1 = compare_matrices(id, id_create);
        destroy_matrix(&a);
        destroy_matrix(&a_inv);
        destroy_matrix(&id);
        destroy_matrix(&id_create);

        printf("Testing non-invertable matrices\n");
        elem i_arr[9] = {
            3,2,-5,
            1,1,-2,
            5,3,-8
        };
        matrix * i = initialise_matrix(3,3);
        set_matrix_array(i, i_arr, 3,3);
        print_matrix(i);
        matrix * i_inv = get_inverse(i);
        bool outcome2 = compare_null(i_inv);
        destroy_matrix(&i_inv);
        destroy_matrix(&i);

        return outcome1 && outcome2;

    #else
        fprintf(stderr, "inv_det_test not run for integer types\n");
        return true;
    #endif
}
