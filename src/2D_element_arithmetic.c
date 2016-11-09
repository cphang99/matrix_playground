#include<2D_element_arithmetic.h>

matrix * elem_matrix_operation(elem (*fp)(elem, float), matrix * m, 
        float param) {
    int i, j = 0;
    for(i = 0; i < m->rows; i++) {
        for(j =0; j < m->columns; j++) {
            set_matrix_member(m, i+1, j+1, 
                    (*fp)(m->arr[i*m->columns +j], param));
        }
    }
    return m;
}

elem pow_elem(elem x, float p) {
    return (elem)pow(x, p);
}

elem sqroot_elem(elem x, float p) {
    float r = (float)1 / p;
    return pow_elem(x, r);
}



