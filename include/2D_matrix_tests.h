#ifndef MATRIX_TESTS_H
#define MATRIX_TESTS_H

#include "2D_matrix_ops.h"
#include "assert_methods.h"
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
 *                  successful (0) or if any were unsuccessful (1), or
 *                  if the test_suite could not run due to incorrect
 *                  pointer (2).
 */
int run_test_suite(test_suite * ts);

/**
 * Prints the outcome of the test_suite to the user
 *
 * Indicates the overall outcome, number of tests passed and failed.
 *
 * \param   ts      The test suite
 * \return          True if successful. False if not
 *                  (if a NULL pointer is passed)
 */
bool print_outcome(test_suite * ts);

/**
 * Frees the memory allocated to a test suite
 *
 * \param ts        The test suite
 * \return          True if successful. False if not
 *                  (if a NULL pointer is passed)
 */
bool destroy_test_suite(test_suite ** ts);

#endif
