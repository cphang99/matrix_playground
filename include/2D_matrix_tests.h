#include <2D_matrix_ops.h>
#include <stdarg.h>

typedef bool (*test)(void);

typedef struct {
    const int num_tests;
    int tests_passed;
    int tests_failed;
    test * tests;
} test_suite;

/**
 * Initalises a test suite
 *
 * \param   num_tests   The number of tests to run in the test suite
 * \returns             A test_suite structure
 */
test_suite initialise_test_suite(int num_tests, ...);

/**
 * Runs a test suite
 *
 * \param   ts      The test suite
 * \returns         A int telling if all tests in the test suite were
 *                  successful (0) or if any were unsuccessful (1)
 */
int run_test_suite(test_suite * ts);

/**
 * Frees the memory allocated to a test suite
 *
 * \param ts        The test suite
 */
void destroy_test_suite(test_suite * ts);

/**
 * Determines whether two matrices are equal or not
 *
 * Matrices are equal iff dimensions of a == dimensions of b AND
 * if every value of a at coordinate (x,y) is equal to every value of b 
 * at coordinate (x,y)
 *
 * \param a     Matrix a
 * \param b     Matrix b
 * \returns     A boolean whether matrix a == matrix b
 */
bool are_matrices_equal(matrix * a, matrix * b);
