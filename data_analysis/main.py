import argparse

from scripts.visualization import *

if __name__ == '__main__':
    # file_path = 'test_data/uchoa_et_al_2014/X-n101-k25.xml'
    # file_path = 'test_data/uchoa_et_al_2014/X-n1001-k43.xml'
    parser = argparse.ArgumentParser(description="Visualize VRP nodes from XML")
    parser.add_argument('input_file', type=str, help="file-path to the XML graph")
    parser.add_argument('output_file', type=str, help="file-path to save the output image")
    parser.add_argument('--solution_file', type=str, help="path to the XML solution", default=None)

    args = parser.parse_args()
    visualize(args.input_file, args.output_file, args.solution_file)
