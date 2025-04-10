import numpy as np
import pandas as pd
import sys
import glob

from scripts.file_helper import *
from scripts.xml_parser import *


def prepare_data():
    combine_statistics_of_test_data()
    analyze_tests_and_save()


def combine_statistics_of_test_data():
    file_list = ['test_data/augerat_1995_set_a/data.csv',
                 'test_data/christofides_et_al_1979_cmt/data.csv',
                 'test_data/uchoa_et_al_2014/data.csv']

    combined_df = pd.concat([pd.read_csv(f, sep=';') for f in file_list], ignore_index=True)

    combined_df.to_csv('test_data/data_stats.csv', index=False, sep=';')


def analyze_tests_and_save():
    dir_list = ['test_data/augerat_1995_set_a',
                'test_data/christofides_et_al_1979_cmt',
                'test_data/uchoa_et_al_2014']

    csv_path = 'test_data/data_stats.csv'
    if not file_exists(csv_path):
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
            entropy = get_spatial_entropy(nodes)
            # get depot location
            abs_pos, rel_horiz_pos, rel_vert_pos = get_depot_placement(nodes)

            # add data for every test-instance
            df.loc[df['instance_name'] == instance_name, 'entropy'] = entropy
            df.loc[df['instance_name'] == instance_name, 'depot_abs_pos'] = abs_pos
            df.loc[df['instance_name'] == instance_name, 'depot_rel_horiz_pos'] = rel_horiz_pos
            df.loc[df['instance_name'] == instance_name, 'depot_rel_vert_pos'] = rel_vert_pos

    # save file
    df.to_csv(csv_path, sep=';', index=False)


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


def get_spatial_entropy(nodes, grid_size=10):
    active_coords = [(x, y) for _, (x, y, qty) in nodes.items() if qty > 0]
    if not active_coords:
        return 0

    xs, ys = zip(*active_coords)
    x_min, x_max = min(xs), max(xs)
    y_min, y_max = min(ys), max(ys)

    # creating grid
    cell_counts = np.zeros((grid_size, grid_size))
    for x, y in active_coords:
        xi = int((x - x_min) / (x_max - x_min + 1e-6) * (grid_size - 1))
        yi = int((y - y_min) / (y_max - y_min + 1e-6) * (grid_size - 1))
        cell_counts[yi, xi] += 1

    probs = cell_counts.flatten() / len(active_coords)
    probs = probs[probs > 0]  # remove empty cells
    entropy = -np.sum(probs * np.log2(probs + 1e-10))
    return entropy
