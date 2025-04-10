import sys

import pandas as pd
from matplotlib import pyplot as plt
import seaborn as sns

from scripts.file_helper import *
from scripts.xml_parser import *


def run_statistics(nodes, vehicle_profile, solution_routes):
    print("hello")


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


def plot_performance(test_df, perf_df, output_dir):
    merged_df = pd.merge(perf_df, test_df, on="instance_name", how="left").sort_values("n")
    groups = split_by_test_group(merged_df)

    for name, group_df in groups.items():
        plot_instance_time_taken(group_df, output_dir, test_group=name)
        plot_total_distance(group_df, output_dir, test_group=name)
        plot_total_routes(group_df, output_dir, test_group=name)
        plot_rel_distance(group_df, output_dir, test_group=name)
        plot_rel_distance_vs_entropy(group_df, output_dir, test_group=name)


def split_by_test_group(merged_df):
    groups = {
        'augerat': merged_df[merged_df["folder_name"] == 'augerat_1995_set_a'].copy(),
        'christofides': merged_df[merged_df["folder_name"] == 'christofides_et_al_1979_cmt'].copy(),
        'uchoa': merged_df[merged_df["folder_name"] == 'uchoa_et_al_2014'].copy()
    }
    return groups


def plot_instance_time_taken(df, output_dir, test_group=""):
    avg_df = df.groupby(["n", "algorithm"], as_index=False)["duration_μs"].mean()

    plt.figure(figsize=(14, 6))
    sns.lineplot(data=avg_df, x="n", y="duration_μs", hue="algorithm", marker="o")
    plt.title(f"Computation time per Instance (μs) - {test_group.capitalize()} Instances")
    plt.xlabel("Number of nodes")
    plt.ylabel("Time (μs)")
    plt.tight_layout()
    plt.grid(True)
    file_name = f"computation_time_line_{test_group}.png"
    plt.savefig(os.path.join(output_dir, file_name))
    plt.close()


def plot_total_distance(df, output_dir, test_group=""):
    avg_df = df.groupby(["n", "algorithm"], as_index=False)["total_distance"].mean()
    avg_ub_df = df.groupby("n", as_index=False)["UB"].mean()

    plt.figure(figsize=(14, 6))
    sns.lineplot(data=avg_df, x="n", y="total_distance", hue="algorithm", marker="o", legend=True)
    plt.plot(avg_ub_df["n"], avg_ub_df["UB"], color="black", linestyle="--", marker="x", label="BK-distance")
    plt.title(f"Total distance per number of nodes (mean) - {test_group.capitalize()} Instances")
    plt.xlabel("Number of nodes")
    plt.ylabel("Total distance")
    plt.tight_layout()
    plt.grid(True)
    file_name = f"total_distance_with_bk_{test_group}.png"
    plt.savefig(os.path.join(output_dir, file_name))
    plt.close()


def plot_total_routes(df, output_dir, test_group=""):
    df["relative_route_number"] = df["number_of_vehicles"] / df["K"]
    avg_df = df.groupby(["n", "algorithm"], as_index=False)["relative_route_number"].mean()

    plt.figure(figsize=(14, 6))
    sns.lineplot(data=avg_df, x="n", y="relative_route_number", hue="algorithm", marker="o")
    plt.axhline(1.0, color="black", linestyle="--", linewidth=2.5, label="Optimal (UB)")

    plt.title(f"Relative number or routes to optimal - {test_group.capitalize()} Instances")
    plt.xlabel("Number of nodes")
    plt.ylabel("Relative route-count (taken/most feasible)")
    plt.tight_layout()
    plt.grid(True)
    plt.legend()
    file_name = f"relative_routes_to_optimal_{test_group}.png"
    plt.savefig(os.path.join(output_dir, file_name))
    plt.close()


def plot_rel_distance(df, output_dir, test_group=""):
    df["relative_distance"] = df["total_distance"] / df["UB"]

    avg_rel_df = df.groupby(["n", "algorithm"], as_index=False)["relative_distance"].mean()

    plt.figure(figsize=(14, 6))
    sns.lineplot(data=avg_rel_df, x="n", y="relative_distance", hue="algorithm", marker="o")
    plt.axhline(1.0, color="black", linestyle="--", linewidth=2.5, label="Optimal (UB)")

    plt.title(f"Relative distance to optimal - {test_group.capitalize()} Instances")
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

    plt.title(f"Relative distance vs entropy - {test_group.capitalize()} Instances")
    plt.xlabel("Entropy (binned)")
    plt.ylabel("Relative Distance (total_distance / UB)")
    plt.grid(True)
    plt.tight_layout()
    plt.legend(title="Algorithm")
    file_name = f"relative_distance_vs_entropy_{test_group}.png"
    plt.savefig(os.path.join(output_dir, file_name))
    plt.close()
