#include "models/graph.h"
#include "app/graph_builder.h"
#include "helper/command_line_parser.h"

int main(int argc, char *argv[]) {
    Graph graph;
    // get options
    ArgumentOptions program_options;
    CommandLineParser::parseArguments(program_options, argc, argv);

    // create graph
    GraphBuilder::loadGraphFromData(graph, program_options.inputFilePath);
    graph.printGraph();

    // create solution

    // output solution


    return 0;
}
