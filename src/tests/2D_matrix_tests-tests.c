#include <2D_matrix_tests.h>

static bool alwaysTrue(void);
static bool alwaysFalse(void);
static bool test_suite_test(void);

int main(void) {
    test_suite * ts = initialise_test_suite(1,
            CREATE_TEST(test_suite_test));
    int outcome = run_test_suite(ts);
    print_outcome(ts);
    destroy_test_suite(&ts);
    return outcome;
}

static bool alwaysTrue(void) {
    return true;
}

static bool alwaysFalse(void) {
    return false;
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
