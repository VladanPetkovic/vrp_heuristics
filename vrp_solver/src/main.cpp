#include <chrono>
#include <models/vehicle.h>
#include <models/graph.h>
#include <helper/xml_converter.h>
#include <solver/solver.h>
#include <helper/command_line_parser.h>
#include <helper/performance_metrics.h>
#include <helper/solver_helper.h>

int main(int argc, char *argv[]) {
    Graph graph;
    Vehicle vehicle;
    std::list<Route> routes;
    // get options
    ArgumentOptions program_options;
    CommandLineParser::parseArguments(program_options, argc, argv);

    // create graph
    XMLConverter::loadGraphFromData(graph, vehicle, program_options.inputFilePath);

    // create solution
    std::unique_ptr<Solver> solver = SolverHelper::createSolver(graph, vehicle, routes, program_options.algorithm);

    auto start = std::chrono::high_resolution_clock::now();
    solver->solve();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Function Execution Time: " << duration.count() << " microseconds\n";

    // output solution
    bool properlySaved = XMLConverter::saveSolutionToFile(solver->getRoutes(), graph, program_options.outputFilePath);

    // save and check metrics
    if (properlySaved) {
        PerformanceMetrics performance = PerformanceMetrics(program_options, graph, *solver, vehicle, duration);
        performance.save();
    }

    return properlySaved ? EXIT_SUCCESS : EXIT_FAILURE;
}
