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

//We are ignoring this as x is only provided to fufil the fp prototype
//in elem_matrix_operation
#pragma GCC diagnostic ignored "-Wunused-parameter"
elem fill_matrix(elem x, float p) {
    return (elem) p;
}

elem pow_elem(elem x, float p) {
    return (elem)floor(pow((float)x, p));
}

elem sqroot_elem(elem x, float p) {
    float r = (float)1 / p;
    return pow_elem(x, r);
}

elem multiply_elem(elem x, float p) {
    return x * p;
}

elem divide_elem(elem x, float p) {
    return (elem)floor((float)x / p);
}



