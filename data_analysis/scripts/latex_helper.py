import pandas as pd

column_mapping = {
    'instance_name': 'Instance Name',
    'n': 'Nodes',
    'K': 'Vehicles',
    'Q': 'Capacity',
    'UB': 'Upper Bound',
    'BK': 'BK Value',
    'entropy': 'Entropy',
    'depot_abs_pos': 'Depot Absolute Position',
    'depot_rel_horiz_pos': 'Depot Relative Horizontal Position',
    'depot_rel_vert_pos': 'Depot Relative Vertical Position'
}

column_mapping_solution = {
    "algorithm": "Heuristic",
    "duration_μs": "Avg duration (ms)",
    "number_of_iterations": "Avg iteration-count",
    "number_of_vehicles": "Avg vehicle-count",
    "total_distance": "Avg total distance",
    "relative_distance": "Avg relative distance",
    "best_relative_distance": "Best relative distance",
    "worst_relative_distance": "Worst relative distance"
}

algorithm_mapping = {
    "nearest_neighbor": "Nearest Neighbor",
    "savings_clark_wright": "Clarke-Wright Savings",
    "nn_lambda_opt": "NN + Intra-Route LS",
    "savings_lambda_opt": "Savings + Intra-Route LS",
    "nn_improvement": "NN + Full Local Search",
    "savings_improvement": "Savings + Full Local Search",
    "iterated_local_search": "ILS"
}


def generate_latex_table_for_test_instances(df):
    df = df.round({
        "UB": 4,
        "entropy": 4
    })
    df = df.rename(columns=column_mapping)
    df = df.fillna('-')
    latex_str = df.to_latex(index=False, header=True, float_format="%.3f")
    return latex_str


def generate_latex_table_for_solution_overview(group_df):
    df = group_df.copy()

    df["relative_distance"] = df["total_distance"] / df["UB"]
    df["duration_μs"] = df["duration_μs"] / 1e3

    summary = df.groupby("algorithm").agg({
        "duration_μs": "mean",
        "number_of_iterations": "mean",
        "number_of_vehicles": "mean",
        "total_distance": "mean",
        "relative_distance": ["mean", "min", "max"]
    }).reset_index()

    summary.columns = ['algorithm', 'duration_μs', 'number_of_iterations', 'number_of_vehicles',
                       'total_distance', 'relative_distance', 'best_relative_distance', 'worst_relative_distance']

    summary = summary.round({
        "duration_μs": 4,
        "number_of_iterations": 4,
        "number_of_vehicles": 4,
        "total_distance": 4,
        "relative_distance": 4,
        "best_relative_distance": 4,
        "worst_relative_distance": 4
    })

    summary = summary.rename(columns=column_mapping_solution)
    latex_str = summary.to_latex(index=False, header=True, escape=False, float_format="%.3f", decimal=',')

    return latex_str
