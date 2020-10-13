#include <iostream>
#include <fstream>
#include <vector>
#include <omp.h>

static constexpr int ARRAY_SIZE = 16000;

int main(int argc, char **argv) {
    std::vector<double> data(ARRAY_SIZE);
    std::vector<double> result(ARRAY_SIZE);

    #pragma omp parallel for
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        data[i] = static_cast<double>(i);
    }
    
    #pragma omp parallel for
    for (int i = 1; i < ARRAY_SIZE - 1; ++i) {
        result[i] = (data[i - 1] + data[i] + data[i + 1]) / 3.0; // it's just data[i], isn't it?
    }

    for (double x : result) {
        std::cout << x << ' ';
    }

    std::cout << std::endl;

    return 0;
}

