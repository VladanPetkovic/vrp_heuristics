//
// Created by petkovic on 26.03.25.
//

#include <helper/command_line_parser.h>

void CommandLineParser::parseArguments(ArgumentOptions &programOptions, const int argc, char *argv[]) {
    int opt;
    bool hasInput = false, hasOutput = false;

    while ((opt = getopt(argc, argv, "i:o:")) != -1) {
        switch (opt) {
            case 'i':
                programOptions.inputFilePath = optarg;
                hasInput = true;
                break;
            case 'o':
                programOptions.outputFilePath = optarg;
                hasOutput = true;
                break;
            default:
                printUsageAndExit();
        }
    }

    if (!(hasInput && hasOutput)) {
        std::cerr << "Error: Both -i and -o options are required.\n";
        printUsageAndExit();
    }
}

void CommandLineParser::printUsageAndExit() {
    std::cerr << "Usage: ./vrp_solver "
                 "\n\t\t-i <input_file_path> "
                 "\n\t\t-o <output_file_path>\n";
    exit(EXIT_FAILURE);
}
