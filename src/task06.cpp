#include <iostream>
#include <vector>
#include <omp.h>

static constexpr int ARRAY_SIZE = 10;

template<typename T>
void mat_mult(
    T** const a, 
    T** const b, 
    T** result,
    size_t a_rows, 
    size_t a_cols, 
    size_t b_cols
) {
    #pragma omp parallel for
    for (int i = 0; i < a_rows; i++) {
        for (int j = 0; j < b_cols; j++) {
            result[i][j] = 0;
            for (int k = 0; k < a_cols; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

int main(int argc, char **argv) {
    int **a = new int *[10];
    int **b = new int *[5];
    int **result = new int*[12];

    for (int i = 0; i < 10; i++) {
        a[i] = new int[5];
        for (int j = 0; j < 5; j++) {
            a[i][j] = i + j;
        }
    }

    for (int i = 0; i < 5; i++) {
        b[i] = new int[12];
        for (int j = 0; j < 12; j++) {
            b[i][j] = i + j;
        }
    }

    for (int i = 0; i < 10; i++)
    {
        result[i] = new int[12];
    }
    
    mat_mult(a, b, result, 10, 5, 12);

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 12; j++) {
            std::cout << result[i][j] << ' ';
        }
        std::cout << std::endl;
    }

    return 0;
}
