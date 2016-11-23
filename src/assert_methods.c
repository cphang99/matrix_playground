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

