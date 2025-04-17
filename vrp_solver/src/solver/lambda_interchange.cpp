//
// Created by petkovic on 16.04.25.
//

#include <solver/lambda_interchange.h>

void LambdaInterchange::solve() {
    for (auto &route: this->routes) {
        for (auto &neighbor_route: this->routes) {
            if (&route != &neighbor_route) {
                reconnectEdges(route, neighbor_route);
            }
        }
    }
}

void LambdaInterchange::reconnectEdges(Route &route, Route &neighbor_route) {
    auto nodes = route.getNodes();
    auto neighbor_nodes = neighbor_route.getNodes();
    uint8_t size = route.getSize();
    uint8_t neighbor_size = neighbor_route.getSize();
    uint8_t iterations = 0;
    bool improvement = true;

    while (improvement && iterations < MAX_ITERATIONS) {
        improvement = false;
        iterations++;

        for (uint8_t i = 1; i < size - 1; i++) {
            for (uint8_t j = 1; j < neighbor_size - 1; j++) {
                uint16_t start_own = nodes[i - 1];
                uint16_t end_own = nodes[i];
                uint16_t start_neighbor = neighbor_nodes[j];
                uint16_t end_neighbor = neighbor_nodes[j + 1];

                auto new_route = nodes;
                auto new_neighbor = neighbor_nodes;

                // inserting lambda2-nodes into new_route from neighbor
                for (uint8_t k = 0; k < 1; ++k) {
                    new_route[i + k] = neighbor_nodes[j + k];
                }

                // inserting lambda1-nodes into neighbor from nodes
                for (uint8_t k = 0; k < 1; ++k) {
                    new_neighbor[j + k] = nodes[i + k];
                }

                if (isFeasible(new_route) && isFeasible(new_neighbor)) {
                    double old_cost = getRouteCost(nodes) + getRouteCost(neighbor_nodes);
                    double new_cost = getRouteCost(new_route) + getRouteCost(new_neighbor);

                    if (new_cost < old_cost - 1e-6) {
                        // apply
                        nodes = new_route;
                        neighbor_nodes = new_neighbor;
                        improvement = true;
                        break;
                    }
                }
            }
            if (improvement) break;
        }
    }

    // update route
    route.setRoute(nodes);
    neighbor_route.setRoute(neighbor_nodes);
}

double LambdaInterchange::getRouteCost(const std::array<short, Route::MAX_COUNT_NODES_PER_ROUTE> &route) {
    double cost = 0.0;
    for (uint8_t i = 0; i < route.size() - 1 && route[i + 1] != -1; ++i) {
        cost += graph.getDistance(route[i], route[i + 1]);
    }
    return cost;
}

bool LambdaInterchange::isFeasible(const std::array<short, Route::MAX_COUNT_NODES_PER_ROUTE> &route) {
    uint16_t total = 0;
    for (const auto id: route) {
        if (id == -1) {
            break;
        }
        total += graph.getNode(id)->getQuantity();
    }
    return !vehicle.exceedsCapacity(total);
}
