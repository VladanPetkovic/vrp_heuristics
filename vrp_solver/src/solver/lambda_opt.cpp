//
// Created by petkovic on 14.04.25.
//

#include <solver/lambda_opt.h>

void LambdaOpt::solve() {
    for (auto &route: this->routes) {
        reconnectEdges(route);
    }
}

int LambdaOpt::getIterations() const {
    return _iterations;
}

/**
 * In this function, we are looping to find the local optimum. (Strong local optimization)
 * Another version is: Controlled Search (find the best one) - used inside a metaheuristic
 * @param route the route to optimize
 */
void LambdaOpt::reconnectEdges(Route &route) {
    auto nodes = route.getNodes();
    uint8_t size = route.getSize();
    bool improvement = true;
    int iterations = 0;

    while (improvement && iterations < MAX_ITERATIONS) {
        improvement = false;
        iterations++;

        for (uint8_t i = 1; i < size - 2; i++) {
            for (uint8_t j = 1; j < size - 1; j++) {
                uint16_t start1 = nodes[i - 1];
                uint16_t end1 = nodes[i];
                uint16_t start2 = nodes[j];
                uint16_t end2 = nodes[j + 1];

                if (start1 != start2 && end1 != end2) {
                    double d1 = graph.getDistance(start1, end1) + graph.getDistance(start2, end2);
                    double d2 = graph.getDistance(start1, start2) + graph.getDistance(end1, end2);

                    if (d2 < d1 - 1e-6) {
                        // using a small threshold to avoid precision issues
                        std::reverse(nodes.begin() + i, nodes.begin() + j + 1);
                        improvement = true;
                        break;
                    }
                }
            }
            if (improvement) break;
        }
    }

    _iterations = iterations;

    // update route
    route.setRoute(nodes);
}
