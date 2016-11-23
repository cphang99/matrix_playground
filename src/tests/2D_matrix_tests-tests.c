#include <2D_matrix_tests.h>

static bool test_suite_test(void);
static bool compare_null_test(void);

int main(void) {
    test_suite * ts = initialise_test_suite(2,
            CREATE_TEST(test_suite_test),
            CREATE_TEST(compare_null_test));
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
