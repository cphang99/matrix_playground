#include <2D_matrix_tests.h>

test_suite initialise_test_suite(int num_tests, ...) {
    va_list valist;
    test_suite ts = {.num_tests = num_tests,
        .tests_passed = 0,
        .tests_failed = 0};
    ts.tests = malloc(num_tests * sizeof(test));
    va_start(valist, num_tests);
    for(int i = 0; i < num_tests; i++) {
        ts.tests[i] = va_arg(valist, test);
    }
    va_end(valist);
    return ts;
}

int run_test_suite(test_suite * ts) {
    for(int i = 0; i < ts->num_tests; i++) {
        (*(ts->tests[i]))() ? (ts->tests_passed)++ : (ts->tests_failed)++;
    }

    return ts->tests_failed == 0 ? 0 : 1;
}

void destroy_test_suite(test_suite * ts) {
    free(ts->tests);
    ts->tests = NULL;
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
