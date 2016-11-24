#include<assert_methods.h>

#ifdef FLOAT
static bool compare_float(float a, float b);
#endif

bool compare_integers(int a, int b) {
    return a==b ? true : false;
}

bool compare_null(void * a) {
    return a==NULL ? true : false;
}

bool alwaysTrue(void) {
    return true;
}

bool alwaysFalse(void) {
    return false;
}

bool compare_matrices(matrix * a, matrix * b) {
    if( (get_rows(a) != get_rows(b)) || (get_columns(a) != get_columns(b))) {
        return false;
    } else {
        for(int i = 0; i < get_rows(a); i++) {
            for(int j = 0; j < get_columns(a); j++) {
                #ifdef FLOAT
                    if (!compare_float(get_matrix_member(a, i+1, j+1),
                            get_matrix_member(b, i+1, j+1))) {
                        return false;
                    }
                #else
                    if(get_matrix_member(a, i+1, j+1) !=
                         get_matrix_member(b, i+1, j+1)) {
                        return false;
                    }
                #endif
            }

        }
    }
    return true;
}

/*Only used if floating point values are employed
 * True if the same, false if not (within FLT_EPS value)
 */
#ifdef FLOAT
static bool compare_float(float a, float b) {
    return (fabsf(a-b) < FLT_EPS) ? 1 : 0;
}
#endif
