//
// Created by petkovic on 21.04.25.
//

#include <solver/iterated_local_search.h>

IteratedLocalSearch::IteratedLocalSearch(Graph &graph, Vehicle &vehicle, std::list<Route> &r)
    : Solver(graph, vehicle, r),
      _savings_clark_wright(graph, vehicle, r),
      _inter_route_improvement(graph, vehicle, r),
      _lambda_opt(graph, vehicle, r) {
    setTemperature();
}

int IteratedLocalSearch::getIterations() const {
    return _iterations;
}

void IteratedLocalSearch::solve() {
    initSolution();
    auto best_solution = routes;
    auto current = routes;
    double best_solution_value = getTotalDistance(routes);
    uint16_t iterations_without_improvement = 0;
    uint16_t iterations_without_change = 0;

    for (_iterations = 0; _iterations < MAX_ITERATIONS; _iterations++) {
        // restart
        if (iterations_without_improvement > MAX_ITERATIONS_WITHOUT_IMPROVEMENT) {
            routes = best_solution;
            iterations_without_improvement = 0;
        }
        const uint8_t intensity = std::max(1, static_cast<int>(std::log10(_temperature + 1e-6))); // avoid log(0)
        shake(intensity);
        localSearch();

        auto new_solution_value = getTotalDistance(routes);
        if (new_solution_value < best_solution_value) {
            // save the best solution
            best_solution = routes;
            best_solution_value = new_solution_value;
            iterations_without_improvement = 0;
            iterations_without_change = 0;
        } else {
            iterations_without_improvement++;
            iterations_without_change++;
        }
        LogHelper::log(best_solution_value, new_solution_value, _temperature);
        // std::cout << best_solution_value << " " << new_solution_value << " " << _temperature << std::endl;

        // simulated annealing
        if (accept(current, new_solution_value)) {
            current = routes; // use the solution as 'current'
        } else {
            // reset routes
            routes = current; // don't continue with the newest solution
        }
        _temperature *= ALPHA;

        if (_temperature < MIN_TEMPERATURE && iterations_without_change > MAX_ITERATIONS_WITHOUT_IMPROVEMENT) {
            break;
        }
    }

    routes = best_solution;
}

void IteratedLocalSearch::initSolution() {
    _savings_clark_wright.solve();
    localSearch();
}

void IteratedLocalSearch::localSearch() {
    _lambda_opt.solve();
    _inter_route_improvement.solve();
}

/**
 * points to consider: TODO: shake routes with high cost more often
 */
void IteratedLocalSearch::shake(const uint8_t intensity) {
    for (uint8_t i = 0; i < intensity; ++i) {
        switch (rand() % 3) {
            case 1: randomInterMove();
                break;
            case 2: randomCrossExchange();
                break;
            default:
                randomIntraSwap();
        }
    }
}

/**
 * pick random route A; pick two random positions in A; swap customers
 */
void IteratedLocalSearch::randomIntraSwap() {
    for (auto &route: routes) {
        const auto route_size = route.getSize() - 1; // don't move depot
        if (route_size <= 2) {
            continue;
        }
        const uint8_t pos_one = std::max(1, rand() % route_size);
        const uint8_t pos_two = std::max(1, rand() % route_size);
        const short temp = route.getNodeIdAt(pos_two);

        if (pos_one != pos_two) {
            // intra swap
            route.setNodeIdAt(pos_two, route.getNodeIdAt(pos_one));
            route.setNodeIdAt(pos_one, temp);
        }
    }
}

/**
 * choose two different routes A and B; pick random customer from A; insert into random position in B (if allowed)
 */
void IteratedLocalSearch::randomInterMove() {
    for (auto &route: routes) {
        bool moved = false;
        for (uint8_t i = 0; !moved && i < routes.size(); i++) {
            Route &neighbor_route = getRoute(i);
            if (&route != &neighbor_route) {
                const auto route_size = route.getSize() - 1; // don't move depot
                const auto neighbor_route_size = neighbor_route.getSize() - 1; // don't move depot
                if (route_size <= 2 || neighbor_route_size <= 2) {
                    continue;
                }
                const uint8_t index_to_move = std::max(1, rand() % route_size);
                const uint8_t pos_to_insert = std::max(1, rand() % neighbor_route_size);

                const auto node_to_move = graph.getNode(route.getNodeIdAt(index_to_move));
                const uint16_t new_total_quantity =
                        neighbor_route.getTotalQuantity(graph) + node_to_move->getQuantity();

                if (!vehicle.exceedsCapacity(new_total_quantity)) {
                    // inter move
                    neighbor_route.insertNodeAt(pos_to_insert, node_to_move->getId());
                    route.removeNodeFrom(index_to_move);
                    moved = true;
                }
            }
        }
    }
}

// Select customer i from route A, and j from route B
// Swap their positions if capacity is not violated
void IteratedLocalSearch::randomCrossExchange() {
    for (auto &route: routes) {
        bool moved = false;
        for (uint8_t i = 0; !moved && i < routes.size(); i++) {
            Route &neighbor_route = getRoute(i);
            if (&route != &neighbor_route) {
                const auto route_size = route.getSize() - 1; // don't move depot
                const auto neighbor_route_size = neighbor_route.getSize() - 1; // don't move depot
                if (route_size <= 2 || neighbor_route_size <= 2) {
                    continue;
                }
                const uint8_t index_from_a = std::max(1, rand() % route_size);
                const uint8_t index_from_b = std::max(1, rand() % neighbor_route_size);

                const auto node_to_b = graph.getNode(route.getNodeIdAt(index_from_a));
                const auto node_to_a = graph.getNode(neighbor_route.getNodeIdAt(index_from_b));
                const uint16_t new_total_quantity_a =
                        route.getTotalQuantity(graph) + node_to_a->getQuantity() - node_to_b->getQuantity();
                const uint16_t new_total_quantity_b =
                        neighbor_route.getTotalQuantity(graph) + node_to_b->getQuantity() - node_to_a->getQuantity();

                if (!vehicle.exceedsCapacity(new_total_quantity_a) && !vehicle.exceedsCapacity(new_total_quantity_b)) {
                    // swap nodes
                    neighbor_route.setNodeIdAt(index_from_b, node_to_b->getId());
                    route.setNodeIdAt(index_from_a, node_to_a->getId());
                    moved = true;
                }
            }
        }
    }
}

bool IteratedLocalSearch::accept(std::list<Route> &current, double new_cost) const {
    double current_cost = getTotalDistance(current);
    if (new_cost <= current_cost) {
        return true; // always use better solutions
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    double relative_increase = (new_cost / current_cost) - 1.0;
    double prob = std::exp(-relative_increase / _temperature);

    return dis(gen) < prob;
}

void IteratedLocalSearch::setTemperature() {
    double summed_distance = 0;
    uint16_t number_of_nodes = graph.getNumNodes();

    for (uint16_t i = 1; i < number_of_nodes; i++) {
        for (uint16_t j = i + 1; j < number_of_nodes; j++) {
            summed_distance += graph.getDistance(i, j);
        }
    }

    avg_arc_cost = summed_distance / number_of_nodes;
    _temperature = std::min(MAX_TEMPERATURE, TEMPERATURE_FACTOR * avg_arc_cost);
}
