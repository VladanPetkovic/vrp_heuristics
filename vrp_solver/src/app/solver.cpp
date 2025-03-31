//
// Created by petkovic on 27.03.25.
//

#include <app/solver.h>

Solver::~Solver() {
    for (Route *route: routes) {
        delete route;
    }
    routes.clear();
}

void Solver::nearestNeighbor() {
    uint16_t start_node_id = vehicle.getDepartureNode().getId();
    uint16_t num_of_nodes = graph.getNumNodes();
    std::vector<bool> visited(num_of_nodes, false);
    visited[start_node_id] = true;
    bool every_node_visited = false;

    while (!every_node_visited) {
        auto *route = new Route(); // TODO: change this.routes to an stack-array
        uint16_t current_node_id = start_node_id;
        route->addNode(start_node_id); // always start with depot

        uint16_t current_capacity = 0;
        bool route_completed = false;

        while (!route_completed) {
            uint16_t nearest_node_id = start_node_id; // always return to depot, if nothing found
            double min_distance = std::numeric_limits<double>::max();

            for (uint16_t neighbour_id = 1; neighbour_id < num_of_nodes; ++neighbour_id) {
                if (!visited[neighbour_id]) {
                    double distance = graph.getDistance(current_node_id, neighbour_id);
                    if (distance < min_distance) {
                        min_distance = distance;
                        nearest_node_id = neighbour_id;
                    }
                }
            }

            uint16_t new_capacity = current_capacity + graph.getNode(nearest_node_id)->getQuantity();

            // we went back to the depot OR currentCapacity is too high
            if (nearest_node_id == start_node_id || vehicle.exceedsCapacity(new_capacity)) {
                route->addNode(start_node_id);
                routes.push_back(route);
                route_completed = true;
            } else if (!vehicle.exceedsCapacity(new_capacity)) {
                // we picked another customer
                route->addNode(nearest_node_id);
                visited[nearest_node_id] = true;
                current_node_id = nearest_node_id;
                current_capacity = new_capacity;
            }
        }

        every_node_visited = true;
        for (uint16_t i = 1; i < num_of_nodes; ++i) {
            if (!visited[i]) {
                every_node_visited = false;
                break;
            }
        }
    }
}

void Solver::printRoutes() const {
    size_t i = 0;
    for (const auto &route: routes) {
        std::cout << "Route for vehicle " << i++ << ": ";
        route->printRoute();
    }
}

std::list<Route *> *Solver::getRoutes() {
    return &routes;
}
