#include <2D_matrix_tests.h>

test_suite * _initialise_test_suite(int num_tests, ...) {
    va_list valist;
    int tests_added = 0;
    test_suite * ts = malloc(sizeof(test_suite));

    //To initialise the const member we need to cast to non-const
    #pragma GCC diagnostic ignored "-Wcast-qual"
    *(int*)&(ts->num_tests) = num_tests;
    ts->suite_outcome = 0;
    ts->tests_passed = 0;
    ts->tests_failed=0;
    ts->tests = malloc(num_tests * sizeof(test));
    va_start(valist, num_tests);
    for(int i = 0; i < num_tests; i++) {
        test t =  va_arg(valist, test);
        if(t.t_func != NULL) {
            ts->tests[i] = t;
            tests_added++;
        } else {
            break;
        }
    }
    va_end(valist);
    if(tests_added != num_tests) {
        destroy_test_suite(&ts);
        fprintf(stderr, "Number of tests added (%d) do not match "
                "the number of tests indicated (%d). Abort\n",
                tests_added, num_tests);
        exit(1);
    }
    return ts;
}

int run_test_suite(test_suite * ts) {
    if(ts != NULL) {
        for(int i = 0; i < ts->num_tests; i++) {
            printf("-------------------------------------\n");
            printf("Running test %s...\n", ts->tests[i].name);
            if((*(ts->tests[i].t_func))()) {
                printf("Test %s passed\n", ts->tests[i].name);
                (ts->tests_passed)++;
            } else {
                printf("Test %s failed\n", ts->tests[i].name);
                (ts->tests_failed)++;
            }
            printf("-------------------------------------\n");
        }
        return ts->suite_outcome = (ts->tests_failed ? 1 : 0);
    } else {
        fprintf(stderr, "No valid test_suite to run\n");
        return 1;
    }
}

void print_outcome(test_suite * ts) {
    if(ts != NULL) {
        printf("Outcome = %s Tests passed = %d, Tests Failed = %d\n",
                ts->suite_outcome == 0 ? "SUCCESS" : "FAIL", 
                ts->tests_passed, ts->tests_failed);
    } else {
        fprintf(stderr, "No valid test_suite print_outcome\n");
    }
}

void destroy_test_suite(test_suite ** ts) {
    if(*ts != NULL) {
        free((*ts)->tests);
        (*ts)->tests = NULL;
        free(*ts);
        *ts = NULL;
    } else {
        fprintf(stderr, "No valid test_suite to destroy\n");
    }
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
