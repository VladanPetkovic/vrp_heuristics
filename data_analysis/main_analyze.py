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
### --> (routes-sum of algorithm, distance-sum)
### --> (instance, distance-sum of algorithm) (with optimal solution and percentage to optimal)
### --> (depot-location, distance-sum of algorithm) (with optimal solution)
### --> (customer-grouping, distance-sum of algorithm) (with optimal solution)

# ------------------- TABLES

### general overview
### --> nearest neighbor, savings, improvement heuristics, ils
### --> grouped for every test-set:
### --> --> average duration, avg number of iterations (only ils), number of vehicles, total_distance
### --> --> total distance relative to optimal

### instances
### --> instance_name;n;K;Q;UB;BK;entropy;depot_abs_pos;depot_rel_horiz_pos;depot_rel_vert_pos