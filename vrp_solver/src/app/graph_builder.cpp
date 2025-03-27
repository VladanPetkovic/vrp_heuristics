//
// Created by petkovic on 24.03.25.
//

#include "app/graph_builder.h"

#include <models/node.h>

void GraphBuilder::loadGraphFromData(Graph &graph, const std::string &file_path) {
    pugi::xml_document doc;
    if (!doc.load_file(file_path.c_str())) {
        std::cerr << "Failed to load XML file!" << std::endl;
        exit(EXIT_FAILURE);
    }

    pugi::xml_node instance = doc.child("instance"); // root

    // nodes
    pugi::xml_node nodes = instance.child("network").child("nodes");

    for (pugi::xml_node node: nodes.children("node")) {
        uint16_t x = node.child("cx").text().as_int();
        uint16_t y = node.child("cy").text().as_int();
        uint16_t id = node.attribute("id").as_int();
        uint8_t type = node.attribute("type").as_int();
        Node newNode = Node(x, y, id, type);
        graph.addNode(id, newNode);
    }
    // vehicle-profile
    pugi::xml_node fleet = instance.child("fleet");
    // requests
    pugi::xml_node requests = instance.child("requests");
    for (pugi::xml_node request: requests.children("request")) {
        uint8_t quantity = request.child("quantity").text().as_int();
        uint16_t node_id = request.attribute("node").as_int();
        Node* existingNode = graph.getNode(node_id);
        existingNode->setQuantity(quantity);
    }

    graph.computeDistances();
}
