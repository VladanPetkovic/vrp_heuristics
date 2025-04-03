import sys
import matplotlib.pyplot as plt

from scripts.file_helper import *
from scripts.xml_parser import *


def plot_nodes(nodes, vehicle_profile, output_file_path, plot_title):
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
    plt.title(f'Instance: {plot_title}')
    plt.grid(True)
    description = f'Given quantity per request\nMax vehicle-capacity: {vehicle_profile[0]}'
    second_desc = 'X...depot\n●...requests'
    plt.figtext(0.15, 0.95, description, wrap=True, ha='center', fontsize=10, va='center')
    plt.figtext(0.9, 0.95, second_desc, wrap=True, ha='center', fontsize=10, va='center')
    plt.savefig(output_file_path)


def plot_nodes_with_routes(nodes, vehicle_profile, output_file_path, solution_routes, plot_title):
    plt.figure(figsize=(8, 6))

    for node_id, (cx, cy, quantity) in nodes.items():
        is_depot = (quantity <= 0) or (node_id == vehicle_profile[1]) or (node_id == vehicle_profile[2])
        marker = 'x' if is_depot else 'o'
        size = 50 if is_depot else 20
        plt.scatter(cx, cy, color='black', marker=marker, s=size)

        show_label = len(nodes) < 150
        label = '' if is_depot else f"{quantity}"
        label = label if show_label else ''
        plt.text(cx + 1, cy + 1, label, fontsize=12, color='grey')

    # routes
    route_colors = ['red', 'blue', 'green', 'orange', 'black', 'grey', 'violet']
    for idx, route in enumerate(solution_routes):
        route_color = route_colors[idx % len(route_colors)]
        if idx > 6:
            break
        for i in range(len(route) - 2):
            node1 = route[i]
            node2 = route[i + 1]

            plt.plot([node1.x, node2.x], [node1.y, node2.y], color=route_color,
                     linestyle='-', linewidth=0.5, label=f'Route {idx + 1}')

    plt.xlabel('X Coordinate')
    plt.ylabel('Y Coordinate')
    plt.title(f'Instance: {plot_title}')
    plt.grid(True)
    description = f'Given quantity per request\nMax vehicle-capacity: {vehicle_profile[0]}'
    second_desc = 'X...depot\n●...requests'
    plt.figtext(0.15, 0.95, description, wrap=True, ha='center', fontsize=10, va='center')
    plt.figtext(0.9, 0.95, second_desc, wrap=True, ha='center', fontsize=10, va='center')

    # plt.legend(loc='upper right', fontsize=10)

    plt.savefig(output_file_path)


def plot_solution(file_path, output_file_path, solution_file_path):
    # get data from file_path
    root = parse_xml(file_path)
    nodes = extract_nodes(root)
    vehicle_profile = extract_vehicle_profile(root)
    plot_title = get_file_name_from_path(file_path)

    # get data from solution
    solution_root = parse_xml(solution_file_path)
    solution_routes = extract_solution(solution_root)

    plot_nodes_with_routes(nodes, vehicle_profile, output_file_path, solution_routes, plot_title)


def plot_only_nodes(file_path, output_file_path):
    # get data
    root = parse_xml(file_path)
    nodes = extract_nodes(root)
    vehicle_profile = extract_vehicle_profile(root)
    # plot only the nodes
    plot_title = get_file_name_from_path(file_path)
    plot_nodes(nodes, vehicle_profile, output_file_path, plot_title)


def visualize(file_path, output_file_path, solution_file_path):
    if file_exists(file_path) and file_exists(solution_file_path):
        plot_solution(file_path, output_file_path, solution_file_path)
    elif file_exists(file_path) and not file_exists(solution_file_path):
        plot_only_nodes(file_path, output_file_path)
    else:
        print("File path does not exist!")
        sys.exit(1)
