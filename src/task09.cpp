#include <iostream>
#include <vector>
#include <cassert>
#include <omp.h>

const size_t infinity = SIZE_MAX;

class SSSPSolver {
public:
    explicit SSSPSolver(const std::vector<std::vector<int>> &graph)
            : graph_(graph),
              visited_(graph.size(), 0),
              distance_(graph.size(), infinity) {}

    size_t solve(size_t start_vertex, size_t target_vertex) {
        distance_[start_vertex] = 0;

        #pragma omp parallel
        {
            dfs(start_vertex);
        }

        return distance_[target_vertex];
    }

private:
    void dfs(size_t vertex) {
        bool should_visit = false;

        #pragma omp critical
        if (!visited_[vertex]) {
            should_visit = true;
            visited_[vertex] = 1;
        }

        if (should_visit) {
            for (size_t other : graph_[vertex]) {
                #pragma omp critical
                if (distance_[other] > distance_[vertex] + 1) {
                    distance_[other] = distance_[vertex] + 1;
                }

                #pragma omp task
                dfs(other);
            }
        }
    }

    const std::vector<std::vector<int>> graph_;
    std::vector<size_t> visited_;
    std::vector<size_t> distance_;
};

std::vector<std::vector<int>> simple_graph = {
    {1, 2, 3},
    {4},
    {4},
    {2, 4},
    {}
};

int main(int argc, char **argv) {
    auto solver = SSSPSolver(simple_graph);
    assert(solver.solve(0, 4) == 2);
    return 0;
}
