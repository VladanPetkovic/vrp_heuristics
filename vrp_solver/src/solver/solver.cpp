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

uint16_t Solver::getIterations() const {
    return 1;
}

double Solver::getTotalDistance(std::list<Route> &routes_list) const {
    double total_distance = 0.0;
    for (Route &route: routes_list) {
        short previous_node_id = vehicle.getDepartureNode().getId();
        for (const short node_id: route.getNodes()) {
            if (node_id == -1) {
                break;
            }
            total_distance += graph.getDistance(previous_node_id, node_id);
            previous_node_id = node_id;
        }
    }

    return total_distance;
}
