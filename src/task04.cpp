#include <iostream>
#include <fstream>
#include <vector>
#include <functional>
#include <omp.h>

static constexpr int ARRAY_SIZE = 10;

double integrate(std::function<double(double)> const &func, std::vector<double> const x_values_sorted) {
    double integral = 0;

    #pragma omp parallel for reduction(+:integral)
    for (int i = 1; i < x_values_sorted.size(); ++i) {
        double const argument = (x_values_sorted[i] + x_values_sorted[i - 1]) / 2;
        double const delta_x = x_values_sorted[i] - x_values_sorted[i - 1];
        integral += func(argument) * delta_x;
    }

    return integral;
}

double polynomial_function(double const x) {
    return 2.5 * x * x + 17.6 * x + 1;
}

int main(int argc, char **argv) {
    std::vector<double> x_values(ARRAY_SIZE);
    for (int i = 0; i < x_values.size(); ++i) {
        x_values[i] = static_cast<double>(i);
    }
    
    double integral = integrate(polynomial_function, x_values);
    std::cout << integral << std::endl;

    return 0;
}
