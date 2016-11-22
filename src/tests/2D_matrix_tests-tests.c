#include <2D_matrix_tests.h>

static bool alwaysTrue(void);

int main(void) {
    test_suite ts = initialise_test_suite(1, &alwaysTrue);
    destroy_test_suite(&ts);
    return 0;
}

static bool alwaysTrue(void) {
    return true;
}
