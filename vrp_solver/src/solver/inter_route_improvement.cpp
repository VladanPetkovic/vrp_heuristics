//
// Created by petkovic on 18.04.25.
//

#include <solver/inter_route_improvement.h>

void InterRouteImprovement::solve() {
    for (auto &route: this->routes) {
        for (auto &neighbor_route: this->routes) {
            if (&route != &neighbor_route) {
                reconnectEdges(route, neighbor_route);
            }
        }
    }
}

void InterRouteImprovement::reconnectEdges(Route &route, Route &neighbor_route) {
    auto nodes = route.getNodes();
    auto neighbor_nodes = neighbor_route.getNodes();
    uint8_t size = route.getSize();
    uint8_t neighbor_size = neighbor_route.getSize();
    uint8_t iterations = 0; // TODO: save iterations
    bool improvement = true;

    while (improvement && iterations < MAX_ITERATIONS) {
        improvement = false;
        iterations++;

        for (uint8_t lambda = 1; lambda <= MAX_LAMBDA && !improvement; ++lambda) {
            if (size < lambda + 1) break;

            for (uint8_t i = 1; i < size - lambda - 1 && !improvement; i++) {
                for (uint8_t j = 1; j < neighbor_size - lambda - 1 && !improvement; j++) {
                    trySwap(nodes, neighbor_nodes, i, j, lambda, improvement);

                    tryInsert(nodes, neighbor_nodes, i, j, lambda, improvement, size, neighbor_size);

                    // makes only sense for lambda = 1
                    // and when difference in nodes is not that high
                    if (lambda == 1 && i < j + 5 && j < i + 5) {
                        tryTwoOptStar(nodes, neighbor_nodes, i, j, improvement, size, neighbor_size);
                    }
                }
            }
            // TODO: check, if this is needed
            // if (improvement) {
            //     route.setRoute(nodes);
            //     neighbor_route.setRoute(neighbor_nodes);
            // }
        }
    }

    // update route
    route.setRoute(nodes);
    neighbor_route.setRoute(neighbor_nodes);
}

void InterRouteImprovement::trySwap(std::array<short, Route::MAX_COUNT_NODES_PER_ROUTE> &route,
                                    std::array<short, Route::MAX_COUNT_NODES_PER_ROUTE> &neighbor_route,
                                    uint8_t i, uint8_t j, uint8_t lambda, bool &improvement) {
    auto new_route = route;
    auto new_neighbor = neighbor_route;

    // inserting lambda neighbor-nodes
    for (uint8_t k = 0; k < lambda; ++k) {
        new_route[i + k] = neighbor_route[j + k];
    }

    // inserting lambda nodes-nodes
    for (uint8_t k = 0; k < lambda; ++k) {
        new_neighbor[j + k] = route[i + k];
    }

    if (isFeasible(new_route) && isFeasible(new_neighbor)) {
        double old_cost = getRouteCost(route) + getRouteCost(neighbor_route);
        double new_cost = getRouteCost(new_route) + getRouteCost(new_neighbor);

        if (new_cost < old_cost - 1e-6) {
            // apply
            route = new_route;
            neighbor_route = new_neighbor;
            improvement = true;
        }
    }
}

void InterRouteImprovement::tryInsert(std::array<short, Route::MAX_COUNT_NODES_PER_ROUTE> &route,
                                      std::array<short, Route::MAX_COUNT_NODES_PER_ROUTE> &neighbor_route,
                                      uint8_t i, uint8_t j, uint8_t lambda, bool &improvement,
                                      uint8_t &size, uint8_t &neighbor_size) {
    auto new_route = route;
    auto new_neighbor = neighbor_route;

    // making place for lambda nodes
    for (short k = size - 1 + lambda; k >= i; --k) {
        new_route[k] = new_route[k - lambda];
    }

    // inserting lambda neighbor-nodes
    for (uint8_t k = 0; k < lambda; ++k) {
        new_route[i + k] = neighbor_route[j + k];
    }

    // removing lambda neighbor-nodes
    for (uint8_t k = 0; k < neighbor_size; ++k) {
        new_neighbor[j + k] = new_neighbor[j + k + lambda];
    }

    if (isFeasible(new_route) && isFeasible(new_neighbor)) {
        double old_cost = getRouteCost(route) + getRouteCost(neighbor_route);
        double new_cost = getRouteCost(new_route) + getRouteCost(new_neighbor);

        if (new_cost < old_cost - 1e-6) {
            // apply
            route = new_route;
            neighbor_route = new_neighbor;
            size += lambda;
            neighbor_size -= lambda;
            improvement = true;
        }
    }
}

void InterRouteImprovement::tryTwoOptStar(std::array<short, Route::MAX_COUNT_NODES_PER_ROUTE> &route,
                                          std::array<short, Route::MAX_COUNT_NODES_PER_ROUTE> &neighbor_route,
                                          uint8_t i, uint8_t j, bool &improvement,
                                          uint8_t &size, uint8_t &neighbor_size) {
    auto new_route = route;
    auto new_neighbor = neighbor_route;

    // inserting neighbor-nodes after i
    for (uint8_t k = 0; k < neighbor_size; ++k) {
        new_route[i + k] = neighbor_route[j + k];
    }
    // filling left spaces with -1
    for (uint8_t k = neighbor_size; k < size; ++k) {
        new_route[i + k] = -1;
    }

    // inserting route-nodes after j
    for (uint8_t k = 0; k < size; ++k) {
        new_neighbor[j + k] = route[i + k];
    }
    for (uint8_t k = size; k < neighbor_size; ++k) {
        new_neighbor[j + k] = -1;
    }

    if (isFeasible(new_route) && isFeasible(new_neighbor)) {
        double old_cost = getRouteCost(route) + getRouteCost(neighbor_route);
        double new_cost = getRouteCost(new_route) + getRouteCost(new_neighbor);

        if (new_cost < old_cost - 1e-6) {
            // apply
            route = new_route;
            neighbor_route = new_neighbor;
            uint8_t size_temp = i + neighbor_size - j;
            neighbor_size = j + size - i;
            size = size_temp;
            improvement = true;
        }
    }
}

double InterRouteImprovement::getRouteCost(const std::array<short, Route::MAX_COUNT_NODES_PER_ROUTE> &route) const {
    double cost = 0.0;
    for (uint8_t i = 0; i < route.size() - 1 && route[i + 1] != -1; ++i) {
        cost += graph.getDistance(route[i], route[i + 1]);
    }
    return cost;
}

bool InterRouteImprovement::isFeasible(const std::array<short, Route::MAX_COUNT_NODES_PER_ROUTE> &route) const {
    uint16_t total = 0;
    for (const auto id: route) {
        if (id == -1) {
            break;
        }
        total += graph.getNode(id)->getQuantity();
    }
    return !vehicle.exceedsCapacity(total);
}

bool InterRouteImprovement::hasUniqueNodes(const std::array<short, Route::MAX_COUNT_NODES_PER_ROUTE> &new_route,
                                           const std::array<short, Route::MAX_COUNT_NODES_PER_ROUTE> &new_neighbor)
const {
    std::unordered_set<short> seen;
    const uint16_t departure_node = vehicle.getDepartureNode().getId();

    // inserting route-nodes
    for (const auto &node: new_route) {
        if (node != departure_node && node != -1) {
            if (!seen.insert(node).second) {
                return false; // duplicate found
            }
        }
    }

    // inserting neighbor-nodes
    for (const auto &node: new_neighbor) {
        if (node != departure_node && node != -1) {
            if (!seen.insert(node).second) {
                return false; // duplicate between routes
            }
        }
    }

    return true;
}
