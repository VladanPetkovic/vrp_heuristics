import argparse
from scripts.analysis import analyze

# TODO: we only need test_data_analyzed.csv
# --> therefore another main, that merges all three and evaluates customers and depot-location
parser = argparse.ArgumentParser(description="Analyze VRP-heuristic solution from XML")
parser.add_argument('input_file', type=str, help="file-path to the XML graph")
parser.add_argument('solution_file', type=str, help="path to the XML solution")

args = parser.parse_args()
analyze(args.input_file, args.solution_file)

# TODO
# 1. analyze the test_data (data.csv)--> customer and depot-location is missing (save and reuse)
# --> entropy of nodes is missing
# 2. combine with solution (in memory)
# --> because we are doing this every time again

# as a result:
# plots for: (and data)
# --> (instance, time-taken of algorithm)
# --> (instance, routes-sum of algorithm)
# --> (instance, distance-sum of algorithm) (with optimal solution and percentage to optimal)
# --> (depot-location, distance-sum of algorithm) (with optimal solution)
# --> (customer-grouping, distance-sum of algorithm) (with optimal solution)
