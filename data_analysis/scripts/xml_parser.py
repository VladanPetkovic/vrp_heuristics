import xml.etree.ElementTree as ET
from models.route_node import *


def parse_xml(file_path):
    tree = ET.parse(file_path)
    root = tree.getroot()
    return root


def extract_nodes(root):
    nodes = {}
    for node in root.find('./network/nodes'):
        node_id = int(node.get('id'))
        cx = float(node.find('cx').text)
        cy = float(node.find('cy').text)
        nodes[node_id] = (cx, cy, 0)  # 0 as default quantity

    for request in root.find('./requests'):
        request_id = int(request.get('id'))
        node_id = int(request.get('node'))
        quantity = float(request.find('quantity').text)

        if node_id in nodes:
            cx, cy, _ = nodes[node_id]
            nodes[node_id] = (cx, cy, quantity)
        else:
            print(f"Warning: Request {request_id} references missing node {node_id}")
    return nodes


def extract_vehicle_profile(root):
    vehicle_profile = root.find('./fleet/vehicle_profile')
    capacity = float(vehicle_profile.find('capacity').text)
    departure_node_id = int(vehicle_profile.find('departure_node').text)
    arrival_node_id = int(vehicle_profile.find('arrival_node').text)
    return [capacity, departure_node_id, arrival_node_id]


def extract_solution(root):
    routes = []
    for route in root.findall('./route'):
        new_route = []
        for node in route.findall('./nodes/node'):
            node_id = int(node.get('id'))
            next_node_id = int(node.get('next_node_id'))
            x = float(node.find('x').text)
            y = float(node.find('y').text)
            quantity = float(node.find('quantity').text)
            # make object Node
            new_route_node = RouteNode(node_id, next_node_id, x, y, quantity)
            # add this Node to new_route
            new_route.append(new_route_node)

        routes.append(new_route)
    return routes
