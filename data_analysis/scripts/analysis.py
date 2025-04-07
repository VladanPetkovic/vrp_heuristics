import sys

from scripts.file_helper import *
from scripts.xml_parser import *


def run_statistics(nodes, vehicle_profile, solution_routes):
    print("hello")


def analyze(file_path, solution_file_path):
    if not file_exists(file_path) or not file_exists(solution_file_path):
        print("Either file_path or solution_file_path does not exist!")
        sys.exit(1)

    # get data from file_path
    root = parse_xml(file_path)
    nodes = extract_nodes(root)
    vehicle_profile = extract_vehicle_profile(root)
    plot_title = get_file_name_from_path(file_path)

    # get data from solution
    solution_root = parse_xml(solution_file_path)
    solution_routes = extract_solution(solution_root)

    run_statistics(nodes, vehicle_profile, solution_routes)
