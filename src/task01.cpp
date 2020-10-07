#include <iostream>
#include <fstream>
#include <vector>
#include <omp.h>

static constexpr int ERROR_CODE_FAILED_TO_READ_FILE = 1;

int read_data_from_file(std::string const &filename, std::vector<double> &array) {
    std::fstream data_file(filename, std::ios_base::in);

    double number;
    while (data_file >> number) {
        array.push_back(number);
    }
    
    return 0;
}

void write_data_to_file(std::string const &filename, std::vector<double> &array) {
    std::fstream data_file(filename, std::ios_base::out);

    for (double value : array) {
        data_file << value << '\n';
    }
}

int read_arrays(
    std::string const &filename_a, 
    std::string const &filename_b, 
    std::vector<double> &a, 
    std::vector<double> &b
) {
    int result_a = read_data_from_file(filename_a, a);
    int result_b = read_data_from_file(filename_b, b);

    return result_a == 0 && result_b == 0 ? 0 : ERROR_CODE_FAILED_TO_READ_FILE;
}

double calculate_formula(double a_value, double b_value) {
    return a_value * a_value + b_value * b_value * b_value;
}

void calculate_c_data(std::vector<double> &a_data, std::vector<double> &b_data, std::vector<double> &c_data) {
    size_t size = std::min(a_data.size(), b_data.size());
    c_data.resize(size);

    #pragma omp parallel for
    for (int i = 0; i < size; ++i) {
        c_data[i] = calculate_formula(a_data[i], b_data[i]);
    }
 }

int main(int argc, char **argv) {
    // #pragma omp parallel
    // {
    //     printf("Hello, multithreaded: thread %d of %d\n", omp_get_thread_num(), omp_get_num_threads());
    // }
    if (argc != 3) {
        return 2;
    }

    std::vector<double> a_data, b_data, c_data;

    int result = read_arrays(argv[1], argv[2], a_data, b_data);
    if (result != 0) {
        return result;
    }

    calculate_c_data(a_data, b_data, c_data);
    write_data_to_file("c.txt", c_data);

    return 0;
}

