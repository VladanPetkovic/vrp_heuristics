import argparse
from scripts.analysis import *
from scripts.data_preparation import *

# run this to prepare the test_data (only once needed)
prepare_data()

# run this to analyze the solution
analyze_solution()

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
