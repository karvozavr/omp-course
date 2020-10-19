#include <iostream>
#include <vector>
#include <random>
#include<functional>
#include <omp.h>

const size_t array_size = 100000L;
const size_t cutoff = 10L;

std::size_t total_depth = 0L;

/*
 * Iterator-based quick sort implementation with the cut-off limit to the size of the array.
 * After the limit is reached, the array would be sorted single-threadedly.
 */
template<typename RAIterator, typename Predicate>
void quick_sort(RAIterator first_it, RAIterator last_it, Predicate compare) {
    if (first_it >= last_it) return;
    
    size_t size = 0L; 
    total_depth++;
    if ((size = std::distance(first_it, last_it)) > 0) {
        RAIterator left_it = first_it;
        RAIterator right_it = last_it;
        bool is_swapped_left = false;
        bool is_swapped_right = false;
        typename std::iterator_traits<RAIterator>::value_type pivot = *first_it;

        RAIterator forward_it = first_it + 1;
        while (forward_it <= right_it) {
            if (compare(*forward_it, pivot)) {
                is_swapped_left = true;
                std::iter_swap(left_it, forward_it);
                left_it++; forward_it++;
            } else if (compare(pivot, *forward_it)) {
                is_swapped_right = true;
                std::iter_swap(right_it, forward_it);
                right_it--;
            }

            else forward_it++;
        }

        if (size >= cutoff) {
            #pragma omp taskgroup
            {
                #pragma omp task untied mergeable
                if ((std::distance(first_it, left_it) > 0) && (is_swapped_left)) {
                    quick_sort(first_it, left_it - 1, compare);
                }

                #pragma omp task untied mergeable
                if ((std::distance(right_it, last_it) > 0) && (is_swapped_right)) {
                    quick_sort(right_it + 1, last_it, compare);
                }
            }
        } else {
            #pragma omp task untied mergeable
            {
                if ((std::distance(first_it, left_it) > 0) && is_swapped_left)
                    quick_sort(first_it, left_it - 1, compare);

                if ((std::distance(right_it, last_it) > 0) && is_swapped_right)
                    quick_sort(right_it + 1, last_it, compare);
            }
        }
    }
}

template<class RAIterator, class Predicate >
void parallel_sort(RAIterator first_it, RAIterator last_it, Predicate compare) {
    size_t pos = 0L; 
    size_t total_depth = 0L;
    
    #pragma omp parallel num_threads(8)
    #pragma omp master
    quick_sort(first_it, last_it - 1, compare);
}

std::default_random_engine generator;
std::uniform_int_distribution<int> distribution(0,array_size);
auto random_int = std::bind(distribution, generator);

int main(int argc, char **argv) {
    std::vector<int> data(array_size);

    for (int &elem : data) {
        elem = random_int();
    }

    parallel_sort(data.begin(), data.end(), [](int x1, int x2){ return x1 < x2; });

    for (int elem : data) {
        std::cout << elem << " ";
    }

    return 0;
}
