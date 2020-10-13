#include <iostream>
#include <fstream>
#include <vector>
#include <omp.h>

static constexpr int ERROR_CODE_FAILED_TO_READ_FILE = 1;

void read_data_from_file(std::string const &filename, std::vector<double> &array) {
    std::fstream data_file(filename, std::ios_base::in);

    double number;
    while (data_file >> number) {
        array.push_back(number);
    }
}

double calculate_sum(std::vector<double> &data) {
    const size_t size = data.size();
    double sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < size; ++i) {
        sum += data[i];
    }
    return sum;
}

int main(int argc, char **argv) {
    std::vector<double> data;
    read_data_from_file("data.txt", data);

    const double sum = calculate_sum(data);
    std::cout << sum << std::endl;

    return 0;
}

