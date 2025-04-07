import argparse
from scripts.analysis import analyze

parser = argparse.ArgumentParser(description="Analyze VRP-heuristic solution from XML")
parser.add_argument('input_file', type=str, help="file-path to the XML graph")
parser.add_argument('solution_file', type=str, help="path to the XML solution")

args = parser.parse_args()
analyze(args.input_file, args.solution_file)


# was will ich machen
# --> die Lösung analysieren (sum_distance, routes_sum, entropy and number of nodes)
# --> Heuristiken miteiander vergleichen
# --> --> % distance_sum (to opt-solution),...
# --> --> data for a table (of all heuristics)
# --> --> plots for different metrics (given all heuristics)


# Solution
# 1. analyze every solution and save data to csv (unique for file_name and heuristic)
# 2. compare solutions all together
