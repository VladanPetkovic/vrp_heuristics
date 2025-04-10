import argparse
from scripts.analysis import *
from scripts.data_preparation import *

# run this to prepare the test_data (only once needed)
# prepare_data() # done

# run this to analyze the solution
parser = argparse.ArgumentParser(description="Analyze performance of heuristics")
parser.add_argument('input_file', type=str, help="file-path to performance-data")
parser.add_argument('output_dir', type=str, help="path to output-directory, where to save plots")

args = parser.parse_args()
analyze_solution(args.input_file, args.output_dir)

### as a result:
### plots for: (and data)
### --> (instance, time-taken of algorithm)
### --> (instance, routes-sum of algorithm)
### --> (instance, distance-sum of algorithm) (with optimal solution and percentage to optimal)
# --> (number of routes, distance-sum) --> check the relation between num_routes and distance_total
# --> (depot-location, distance-sum of algorithm) (with optimal solution)
# --> (customer-grouping, distance-sum of algorithm) (with optimal solution) TODO: make better
