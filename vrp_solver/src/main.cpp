#include <iostream>
#include "../include/graph.h"
#include "../include/graph_builder.h"

int main() {
    Graph graph;

    GraphBuilder::loadGraphFromData(graph, "../../test_data/uchoa_et_al_2014");

    graph.printGraph();
    return 0;
}
