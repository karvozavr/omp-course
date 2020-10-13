#include <iostream>
#include <fstream>
#include <vector>
#include <functional>
#include <omp.h>

static constexpr int ARRAY_SIZE = 10;

double integrate_simpson(std::function<double(double)> const &func, double a, double b, size_t n) {
    double integral = 0;
    double const h = (b - a) / (2 * n);

    #pragma omp parallel for reduction(+:integral)
    for (int i = 0; i <= 2 * n; ++i) {
        double const argument = a + h * i;
        double const f = func(argument);
        if (i % 2 == 0) {
            integral += f * 2;
        } else {
            integral += f * 4;
        }
    }

    integral *= h / 3;
    return integral;
}

double polynomial_function(double const x) {
    return 2.5 * x * x + 17.6 * x + 1;
}

int main(int argc, char **argv) {
    double integral = integrate_simpson(polynomial_function, 0, 9, 20);
    std::cout << integral << std::endl;

    return 0;
}
