//
// Created by petkovic on 26.03.25.
//

#include <helper/command_line_parser.h>

void CommandLineParser::parseArguments(ArgumentOptions &programOptions, const int argc, char *argv[]) {
    int opt;
    bool hasInput = false, hasOutput = false, hasAlgorithm = false;

    while ((opt = getopt(argc, argv, "i:o:a:")) != -1) {
        switch (opt) {
            case 'i':
                programOptions.inputFilePath = optarg;
                hasInput = true;
                break;
            case 'o':
                programOptions.outputFilePath = optarg;
                hasOutput = true;
                break;
            case 'a':
                programOptions.algorithm = algorithmFromString(optarg);
                hasAlgorithm = true;
                break;
            default:
                printUsageAndExit();
        }
    }

    if (!(hasInput && hasOutput && hasAlgorithm)) {
        std::cerr << "Error: -i, -o and -a options are required.\n";
        printUsageAndExit();
    }
}

void CommandLineParser::printUsageAndExit() {
    std::cerr << "Usage: ./vrp_solver "
            << "\n\tRequired arguments:"
            << "\n\t\t-i <input_file_path>       Path to input file"
            << "\n\t\t-o <output_file_path>      Path to output file"
            << "\n\t\t-a <algorithm_name>        Algorithm to use"
            << "\n\t\t                          Options: nearest_neighbor, savings_clark_wright\n";
    exit(EXIT_FAILURE);
}
