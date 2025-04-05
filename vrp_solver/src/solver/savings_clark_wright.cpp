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
    routes.assign(num_of_nodes - 1, Route()); // subtract departure_node
    // then perform the savings algorithm
    for (uint16_t node_id = start_node_id + 1; node_id <= num_of_nodes; ++node_id) {
        auto it = routes.begin();
        std::advance(it, node_id - 2);

        it->addNode(start_node_id);
        it->addNode(node_id);
        it->addNode(start_node_id);
    }
}

void SavingsClarkWright::calculateSavings() {
    uint16_t start_node_id = vehicle.getDepartureNode().getId();
    uint16_t num_of_nodes = graph.getNumNodes();

    for (uint16_t current_id = start_node_id + 1; current_id <= num_of_nodes; ++current_id) {
        for (uint16_t other_id = current_id + 1; other_id <= num_of_nodes; ++other_id) {
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
    auto from_it = routes.end();
    auto to_it = routes.end();

    // Find routes containing 'from' and 'to'
    for (auto it = routes.begin(); it != routes.end(); ++it) {
        if (it->hasNode(from)) {
            from_it = it;
        }
        if (it->hasNode(to)) {
            to_it = it;
        }
    }

    // Can't merge if same route or either not found
    if (from_it == routes.end() || to_it == routes.end() || from_it == to_it)
        return;

    // Ensure 'from' is at the end of one route, and 'to' is at the beginning of the other
    if (!from_it->endsWith(from) || !to_it->startsWith(to))
        return;

    uint16_t total_quantity = from_it->getTotalQuantity(graph) + to_it->getTotalQuantity(graph);
    if (vehicle.exceedsCapacity(total_quantity))
        return;

    // Merge: remove depot from end of 'from' and beginning of 'to'
    from_it->removeLast(); // depot
    to_it->removeFirst(); // depot

    // add all nodes from to-route to from-route
    for (uint16_t node: to_it->getNodes()) {
        if (node == start_node_id || node == -1) {
            break;
        }
        from_it->addNode(node);
    }

    // add depot to the end
    from_it->addNode(vehicle.getDepartureNode().getId());

    routes.erase(to_it);
}
