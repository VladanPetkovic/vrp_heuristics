//
// Created by petkovic on 27.03.25.
//

#include <solver/solver.h>

Solver::~Solver() {
    // dtor
}

void Solver::printRoutes() const {
    size_t i = 0;
    for (const auto &route: routes) {
        std::cout << "Route for vehicle " << i++ << ": ";
        route.printRoute();
    }
}

std::list<Route> &Solver::getRoutes() {
    return routes;
}

void Solver::setRoutes(const std::list<Route> &newRoutes) {
    routes = newRoutes;
}

int Solver::getIterations() const {
    return 1;
}
