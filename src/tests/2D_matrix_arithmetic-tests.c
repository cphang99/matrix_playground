#include <2D_matrix_arithmetic.h>
#include <2D_element_arithmetic.h>

int matrix_add_test(matrix * a, matrix * b);
int matrix_subtract_test(matrix * a, matrix * b);
int matrix_arithmetic_fail_test(void);
int matrix_multiply_test(matrix * a, matrix * b);
int matrix_interchange_test(void);
int matrix_row_addition_test(void);
int gauss_elimination_ppivot_test(void);
int null_matrix_tests(void);

int main(void) {
    elem a[2][3] = {
        {1,2,3},
        {4,5,6}
    };
    matrix * m = initialise_matrix(2, 3);
    for(int i = 0; i < get_rows(m); i++) { 
        for(int j = 0; j < get_columns(m); j++) {
            set_matrix_member(m, i+1, j+1, a[i][j]);
        }
    }

    elem b[2][3] = {
        {1,2,3},
        {4,5,6}
    };
    matrix * n = initialise_matrix(2, 3);
    for(int i = 0; i < get_rows(n); i++) { 
        for(int j = 0; j < get_columns(n); j++) {
            set_matrix_member(n, i+1, j+1, b[i][j]);
        }
    }

    matrix_add_test(m, n);
    matrix_subtract_test(m,n);
    matrix_arithmetic_fail_test();
    matrix_multiply_test(m,n);
    matrix_interchange_test();
    matrix_row_addition_test();
    gauss_elimination_ppivot_test();
    null_matrix_tests();

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

int matrix_interchange_test(void) {
    printf("\nTesting matrix_interchanages\n");
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

    destroy_matrix(a);
    destroy_matrix(b);
    destroy_matrix(c);
    destroy_matrix(d);
    destroy_matrix(e);

    return 0;
}

int matrix_row_addition_test(void) {
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

    printf("Testing erroneous input: one row = -1\n");
    row_addition(e, 1, -1, 10, 10);

    destroy_matrix(a);
    destroy_matrix(b);
    destroy_matrix(c);
    destroy_matrix(d);
    destroy_matrix(e);

    return 0;
}

int gauss_elimination_ppivot_test(void) {
    printf("\nTesting gauss elimination with partial pivot:1\n");
    elem a_arr[9] = {
        3, 2, -4,
        2, 3, 3,
        5, -3, 1
    };

    elem v_arr[3] = {
        3,
        15,
        14
    };
    
    matrix * a = initialise_matrix(3,3);
    matrix * v = initialise_matrix(3,1);
    set_matrix_array(a, a_arr, 3, 3);
    set_matrix_array(v, v_arr, 3, 1);
    print_matrix(a);
    print_matrix(v);
    
    matrix * a_m = gauss_elimination_ppivot(a, v, true);
    print_matrix(a_m);
    matrix * a_m_rev = gauss_elimination_ppivot(a, v, false);
    print_matrix(a_m_rev);

    destroy_matrix(a);
    destroy_matrix(v);
    destroy_matrix(a_m);
    destroy_matrix(a_m_rev);

    printf("\nTesting gauss elimination with partial pivot:2\n");
    elem c_arr[16] = {
        1, -3, 2, 1,
        2, -6, 1, 4,
        -1, 2, 3, 4,
        0, -1, 1, 1
    };
    
    elem d_arr[4] = {
        -4,
        1,
        12,
        0
    };
    matrix * c = initialise_matrix(4,4);
    matrix * d = initialise_matrix(4,1);
    set_matrix_array(c, c_arr, 4, 4);
    set_matrix_array(d, d_arr, 4, 1);
    print_matrix(c);
    print_matrix(d);

    matrix * b_m = gauss_elimination_ppivot(c, d, true);
    print_matrix(b_m);
    matrix * b_m_rev = gauss_elimination_ppivot(c, d, false);
    print_matrix(b_m_rev);

    printf("\nTesting for incorrect matrix size being used\n");
    matrix * e = initialise_matrix(4,2);
    gauss_elimination_ppivot(c, e, true);

    destroy_matrix(c);
    destroy_matrix(d);
    destroy_matrix(e);
    destroy_matrix(b_m);
    destroy_matrix(b_m_rev);
    
    return 0;
}

int null_matrix_tests(void) {
    printf("\ntesting that null matrices are treated correctly\n");
    matrix * m = NULL;
    gauss_elimination_ppivot(m, m, true);

    return 0;
}
