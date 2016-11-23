#include <2D_matrix_ops.h>
#include <assert_methods.h>
#include <stdarg.h>

typedef bool (*test_func)(void);

typedef struct {
    const char * name;
    test_func t_func;
} test;

#define CREATE_TEST(t_func) (test){#t_func, &t_func}

typedef struct {
    const int num_tests;
    int suite_outcome; // 0 indicates success, 1 indicates failure
    int tests_passed;
    int tests_failed;
    test * tests;
} test_suite;

/**
 * Initalises a test suite
 *
 * \param   num_tests   The number of tests to run in the test suite
 * \param   ...         Variable arguments indidcating the tests
 *                      in a test suite
 * \returns             A test_suite structure
 */
#define initialise_test_suite(num_tests, ...) \
    _initialise_test_suite(num_tests, __VA_ARGS__, (test){NULL, NULL});

/**
 * Initialises a test suite
 *
 * Designed to be run by calling the macro initialise_test_suite
 * which will append a NULL sentinel value to the variable
 * arguements for safety
 *
 * \param num_tests     The number of tests
 * \param ...           Variable arguments indidcating the tests
 *                      in a test suite
 * \return              A test_suite structure
 */
test_suite * _initialise_test_suite(int num_tests, ...);

/**
 * Runs a test suite
 *
 * \param   ts      The test suite
 * \returns         A int telling if all tests in the test suite were
 *                  successful (0) or if any were unsuccessful (1)
 */
int run_test_suite(test_suite * ts);

/**
 * Prints the outcome of the test_suite to the user
 *
 * Indicates the overall outcome, number of tests passed and failed.
 *
 * \param   ts      The test suite
 */
void print_outcome(test_suite * ts);

/**
 * Frees the memory allocated to a test suite
 *
 * \param ts        The test suite
 */
void destroy_test_suite(test_suite ** ts);

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
