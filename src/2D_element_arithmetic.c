#include<2D_element_arithmetic.h>

matrix * elem_matrix_operation(elem (*fp)(elem, float), matrix * m, 
        float param) {
    int i, j = 0;
    for(i = 0; i < get_rows(m); i++) {
        for(j =0; j < get_columns(m); j++) {
            set_matrix_member(m, i+1, j+1, 
                    (*fp)(m->arr[i*get_columns(m) +j], param));
        }
    }
    return m;
}

matrix * sum_matrix(matrix * m, int dim) {
    matrix * s = NULL;
    if(dim < 1 || dim > 2) {
        printf("Invalid dimension given\n");
    } else {
        int dim1 = 0;
        int dim2 = 0;
        //Depending on the dimension that sum_matrix is taking
        //place we need to iterate in different directions
        if(dim == 1) {
            dim1 = get_columns(m);
            dim2 = get_rows(m);
            s = initialise_matrix(1, get_columns(m));
        } else {
            dim1 = get_rows(m);
            dim2 = get_columns(m);
            s = initialise_matrix(get_rows(m), 1);
        }
        //Similarly, we need to fetch and set the matrix members
        //differently depending on dim.
        int i = 0;
        for(i = 0; i < dim1; i++) {
            int sum = 0;
            for(int j = 0; j < dim2; j++) {
                if(dim == 1) {
                    sum += get_matrix_member(m, j+1, i+1);
                } else {
                    sum += get_matrix_member(m, i+1, j+1);
                }
            }

            if(dim == 1) {
                set_matrix_member(s, 1, i+1, sum);
            } else {
                set_matrix_member(s, i+1, 1, sum);
            }
        }
    }
    return s;
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



