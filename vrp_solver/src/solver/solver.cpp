//
// Created by petkovic on 27.03.25.
//

#include <solver/solver.h>

Solver::~Solver() {
    // dtor
}

std::list<Route> &Solver::getRoutes() {
    return routes;
}

int Solver::getIterations() const {
    return 1;
}
