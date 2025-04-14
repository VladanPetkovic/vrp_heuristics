//
// Created by petkovic on 04.04.25.
//

#include <solver/savings_clark_wright.h>

void SavingsClarkWright::solve() {
    initRoutes();
    calculateSavings();

    for (const Saving &s: savings_vector) {
        combineRoutes(s.from_node_id, s.to_node_id);
    }
}

void SavingsClarkWright::initRoutes() {
    uint16_t start_node_id = vehicle.getDepartureNode().getId();
    uint16_t num_of_nodes = graph.getNumNodes();

    // then perform the savings algorithm
    for (uint16_t node_id = 1; node_id <= num_of_nodes; ++node_id) {
        if (node_id == start_node_id) continue;

        Route route = Route();
        route.addNode(start_node_id);
        route.addNode(node_id);
        route.addNode(start_node_id);
        routes.push_back(route);
    }
}

void SavingsClarkWright::calculateSavings() {
    uint16_t start_node_id = vehicle.getDepartureNode().getId();
    uint16_t num_of_nodes = graph.getNumNodes();

    for (uint16_t current_id = 1; current_id <= num_of_nodes; ++current_id) {
        if (current_id == start_node_id) continue;
        for (uint16_t other_id = current_id + 1; other_id <= num_of_nodes; ++other_id) {
            if (other_id == start_node_id) continue;
            double d_curr_depot = graph.getDistance(current_id, start_node_id);
            double d_other_depot = graph.getDistance(other_id, start_node_id);
            double d_curr_other = graph.getDistance(current_id, other_id);
            double saving = d_curr_depot + d_other_depot - d_curr_other;

            savings_vector.push_back({current_id, other_id, saving});
        }
    }

    std::sort(savings_vector.begin(), savings_vector.end());
}

void SavingsClarkWright::combineRoutes(uint16_t from, uint16_t to) {
    uint16_t start_node_id = vehicle.getDepartureNode().getId();
    Route *from_route = nullptr;
    Route *to_route = nullptr;

    // finding from and to
    for (auto &route: routes) {
        if (route.hasNode(from)) {
            from_route = &route;
        }
        if (route.hasNode(to)) {
            to_route = &route;
        }
    }

    if (from_route == nullptr || to_route == nullptr || from_route == to_route) {
        return;
    }

    uint16_t total_quantity = from_route->getTotalQuantity(graph) + to_route->getTotalQuantity(graph);
    if (vehicle.exceedsCapacity(total_quantity)) {
        return;
    }

    // MERGE
    bool is_at_start = from_route->startsWith(from);
    bool is_at_end = from_route->endsWith(from);

    if (is_at_start || is_at_end) {
        for (short node: to_route->getNodes()) {
            if (node == start_node_id) {
                continue;
            }
            if (node == -1) {
                break;
            }

            if (is_at_start) {
                from_route->addNodeToFront(node);
            } else if (is_at_end) {
                from_route->addNode(node);
            }
        }
    } else {
        uint8_t from_index = from_route->findNodeIndex(from);
        if (from_index == -1) return;

        uint8_t insert_at = from_index + 1;
        for (short node: to_route->getNodes()) {
            if (node == start_node_id) {
                continue;
            }
            if (node == -1) {
                break;
            }
            from_route->insertNodeAt(insert_at++, node);
        }
    }

    // add depot to the end
    from_route->addNode(vehicle.getDepartureNode().getId());

    routes.remove(*to_route);
}
