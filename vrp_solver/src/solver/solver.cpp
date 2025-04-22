//
// Created by petkovic on 27.03.25.
//

#include <solver/solver.h>

Solver::~Solver() {
    // dtor
}

std::list<Route> &Solver::getRoutes() const {
    return routes;
}

int Solver::getIterations() const {
    return 1;
}

double Solver::getTotalDistance(std::list<Route> &routes_list) const {
    double total_distance = 0.0;
    for (Route &route: routes_list) {
        total_distance += route.getTotalDistance(graph, vehicle);
    }

    return total_distance;
}

Route &Solver::getRoute(const uint8_t index) {
    auto it = routes.begin();
    std::advance(it, index);
    return *it;
}
