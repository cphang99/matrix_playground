/**
 * Matrix operations with a 10x10 array using flt point arithmetic
 *
 * Solves a 10x10 set of linear equations Ax=b for x, and verifies
 * the correct anwer by performing matrix multiplication on Ax to 
 * obtain b
 */

#include <matrix_playground.h>
int main(void) {
    elem m_arr[100] = {
        0.45999, 0.368591, 0.733466, 0.564988, 0.0224904, 0.316841, 0.149975, 0.117601, 0.0608477, 0.851927,
        0.759185, 0.482425, 0.343895, 0.814801, 0.374725, 0.950394, 0.0183772, 0.67062, 0.132944, 0.241773,
        0.589252, 0.895137, 0.0822144, 0.75625, 0.528986, 0.945164, 0.551733, 0.124207, 0.534853, 0.183334,
        0.227111, 0.717827, 0.937511, 0.754197, 0.589811, 0.471999, 0.675099, 0.188544, 0.915822, 0.828926,
        0.243419, 0.650505, 0.243168, 0.48131, 0.875163, 0.779523, 0.153562, 0.277674, 0.680894, 0.590871,
        0.0671058, 0.602715, 0.631214, 0.052105, 0.417842, 0.259904, 0.815354, 0.39371, 0.264348, 0.040776,
        0.843607, 0.735402, 0.54283, 0.847712, 0.824925, 0.786368, 0.250344, 0.388107, 0.0563698, 0.388194,
        0.955887, 0.330694, 0.663787, 0.454994, 0.0228052, 0.129886, 0.978378, 0.35438, 0.931411, 0.832259,
        0.625139, 0.393228, 0.333586, 0.0944345, 0.273057, 0.491691, 0.859375, 0.391036, 0.478838, 0.0838936,
        0.0165175, 0.918821, 0.29051, 0.514424, 0.764801, 0.110096, 0.38746, 0.736958, 0.654654, 0.49845
         };
    elem x_arr[10] = {
     0.1,
     0.2,
     0.3,
     0.4,
     0.5,
     0.6,
     0.7,
     0.8,
     0.9,
     1.0
    };  

    //Matrices are initialised on the heap, which arrays pass to.
    //Please note that the array above is a 1D array. Shape the array
    //as you see it on the screen, and as long as it matches with 
    //the dimensions defined in initialise_matrix() and set_matrix_array()
    //all will be well.
    matrix * m = initialise_matrix(10,10);
    set_matrix_array(m, m_arr, 10, 10);
    matrix * x = initialise_matrix(10,1);
    set_matrix_array(x, x_arr, 10, 1);

    matrix * r = solve_matrix_eq(m, x);

    matrix * v = matrix_multiplication(m, r);
    printf("Matrix A = \n");
    print_matrix(m);

    printf("Matrix b = \n");
    print_matrix(x);

    printf("Solving for Matrix x (from Ax =b) = \n");
    print_matrix(r);

    printf("Verifying by multiplying matrices A and x\n");
    print_matrix(v);

    //Note that all matrices created must be destroyed as these
    //are created on the heap. In general, with the exception of
    //element operations (found in 2D_element_arithmetic.h) all
    //matrix operations generate a new copy. See the include files
    //for more details
    destroy_matrix(&x);
    destroy_matrix(&r);
    destroy_matrix(&m);
    destroy_matrix(&v);
    return 0;
}

