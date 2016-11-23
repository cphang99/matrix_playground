#include <2D_matrix_tests.h>

static bool test_suite_test(void);
static bool compare_null_test(void);
static bool compare_matrices_equal_test(void);
static bool null_methods_test(void);

int main(void) {
    test_suite * ts = initialise_test_suite(4,
            CREATE_TEST(test_suite_test),
            CREATE_TEST(compare_null_test),
            CREATE_TEST(compare_matrices_equal_test),
            CREATE_TEST(null_methods_test));
    int outcome = run_test_suite(ts);
    print_outcome(ts);
    destroy_test_suite(&ts);
    return outcome;
}

static bool test_suite_test(void) {
    test_suite * ts = initialise_test_suite(3,
            CREATE_TEST(alwaysTrue),
            CREATE_TEST(alwaysTrue),
            CREATE_TEST(alwaysFalse));
    int outcome = run_test_suite(ts);
    print_outcome(ts);
    bool test_outcome = compare_integers(outcome, 1) &&
        compare_integers(ts->tests_passed, 2) &&
        compare_integers(ts->tests_failed, 1);
    destroy_test_suite(&ts);
    return test_outcome;
}

static bool compare_null_test(void) {
    test_suite * ts = NULL;
    test_suite * ts2 = initialise_test_suite(1,
            CREATE_TEST(alwaysTrue));
    bool outcome1 = compare_null(ts);
    bool outcome2 = !compare_null(ts2);
    destroy_test_suite(&ts2);
    return outcome1 && outcome2;
}

static bool compare_matrices_equal_test(void) {
    float a[9] = {
        1,2,3,
        4,5,6,
        7,8,9};
    float b[6] = {
        1,2,3,
        4,5,6};
    float c[9] = {
        1,2,3,
        4,5,6,
        7,8,9};
    float d[9] = {
        1,2,3,
        4,5,6,
        7,8,0};
    matrix * a_m = initialise_matrix(3,3);
    set_matrix_array(a_m, a, 3, 3);
    matrix * b_m = initialise_matrix(2,3);
    set_matrix_array(b_m, b, 2, 3);
    matrix * c_m = initialise_matrix(3,3);
    set_matrix_array(c_m, c, 3, 3);
    matrix * d_m = initialise_matrix(3,3);
    set_matrix_array(d_m, d, 3, 3);

    bool outcome1 = compare_matrices(a_m, a_m);
    bool outcome2 = !compare_matrices(a_m, b_m);
    bool outcome3 = compare_matrices(a_m, c_m);
    bool outcome4 = !compare_matrices(a_m, d_m);

    destroy_matrix(&a_m);
    destroy_matrix(&b_m);
    destroy_matrix(&c_m);
    destroy_matrix(&d_m);

    return outcome1 && outcome2 && outcome3 && outcome4;
}

static bool null_methods_test(void) {
    test_suite * ts = initialise_test_suite(10,
            CREATE_TEST(alwaysFalse));
    bool outcome1 = compare_null(ts);
    bool outcome2 = compare_integers(run_test_suite(ts), 2);
    bool outcome3 = !(print_outcome(ts));
    bool outcome4 = !(destroy_test_suite(&ts));
    return outcome1 && outcome2 && outcome3 && outcome4;
}
