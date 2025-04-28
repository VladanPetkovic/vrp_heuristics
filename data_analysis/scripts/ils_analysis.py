import sys

import pandas as pd
from matplotlib import pyplot as plt
import numpy as np
from scipy.stats import gaussian_kde
import glob

from scripts.file_helper import *


def analyze_ils():
    output_dir = '../solution'
    log_dir = '../log/iterated_local_search'
    if not dir_exists(output_dir):
        print("Output directory does not exist")
        sys.exit(1)
    if not dir_exists(log_dir):
        print("Log directory does not exist")
        sys.exit(1)

    df = load_all_logs(log_dir)
    improvements = compute_improvements(df)
    plot_improvements_vs_temperature(improvements, output_dir)
    plot_histogram_of_improvements(improvements, output_dir)
    plot_avg_improvement_per_temp_bin(improvements, output_dir)


def load_all_logs(logs_dir):
    all_logs = []
    for filepath in glob.glob(os.path.join(logs_dir, "**", "*.txt"), recursive=True):
        df = pd.read_csv(filepath, sep="\t", header=None, names=["best_so_far", "current", "temperature"])
        df["instance"] = os.path.basename(filepath)  # track which file it came from
        all_logs.append(df)
    return pd.concat(all_logs, ignore_index=True)


def compute_improvements(df):
    df["best_so_far_shifted"] = df.groupby("instance")["best_so_far"].shift(1)
    # relative improvement: (previous - current) / previous
    df["relative_improvement"] = ((df["best_so_far_shifted"] - df["best_so_far"]) / df["best_so_far_shifted"]).fillna(0)
    improvements = df[df["relative_improvement"] > 0]
    return improvements


def plot_improvements_vs_temperature(improvements, output_dir):
    x = improvements["temperature"]
    y = improvements["relative_improvement"] * 100

    xy = np.vstack([np.log10(x), y])  # log scale on x-axis
    z = gaussian_kde(xy)(xy)  # density estimate

    idx = z.argsort()
    x, y, z = x.iloc[idx], y.iloc[idx], z[idx]

    plt.figure(figsize=(10, 6))
    scatter = plt.scatter(x, y, c=z, cmap='viridis', s=10, edgecolor='none', alpha=0.8)
    plt.xscale('log')
    plt.xlabel('Temperature (log scale)')
    plt.ylabel('Relative improvement (%)')
    plt.title('Relative improvements vs temperature')
    plt.colorbar(scatter, label='Density')
    plt.grid(True)
    plt.tight_layout()
    plt.savefig(os.path.join(output_dir, "global_improvements_vs_temperature.png"))
    plt.close()


def plot_histogram_of_improvements(improvements, output_dir):
    temperatures = improvements["temperature"]
    bins = np.logspace(np.log10(temperatures.min()), np.log10(temperatures.max()), 100)
    plt.figure(figsize=(10, 6))
    plt.hist(temperatures, bins=bins)
    plt.xscale('log')
    plt.xlabel('Temperature (log scale)')
    plt.ylabel('Number of Improvements')
    plt.title('Histogram of Temperatures where Improvements Occur')
    plt.grid(True)
    plt.tight_layout()
    plt.savefig(os.path.join(output_dir, "histogram_improvements_temperature.png"))
    plt.close()


def plot_avg_improvement_per_temp_bin(improvements, output_dir):
    temp_bins = pd.cut(improvements["temperature"], bins=20)
    avg_improvement = improvements.groupby(temp_bins)["relative_improvement"].mean() * 100

    plt.figure(figsize=(12, 6))
    avg_improvement.plot(kind='line', marker='o')
    plt.xlabel('Temperature bins')
    plt.ylabel('Average relative improvement (%)')
    plt.title('Average relative improvement per temperature range')
    plt.grid(True)
    plt.tight_layout()
    plt.savefig(os.path.join(output_dir, "average_improvement_per_temperature_bin.png"))
    plt.close()
