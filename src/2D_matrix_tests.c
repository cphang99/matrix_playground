#include <2D_matrix_tests.h>

test_suite initialise_test_suite(int num_tests) {
    test_suite ts = {.num_tests = num_tests,
        .tests_passed = 0,
        .tests_failed = 0};
    return ts;
}

bool are_matrices_equal(matrix * a, matrix * b) {
    if( (get_rows(a) != get_rows(b)) || (get_columns(a) != get_columns(b))) {
        return false;
    } else {
        for(int i = 0; i < get_rows(a); i++) {
            for(int j = 0; j < get_columns(a); j++) {
                if(get_matrix_member(a, i+1, j+1) != 
                        get_matrix_member(b, i+1, j+1)) {
                    return false;
                }
            }

        }
    }
    return true;
}
