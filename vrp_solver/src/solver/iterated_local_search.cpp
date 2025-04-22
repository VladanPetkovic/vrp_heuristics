//
// Created by petkovic on 21.04.25.
//

#include <solver/iterated_local_search.h>

IteratedLocalSearch::IteratedLocalSearch(Graph &graph, Vehicle &vehicle, std::list<Route> &r)
    : Solver(graph, vehicle, r),
      _savings_clark_wright(graph, vehicle, r),
      _inter_route_improvement(graph, vehicle, r),
      _lambda_opt(graph, vehicle, r) {
}

int IteratedLocalSearch::getIterations() const {
    return _iterations;
}

void IteratedLocalSearch::solve() {
    initSolution();
    auto best_solution = routes;
    auto current = routes;
    double best_solution_value = getTotalDistance(routes);

    for (_iterations = 0; _iterations < MAX_ITERATIONS; _iterations++) {
        const uint8_t intensity = std::max(1, static_cast<int>(std::log10(temperature + 1e-6)));
        // small epsilon to avoid log(0)
        shake(intensity);
        localSearch();

        auto new_solution_value = getTotalDistance(routes);
        if (new_solution_value < best_solution_value) {
            // save the best solution
            best_solution = routes;
            best_solution_value = new_solution_value;
        }
        std::cout << best_solution_value << "\t" << new_solution_value << "\t" << temperature << std::endl;

        // simulated annealing
        if (accept(current, new_solution_value)) {
            current = routes; // use the solution as 'current'
        } else {
            // reset routes
            routes = current; // don't continue with the newest solution
        }
        temperature *= ALPHA;
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
        const auto route_size = route.getSize();
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
        route.setTotalQuantity(route.getTotalQuantity(graph));
    }
    for (auto &route: routes) {
        bool moved = false;
        for (uint8_t i = 0; !moved && i < routes.size(); i++) {
            Route &neighbor_route = getRoute(i);
            if (&route != &neighbor_route) {
                const auto route_size = route.getSize() - 1; // don't move depot
                const auto neighbor_route_size = neighbor_route.getSize() - 1; // don't move depot
                const uint8_t index_to_move = std::max(1, rand() % route_size);
                const uint8_t pos_to_insert = std::max(1, rand() % neighbor_route_size);

                const auto node_to_move = graph.getNode(route.getNodeIdAt(index_to_move));
                const double new_total_quantity = neighbor_route.getTotalQuantity() + node_to_move->getQuantity();

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
}

bool IteratedLocalSearch::accept(std::list<Route> &current, double new_cost) const {
    double current_cost = getTotalDistance(current);
    double delta = new_cost - current_cost;

    if (delta < 0) {
        return true; // always prefer better solutions
    }

    // accept maybe worse solutions
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    double prob = std::exp(-delta / temperature);
    return dis(gen) < prob;
}
