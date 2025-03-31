#include <chrono>
#include <models/vehicle.h>
#include <models/graph.h>
#include <app/graph_builder.h>
#include <app/solver.h>
#include <helper/command_line_parser.h>

int main(int argc, char *argv[]) {
    Graph graph;
    Vehicle vehicle;
    // get options
    ArgumentOptions program_options;
    CommandLineParser::parseArguments(program_options, argc, argv);

    // create graph
    GraphBuilder::loadGraphFromData(graph, vehicle, program_options.inputFilePath);

    // create solution
    Solver solver(graph, vehicle);
    auto start = std::chrono::high_resolution_clock::now();
    solver.nearestNeighbor();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Function Execution Time: " << duration.count() << " microseconds\n";

    // output solution
    // solver.printRoutes();

    return 0;
}
