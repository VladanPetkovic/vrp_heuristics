import sys

import pandas as pd
from matplotlib import pyplot as plt
import seaborn as sns

from scripts.file_helper import *
from scripts.latex_helper import *


def analyze_solution(performance_file_path, output_dir):
    csv_path = 'test_data/data_stats.csv'
    if not file_exists(csv_path) or not file_exists(performance_file_path):
        print("One of the csv-file does not exist")
        sys.exit(1)
    if not dir_exists(output_dir):
        print("Output directory does not exist")
        sys.exit(1)

    test_df = pd.read_csv(csv_path, sep=';')
    perf_df = pd.read_csv(performance_file_path, sep=';')

    plot_performance(test_df, perf_df, output_dir)
    generate_latex_table_for_test_instances(test_df)


def plot_performance(test_df, perf_df, output_dir):
    merged_df = pd.merge(perf_df, test_df, on="instance_name", how="left").sort_values("n")
    merged_df["algorithm"] = merged_df["algorithm"].map(algorithm_mapping)
    groups = split_by_test_group(merged_df)
    plot_performance_overview(merged_df, output_dir)

    for name, group_df in groups.items():
        plot_instance_time_taken(group_df, output_dir, test_group=name)
        plot_total_distance(group_df, output_dir, test_group=name)
        plot_relative_distance_vs_depot_orientation(group_df, output_dir, test_group=name)
        plot_routes_count_distance_relation(group_df, output_dir, test_group=name)
        plot_route_length_distance_relation(group_df, output_dir, test_group=name)
        plot_rel_distance(group_df, output_dir, test_group=name)
        plot_rel_distance_vs_entropy(group_df, output_dir, test_group=name)

    generate_latex_table_for_solution_overview(merged_df[merged_df["folder_name"] == 'augerat_1995_set_a'])
    generate_latex_table_for_solution_overview(merged_df[merged_df["folder_name"] == 'christofides_et_al_1979_cmt'])
    generate_latex_table_for_solution_overview(merged_df[merged_df["folder_name"] == 'uchoa_et_al_2014'])


def split_by_test_group(merged_df):
    groups = {
        'augerat': merged_df[merged_df["folder_name"] == 'augerat_1995_set_a'].copy(),
        'christofides': merged_df[merged_df["folder_name"] == 'christofides_et_al_1979_cmt'].copy(),
        'uchoa': merged_df[merged_df["folder_name"] == 'uchoa_et_al_2014'].copy()
    }
    return groups


# This function plots the relative-distance of all algorithms across all tests
def plot_performance_overview(df, output_dir, test_group=""):
    df["relative_distance"] = df["total_distance"] / df["UB"]

    # horizontal position
    plt.figure(figsize=(14, 6))
    sns.boxplot(data=df, x="algorithm", y="relative_distance")
    plt.axhline(1.0, color="black", linestyle="--", linewidth=2.5, label="Optimal (UB)")
    plt.title(f"Relative distance by heuristic - All instances")
    plt.xlabel("Heuristic")
    plt.ylabel("Relative Distance (taken / optimal)")
    plt.grid(True, which="both", ls="--", alpha=0.7)
    plt.tight_layout()
    plt.legend()
    file_name_horiz = f"performance_overview_all.png"
    plt.savefig(os.path.join(output_dir, file_name_horiz))
    plt.close()


def plot_instance_time_taken(df, output_dir, test_group=""):
    avg_df = df.groupby(["n", "algorithm"], as_index=False)["duration_μs"].mean()
    avg_df["duration_ms"] = avg_df["duration_μs"] / 1000

    plt.figure(figsize=(14, 6))
    sns.lineplot(data=avg_df, x="n", y="duration_ms", hue="algorithm", marker="o")
    plt.yscale('log')
    plt.title(f"Computation time per Instance (ms) - {test_group.capitalize()} instances")
    plt.xlabel("Number of nodes")
    plt.ylabel("Time (ms, log scale)")
    plt.tight_layout()
    plt.grid(True, which="both", ls="--")
    file_name = f"computation_time_line_{test_group}.png"
    plt.savefig(os.path.join(output_dir, file_name))
    plt.close()


def plot_total_distance(df, output_dir, test_group=""):
    avg_df = df.groupby(["n", "algorithm"], as_index=False)["total_distance"].mean()
    avg_ub_df = df.groupby("n", as_index=False)["UB"].mean()

    plt.figure(figsize=(14, 6))
    sns.lineplot(data=avg_df, x="n", y="total_distance", hue="algorithm", marker="o", legend=True)
    plt.plot(avg_ub_df["n"], avg_ub_df["UB"], color="black", linestyle="--", marker="x", label="BK-distance")
    plt.title(f"Total distance per number of nodes (mean) - {test_group.capitalize()} instances")
    plt.xlabel("Number of nodes")
    plt.ylabel("Total distance")
    plt.tight_layout()
    plt.grid(True)
    plt.legend()
    file_name = f"total_distance_with_bk_{test_group}.png"
    plt.savefig(os.path.join(output_dir, file_name))
    plt.close()


# This function plots the relative-distance to the relative depot location (horizontal)
def plot_relative_distance_vs_depot_orientation(df, output_dir, test_group=""):
    df["relative_distance"] = df["total_distance"] / df["UB"]

    # horizontal position
    plt.figure(figsize=(14, 6))
    sns.boxplot(data=df, x="depot_rel_horiz_pos", y="relative_distance", hue="algorithm")
    plt.axhline(1.0, color="black", linestyle="--", linewidth=2.5, label="Optimal (UB)")
    plt.title(f"Relative distance by depot horizontal position - {test_group.capitalize()} instances")
    plt.xlabel("Depot relative horizontal position")
    plt.ylabel("Relative distance (taken / optimal)")
    plt.grid(True)
    plt.tight_layout()
    file_name_horiz = f"relative_distance_vs_depot_rel_horiz_pos_{test_group}.png"
    plt.savefig(os.path.join(output_dir, file_name_horiz))
    plt.close()


# x = number of routes
# y = relative distance (to optimal)
def plot_routes_count_distance_relation(df, output_dir, test_group=""):
    df["relative_distance"] = df["total_distance"] / df["UB"]
    avg_df = df.groupby(["number_of_vehicles", "algorithm"], as_index=False)["relative_distance"].mean()

    plt.figure(figsize=(14, 6))
    sns.lineplot(data=avg_df, x="number_of_vehicles", y="relative_distance", hue="algorithm", marker="o")
    plt.axhline(1.0, color="black", linestyle="--", linewidth=2.5, label="Optimal (UB)")

    plt.title(f"Relative distance for number of routes - {test_group.capitalize()} instances")
    plt.xlabel("Number of routes")
    plt.ylabel("Relative distance (taken/optimal)")
    plt.tight_layout()
    plt.grid(True)
    plt.legend()
    file_name = f"relative_distance_to_route_count_{test_group}.png"
    plt.savefig(os.path.join(output_dir, file_name))
    plt.close()


# x = route length
# y = relative distance (to optimal)
def plot_route_length_distance_relation(df, output_dir, test_group=""):
    df["relative_distance"] = df["total_distance"] / df["UB"]
    df["avg_route_length"] = (df["n"] - 1) / df["number_of_vehicles"]
    avg_df = df.groupby(["avg_route_length", "algorithm"], as_index=False)["relative_distance"].mean()

    plt.figure(figsize=(14, 6))
    sns.lineplot(data=avg_df, x="avg_route_length", y="relative_distance", hue="algorithm", marker="o")
    plt.axhline(1.0, color="black", linestyle="--", linewidth=2.5, label="Optimal (UB)")

    plt.title(f"Relative distance for average number of customers per route - {test_group.capitalize()} instances")
    plt.xlabel("Number of customers per route")
    plt.ylabel("Relative distance (taken/optimal)")
    plt.tight_layout()
    plt.grid(True)
    plt.legend()
    file_name = f"relative_distance_to_route_length_{test_group}.png"
    plt.savefig(os.path.join(output_dir, file_name))
    plt.close()


def plot_rel_distance(df, output_dir, test_group=""):
    df["relative_distance"] = df["total_distance"] / df["UB"]

    avg_rel_df = df.groupby(["n", "algorithm"], as_index=False)["relative_distance"].mean()

    plt.figure(figsize=(14, 6))
    sns.lineplot(data=avg_rel_df, x="n", y="relative_distance", hue="algorithm", marker="o")
    plt.axhline(1.0, color="black", linestyle="--", linewidth=2.5, label="Optimal (UB)")

    plt.title(f"Relative distance to optimal - {test_group.capitalize()} instances")
    plt.xlabel("Number of nodes")
    plt.ylabel("Relative distance (taken/optimal)")
    plt.grid(True)
    plt.tight_layout()
    plt.legend()
    file_name = f"relative_distance_to_optimal_{test_group}.png"
    plt.savefig(os.path.join(output_dir, file_name))
    plt.close()


def plot_rel_distance_vs_entropy(df, output_dir, test_group=""):
    df["relative_distance"] = df["total_distance"] / df["UB"]

    df = df.sort_values("entropy")

    plt.figure(figsize=(14, 6))
    sns.lineplot(data=df, x="entropy", y="relative_distance", hue="algorithm", marker="o")
    plt.axhline(1.0, color="black", linestyle="--", linewidth=2.5, label="Optimal (UB)")

    plt.title(f"Relative distance vs entropy - {test_group.capitalize()} instances")
    plt.xlabel("Entropy (binned)")
    plt.ylabel("Relative Distance (total_distance / UB)")
    plt.grid(True)
    plt.tight_layout()
    plt.legend(title="Algorithm")
    file_name = f"relative_distance_vs_entropy_{test_group}.png"
    plt.savefig(os.path.join(output_dir, file_name))
    plt.close()
