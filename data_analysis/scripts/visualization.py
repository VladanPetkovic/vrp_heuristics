import os
import xml.etree.ElementTree as ET
import matplotlib.pyplot as plt


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
        quantity = int(request.find('quantity').text)

        if node_id in nodes:
            cx, cy, _ = nodes[node_id]
            nodes[node_id] = (cx, cy, quantity)
        else:
            print(f"Warning: Request {request_id} references missing node {node_id}")
    return nodes


def extract_vehicle_profile(root):
    vehicle_profile = root.find('./fleet/vehicle_profile')
    capacity = int(vehicle_profile.find('capacity').text)
    departure_node_id = int(vehicle_profile.find('departure_node').text)
    arrival_node_id = int(vehicle_profile.find('arrival_node').text)
    return [capacity, departure_node_id, arrival_node_id]


def plot_nodes(nodes, vehicle_profile, file_name):
    plt.figure(figsize=(8, 6))

    for node_id, (cx, cy, quantity) in nodes.items():
        is_depot = (quantity <= 0) or (node_id == vehicle_profile[1]) or (node_id == vehicle_profile[2])
        marker = 'x' if is_depot else 'o'
        size = 50 if is_depot else 20
        plt.scatter(cx, cy, color='black', marker=marker, s=size)

        show_label = len(nodes) < 150
        label = '' if is_depot else f"{quantity}"
        label = label if show_label else ''
        plt.text(cx + 5, cy + 5, label, fontsize=12, color='grey')

    plt.xlabel('X Coordinate')
    plt.ylabel('Y Coordinate')
    plt.title(f'Instance: {file_name}')
    plt.grid(True)
    description = f'Given quantity per request\nMax vehicle-capacity: {vehicle_profile[0]}'
    second_desc = 'X...depot\n●...requests'
    plt.figtext(0.15, 0.95, description, wrap=True, ha='center', fontsize=10, va='center')
    plt.figtext(0.9, 0.95, second_desc, wrap=True, ha='center', fontsize=10, va='center')
    plt.savefig(f'out/{file_name}.png')


def visualize(file_path, solution_file_path = None):
    # TODO: add solution
    root = parse_xml(file_path)
    file_name = os.path.basename(file_path)
    file_name_without_ext = os.path.splitext(file_name)[0]
    nodes = extract_nodes(root)
    vehicle_profile = extract_vehicle_profile(root)
    plot_nodes(nodes, vehicle_profile, file_name_without_ext)
