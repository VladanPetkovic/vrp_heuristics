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

class PerformanceMetrics {
public:
    PerformanceMetrics(const ArgumentOptions &options, Graph &graph, Solver &solver,
                       Vehicle &vehicle, std::chrono::duration<long, std::ratio<1, 1000000> > duration);

    static std::string extractInstanceName(const std::string &full_path);

    void save() const;

private:
    std::chrono::duration<long, std::ratio<1, 1000000> > duration;
    int number_of_iterations; // TODO: later for metaheuristics
    int number_of_vehicles;
    double total_distance;
    std::string instance_name;
    AlgorithmType algorithm;
};


#endif //PERFORMANCE_HELPER_H
