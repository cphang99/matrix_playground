#include<2D_element_arithmetic.h>

matrix * elem_matrix_operation(int (*fp)(int), matrix * m ) {
    int i, j = 0;
    for(i = 0; i < m->rows; i++) {
        for(j =0; j < m->columns; j++) {
            m->arr[i*m->columns+j] =  (*fp)(m->arr[i*m->columns +j]);
        }
    }
    return m;
}

int square(int x) {
    return x * x;
}




