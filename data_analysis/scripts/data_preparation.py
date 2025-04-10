import numpy as np
import pandas as pd
import networkx as nx
import os
import sys
import glob

from scripts.file_helper import *
from scripts.xml_parser import *


def prepare_data():
    # read in the data.csv to one
    combine_statistics_of_test_data()
    analyze_tests()


def combine_statistics_of_test_data():
    file_list = ['test_data/augerat_1995_set_a/data.csv',
                 'test_data/christofides_et_al_1979_cmt/data.csv',
                 'test_data/uchoa_et_al_2014/data.csv']

    combined_df = pd.concat([pd.read_csv(f, sep=';') for f in file_list], ignore_index=True)

    combined_df.to_csv('test_data/data_stats.csv', index=False, sep=';')


def analyze_tests():
    dir_list = ['test_data/augerat_1995_set_a',
                'test_data/christofides_et_al_1979_cmt',
                'test_data/uchoa_et_al_2014']

    csv_path = 'data_stats.csv'
    if not os.path.exists(csv_path):
        print("CSV file does not exist.")
        sys.exit(1)

    df = pd.read_csv(csv_path, sep=';')

    for col in ['entropy', 'depot_abs_pos', 'depot_rel_horiz_pos', 'depot_rel_vert_pos']:
        if col not in df.columns:
            df[col] = None

    for test_dir in dir_list:
        test_files = glob.glob(os.path.join(test_dir, '*.xml'))

        for file_path in test_files:
            if not file_exists(file_path):
                print("File_path does not exist")
                sys.exit(1)

            # get data from file_path
            root = parse_xml(file_path)
            nodes = extract_nodes(root)
            instance_name = get_file_name_from_path(file_path)

            if instance_name not in df['instance_name'].values:
                print("instance_name not existing")
                continue

            # analyze node-placement
            entropy = get_degree_entropy(nodes)
            # get depot location
            abs_pos, rel_horiz_pos, rel_vert_pos = get_depot_placement(nodes)

            # add data for every test-instance
            df.loc[df['instance_name'] == instance_name, 'entropy'] = entropy
            df.loc[df['instance_name'] == instance_name, 'depot_abs_pos'] = abs_pos
            df.loc[df['instance_name'] == instance_name, 'depot_rel_horiz_pos'] = rel_horiz_pos
            df.loc[df['instance_name'] == instance_name, 'depot_rel_vert_pos'] = rel_vert_pos

    # save file
    df.to_csv(csv_path, index=False)


def get_depot_placement(nodes):
    depot_coordinates = None
    for node_id, (cx, cy, quantity) in nodes.items():
        if quantity <= 0:
            depot_coordinates = (cx, cy)
            break
    if depot_coordinates is None:
        print("Depot not found")
        sys.exit(1)

    coords = [(cx, cy) for _, (cx, cy, _) in nodes.items()]
    depot_x, depot_y = depot_coordinates

    abs_position = get_absolute_depot_placement(coords, depot_x, depot_y)
    rel_horiz_pos, rel_vert_pos = get_relative_depot_placement(coords, depot_x, depot_y)

    return abs_position, rel_horiz_pos, rel_vert_pos


def get_absolute_depot_placement(coords, depot_x, depot_y):
    xs, ys = zip(*coords)

    # getting boundaries
    min_x, max_x = min(xs), max(xs)
    min_y, max_y = min(ys), max(ys)
    center_x, center_y = (min_x + max_x) / 2, (min_y + max_y) / 2

    margin_x = (max_x - min_x) * 0.1
    margin_y = (max_y - min_y) * 0.1
    # get absolute placement
    if abs(depot_x - center_x) < margin_x and abs(depot_y - center_y) < margin_y:
        position = "center"
    elif (
            (depot_x < min_x + margin_x or depot_x > max_x - margin_x) and
            (depot_y < min_y + margin_y or depot_y > max_y - margin_y)
    ):
        position = "corner"
    else:
        position = "edge"

    return position


# this function evaluates the relative placement of the depot compared to other nodes
# I said, it is left- or right-sided when more than 60% are on one side
def get_relative_depot_placement(coords, depot_x, depot_y):
    right = sum(1 for cx, cy in coords if cx > depot_x)
    left = sum(1 for cx, cy in coords if cx < depot_x)
    above = sum(1 for cx, cy in coords if cy > depot_y)
    below = sum(1 for cx, cy in coords if cy < depot_y)

    vertical_position_rel = 'centered'
    horizontal_position_rel = 'centered'
    if right > len(coords) * 0.6:
        horizontal_position_rel = "left-sided"
    elif left > len(coords) * 0.6:
        horizontal_position_rel = "right-sided"

    if above > len(coords) * 0.6:
        vertical_position_rel = "below"
    elif below > len(coords) * 0.6:
        vertical_position_rel = "above"

    return horizontal_position_rel, vertical_position_rel


def get_degree_entropy(nodes):
    active_nodes = {node_id: (x, y) for node_id, (x, y, qty) in nodes.items() if qty > 0}

    G = nx.Graph()

    for node_id in active_nodes:
        G.add_node(node_id)

    node_ids = list(active_nodes.keys())
    for i in range(len(node_ids)):
        for j in range(i + 1, len(node_ids)):
            G.add_edge(node_ids[i], node_ids[j])

    degrees = np.array([d for _, d in G.degree()])
    probs = degrees / degrees.sum()
    entropy = -np.sum(probs * np.log2(probs + 1e-10))  # epsilon to prevent log(0)
    return entropy
