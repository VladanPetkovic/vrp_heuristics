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

uint16_t IteratedLocalSearch::getIterations() const {
    return _iterations;
}

void IteratedLocalSearch::solve() {
    initSolution();
    auto best_solution = routes;
    auto current = routes;
    double best_solution_value = getTotalDistance(routes);

    for (_iterations = 0; _iterations < MAX_ITERATIONS; _iterations++) {
        shake(5); // TODO: calculate intensity with temperature
        localSearch();

        auto new_solution_value = getTotalDistance(routes);
        if (new_solution_value < best_solution_value) {
            // save the best solution
            best_solution = routes;
            best_solution_value = new_solution_value;
        }

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
 * TODO: shake multiple routes multiple times
 */
void IteratedLocalSearch::shake(uint8_t intensity) {
    // for (int i = 0; i < intensity; ++i) {
    //     int strategy = rand() % 3;
    //
    //     switch (strategy) {
    //         case 0: randomIntraSwap(); break;
    //         case 1: randomInterMove(); break;
    //         case 2: randomCrossExchange(); break;
    //     }
    // }
}

// randomIntraSwap
// Pick random route
// Pick two random positions in that route
// Swap their customers

// randomInterMove
// Choose two different routes A and B
// Pick a random customer from A
// Insert into random position in B (if capacity allows)

// randomCrossExchange
// Select customer i from route A, and j from route B
// Swap their positions if capacity is not violated

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
