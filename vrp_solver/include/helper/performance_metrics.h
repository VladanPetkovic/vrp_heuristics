//
// Created by petkovic on 08.04.25.
//

#ifndef PERFORMANCE_HELPER_H
#define PERFORMANCE_HELPER_H

#include <helper/command_line_parser.h>
#include <chrono>
#include <list>
#include <fstream>
#include <string>
#include <filesystem>
#include <models/graph.h>
#include <models/vehicle.h>
#include <solver/solver.h>
#include <models/route.h>
#include <unordered_set>

class PerformanceMetrics {
public:
    PerformanceMetrics(const ArgumentOptions &options, Graph &graph, Solver &solver,
                       Vehicle &vehicle, std::chrono::duration<long, std::ratio<1, 1000000> > duration);

    static std::string extractInstanceName(const std::string &full_path);

    static std::string extractFolderName(const std::string &full_path);

    void save() const;

private:
    int duration;
    int number_of_iterations;
    int number_of_vehicles;
    double total_distance;
    std::string instance_name;
    std::string folder_name;
    AlgorithmType algorithm;

    bool everyNodeVisited(Graph &graph, Solver &solver) const;

    bool routeIsCorrect(Solver &solver, Vehicle &vehicle) const;

    bool vehicleExceedsQuantity(Solver &solver, Vehicle &vehicle, Graph &graph) const;

    bool duplicateNodesFound(Solver &solver, Vehicle &vehicle) const;
};


#endif //PERFORMANCE_HELPER_H
