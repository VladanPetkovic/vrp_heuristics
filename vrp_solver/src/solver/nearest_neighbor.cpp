//
// Created by petkovic on 01.04.25.
//

#include <solver/nearest_neighbor.h>

void NearestNeighbor::solve() {
    uint16_t start_node_id = vehicle.getDepartureNode().getId();
    uint16_t num_of_nodes = graph.getNumNodes();
    std::vector<bool> visited(num_of_nodes, false);
    visited[start_node_id] = true;

    while (!allNodesVisited(visited)) {
        routes.push_back(buildRoute(start_node_id, visited));
    }
}

/**
 * Here I decided to return a value and avoid heap-allocation, because Route contains only a vector of uint16_t.
 * @param start_node_id id of the depot-node
 * @param visited array of boolean for every customer (if already collected)
 * @return a Route
 */
Route NearestNeighbor::buildRoute(uint16_t start_node_id, std::vector<bool> &visited) const {
    Route route;
    uint16_t current_node_id = start_node_id;
    uint16_t current_capacity = 0;
    route.addNode(start_node_id); // always start with depot

    while (true) {
        uint16_t nearest_node_id = findNearestNode(current_node_id, visited);
        uint16_t new_capacity = current_capacity + graph.getNode(nearest_node_id)->getQuantity();

        // we went back to the depot OR currentCapacity is too high
        if (nearest_node_id == start_node_id || vehicle.exceedsCapacity(new_capacity)) {
            route.addNode(start_node_id);
            return route;
        }

        // we picked another customer
        route.addNode(nearest_node_id);
        visited[nearest_node_id] = true;
        current_node_id = nearest_node_id;
        current_capacity = new_capacity;
    }
}

uint16_t NearestNeighbor::findNearestNode(uint16_t current_node_id, const std::vector<bool> &visited) const {
    uint16_t nearest_node_id = vehicle.getDepartureNode().getId(); // always return to depot, if nothing found
    double min_distance = std::numeric_limits<double>::max();

    for (uint16_t neighbour_id = 1; neighbour_id < graph.getNumNodes(); ++neighbour_id) {
        if (!visited[neighbour_id]) {
            double distance = graph.getDistance(current_node_id, neighbour_id);
            if (distance < min_distance) {
                min_distance = distance;
                nearest_node_id = neighbour_id;
            }
        }
    }
    return nearest_node_id;
}

bool NearestNeighbor::allNodesVisited(const std::vector<bool> &visited) {
    for (uint16_t i = 1; i < visited.size(); ++i) {
        if (!visited[i]) {
            return false;
        }
    }
    return true;
}
