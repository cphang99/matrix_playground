#include <matrix_playground.h>

int main(void) {
    float m_arr[36] = {
        0.343622, 0.734144, 0.488707, 0.381427, 0.74368, 0.230597,
        0.668181, 0.742611, 0.243255, 0.583696, 0.440894, 0.956143,
        0.321692, 0.390649, 0.701914, 0.37857, 0.412133, 0.313376,
        0.0818269, 0.89968, 0.315385, 0.228418, 0.324942, 0.598589,
        0.84194, 0.437208, 0.591353, 0.754164, 0.501769, 0.207125,
        0.140268, 0.165576, 0.884312, 0.383825, 0.0809907, 0.819016
    };
    matrix * m = initialise_matrix(6,6);
    set_fixed_array(m, m_arr, 6, 6);
    print_matrix(m);

    printf("Determinant = %.5f\n", get_determinant(m));
    matrix * m_inv = get_inverse(m);
    printf("Inverse = \n");
    print_matrix(m_inv);

    printf("Multiplying m and m_inv = \n");
    matrix * id = matrix_multiplication(m, m_inv);
    print_matrix(id);

    destroy_matrix(&m_inv);
    destroy_matrix(&id);
    destroy_matrix(&m);

    return 0;
}
