//
// Created by petkovic on 27.03.25.
//

#include "app/solver.h"

void Solver::nearestNeighbor(u_int16_t startNodeId) {
    const u_int16_t vehicleCapacity = 2000;
    u_int16_t numOfNodes = graph.getNumNodes();
    std::vector<bool> visited(numOfNodes, false);
    visited[startNodeId] = true;
    routes.clear();

    while (true) {
        Route route;
        u_int16_t currentNode = startNodeId;
        route.addNode(currentNode);

        u_int16_t currentCapacity = 0;
        bool routeCompleted = false;

        while (!routeCompleted) {
            u_int16_t nearestNode = startNodeId; // always return to depot, if nothing found
            double minDistance = std::numeric_limits<double>::max();

            for (u_int16_t neighborId = 1; neighborId < numOfNodes; ++neighborId) {
                if (!visited[neighborId]) {
                    double distance = graph.getDistance(currentNode, neighborId);
                    if (distance < minDistance) {
                        minDistance = distance;
                        nearestNode = neighborId;
                    }
                }
            }

            // TODO: continue here - think about the startNodeId
            if (nearestNode != -1) {
                if (currentCapacity + graph.getNode(nearestNode)->getQuantity() <= vehicleCapacity) {
                    route.addNode(nearestNode);
                    visited[nearestNode] = true;
                    currentNode = nearestNode;
                    currentCapacity += graph.getNode(nearestNode)->getQuantity();
                } else {
                    route.addNode(startNodeId);
                    routes.push_back(route);
                    routeCompleted = true;
                    break;
                }
            }

            bool allNodesVisited = true;
            for (u_int16_t i = 1; i < numOfNodes; ++i) {
                if (!visited[i]) {
                    allNodesVisited = false;
                    break;
                }
            }

            if (allNodesVisited) {
                route.addNode(startNodeId);
                routes.push_back(route);
                routeCompleted = true;
            }
        }

        bool allNodesVisited = true;
        for (u_int16_t i = 1; i < numOfNodes; ++i) {
            if (!visited[i]) {
                allNodesVisited = false;
                break;
            }
        }

        if (allNodesVisited) {
            break;
        }
    }
}

void Solver::printRoutes() const {
    for (size_t i = 0; i < routes.size(); ++i) {
        std::cout << "Route for vehicle " << i + 1 << ": ";
        routes[i].printRoute();
    }
}
