#include "graph.h"
#include "graph_builder.h"
#include "helper/program_helper.h"

int main(int argc, char *argv[]) {
    Graph graph;
    // get options
    ProgramOptions program_options;
    ProgramHelper::parseArguments(program_options, argc, argv);

    // create graph
    GraphBuilder::loadGraphFromData(graph, program_options.inputFilePath);
    graph.printGraph();

    // create solution

    // output solution



    return 0;
}
