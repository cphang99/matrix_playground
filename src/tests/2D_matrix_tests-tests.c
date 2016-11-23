#include <2D_matrix_tests.h>

static bool alwaysTrue(void);
static bool alwaysFalse(void);

int main(void) {
    test_suite * ts = initialise_test_suite(3,
            &alwaysTrue,
            &alwaysTrue,
            &alwaysFalse);
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
