//
// Created by petkovic on 24.03.25.
//

#include "app/xml_converter.h"

#include <models/node.h>

void XMLConverter::loadGraphFromData(Graph &graph, Vehicle &vehicle, const std::string &file_path) {
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
    pugi::xml_node vehicleProfile = instance.child("fleet").child("vehicle_profile");
    uint16_t capacity = vehicleProfile.child("capacity").text().as_int();
    uint16_t departure_node_id = vehicleProfile.child("departure_node").text().as_int();
    uint16_t arrival_node_id = vehicleProfile.child("arrival_node").text().as_int();
    vehicle.setCapacity(capacity);
    vehicle.setDepartureNode(graph.getNode(departure_node_id));
    vehicle.setArrivalNode(graph.getNode(arrival_node_id));

    // requests
    pugi::xml_node requests = instance.child("requests");
    for (pugi::xml_node request: requests.children("request")) {
        uint8_t quantity = request.child("quantity").text().as_int();
        uint16_t node_id = request.attribute("node").as_int();
        Node *existingNode = graph.getNode(node_id);
        existingNode->setQuantity(quantity);
    }

    graph.computeDistances();
}

bool XMLConverter::saveSolutionToFile(std::list<Route *> *routes, Graph &graph, const std::string &filename) {
    pugi::xml_document doc;
    pugi::xml_node routes_node = doc.append_child("routes");

    for (auto route: *routes) {
        pugi::xml_node route_node = routes_node.append_child("route");
        pugi::xml_node nodes_node = route_node.append_child("nodes");

        RouteNode *current_node = route->getHead();
        while (current_node) {
            Node *data_node = graph.getNode(current_node->id);
            pugi::xml_node node_node = nodes_node.append_child("node");

            node_node.append_child("x").text() = data_node->getX();
            node_node.append_child("y").text() = data_node->getY();
            node_node.append_child("quantity").text() = data_node->getQuantity();
            node_node.append_child("id").text() = data_node->getId();

            if (current_node->next) {
                node_node.append_child("next_node_id").text() = current_node->next->id;
            } else {
                node_node.append_child("next_node_id").text() = -1;
            }

            current_node = current_node->next;
        }
    }

    return doc.save_file(filename.c_str());
}
