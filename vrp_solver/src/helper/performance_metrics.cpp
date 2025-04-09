//
// Created by petkovic on 08.04.25.
//

#include <helper/performance_metrics.h>

PerformanceMetrics::PerformanceMetrics(const ArgumentOptions &options, Graph &graph, Solver &solver, Vehicle &vehicle,
                                       std::chrono::duration<long, std::ratio<1, 1000000> > duration) {
    this->duration = duration;
    this->number_of_iterations = solver.getIterations();
    this->number_of_vehicles = solver.getRoutes().size();
    this->algorithm = options.algorithm;
    this->instance_name = extractInstanceName(options.inputFilePath);

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
        file << "algorithm;instance_name;duration;number_of_iterations;number_of_vehicles;total_distance\n";
    }

    file << to_string(this->algorithm) << ";"
            << this->instance_name << ";"
            << this->duration << ";"
            << this->number_of_iterations << ";"
            << this->number_of_vehicles << ";"
            << this->total_distance << "\n";

    file.close();
}

std::string PerformanceMetrics::extractInstanceName(const std::string &full_path) {
    const std::filesystem::path path(full_path);

    auto filename = path.filename().string();
    auto parent_dir = path.parent_path().filename().string();

    return parent_dir + "/" + filename;
}
