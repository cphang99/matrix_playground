#include<assert_methods.h>

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
                if(get_matrix_member(a, i+1, j+1) !=
                        get_matrix_member(b, i+1, j+1)) {
                    return false;
                }
            }

        }
    }
    return true;
}
