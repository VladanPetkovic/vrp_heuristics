#include "models/graph.h"
#include "app/graph_builder.h"
#include "app/solver.h"
#include "helper/command_line_parser.h"

int main(int argc, char *argv[]) {
    Graph graph;
    // get options
    ArgumentOptions program_options;
    CommandLineParser::parseArguments(program_options, argc, argv);

    // create graph
    GraphBuilder::loadGraphFromData(graph, program_options.inputFilePath);
    // graph.printGraph();

    // create solution
    Solver solver(graph);
    solver.nearestNeighbor(1);

    // output solution
    solver.printRoutes();

    return 0;
}

// TODO: refactor with typdef: u_int16_t (DRY)
