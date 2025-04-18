//
// Created by petkovic on 08.04.25.
//

#include <helper/performance_metrics.h>

PerformanceMetrics::PerformanceMetrics(const ArgumentOptions &options, Graph &graph, Solver &solver, Vehicle &vehicle,
                                       std::chrono::duration<long, std::ratio<1, 1000000> > duration) {
    this->duration = static_cast<int>(duration.count());
    this->number_of_iterations = solver.getIterations();
    this->number_of_vehicles = solver.getRoutes().size();
    this->algorithm = options.algorithm;
    this->instance_name = extractInstanceName(options.inputFilePath);
    this->folder_name = extractFolderName(options.inputFilePath);

    // calculate total_distance
    double total_distance = 0.0;
    for (Route &route: solver.getRoutes()) {
        short previous_node_id = 1;
        for (short node_id: route.getNodes()) {
            if (node_id == -1) {
                break;
            }
            total_distance += graph.getDistance(previous_node_id, node_id);
            previous_node_id = node_id;
        }
    }
    this->total_distance = total_distance;
    std::cout << "Total distance " << total_distance << std::endl;
    if (!everyNodeVisited(graph, solver)) {
        std::cout << "Not visited every node!" << std::endl;
    }
    if (!routeIsCorrect(solver, vehicle)) {
        std::cout << "Route invalid!" << std::endl;
    }
    // TODO: check, if vehicle capacity was exceeded
}


void PerformanceMetrics::save() const {
    std::string filename = "performance.csv";
    bool file_exists = std::filesystem::exists(filename);

    std::ofstream file(filename, std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file '" << filename << "' for writing.\n";
        return;
    }

    if (!file_exists) {
        file <<
                "algorithm;instance_name;folder_name;duration_μs;number_of_iterations;number_of_vehicles;total_distance\n";
    }

    file << to_string(this->algorithm) << ";"
            << this->instance_name << ";"
            << this->folder_name << ";"
            << this->duration << ";"
            << this->number_of_iterations << ";"
            << this->number_of_vehicles << ";"
            << this->total_distance << "\n";

    file.close();
}

std::string PerformanceMetrics::extractInstanceName(const std::string &full_path) {
    const std::filesystem::path path(full_path);
    return path.stem().string();
}

std::string PerformanceMetrics::extractFolderName(const std::string &full_path) {
    const std::filesystem::path path(full_path);
    auto parent_dir = path.parent_path().filename().string();
    return parent_dir;
}

bool PerformanceMetrics::everyNodeVisited(Graph &graph, Solver &solver) const {
    uint16_t num_of_nodes = graph.getNumNodes();
    std::vector visited(num_of_nodes, false);

    for (const auto &route: solver.getRoutes()) {
        for (const auto node: route.getNodes()) {
            if (node != -1) {
                visited[node - 1] = true;
            }
        }
    }

    for (uint16_t i = 0; i < visited.size(); ++i) {
        if (!visited[i]) {
            return false;
        }
    }
    return true;
}

bool PerformanceMetrics::routeIsCorrect(Solver &solver, Vehicle &vehicle) const {
    uint16_t start_node_id = vehicle.getDepartureNode().getId();

    if (start_node_id != vehicle.getArrivalNode().getId()) {
        std::cerr << "Departure and arrival nodes not matching!" << std::endl;
        return false;
    }

    for (const auto& route: solver.getRoutes()) {
        uint8_t route_size = route.getSize() - 1;
        auto route_nodes = route.getNodes();
        for (uint8_t i = 0; i < Route::MAX_COUNT_NODES_PER_ROUTE; ++i) {
            auto node = route_nodes[i];
            if (node == -1 && i < route_size) {
                std::cerr << "-1 before route-size!" << std::endl;
                return false;
            }

            if ((i == 0 || i == route_size) && node != start_node_id) {
                std::cerr << "Depot-node not at start and finish!" << std::endl;
                return false;
            }
        }
    }
    return true;
}
