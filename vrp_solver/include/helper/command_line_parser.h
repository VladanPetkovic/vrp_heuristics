//
// Created by petkovic on 26.03.25.
//

#ifndef PROGRAM_HELPER_H
#define PROGRAM_HELPER_H

#include <iostream>
#include <getopt.h>
#include <string>

struct ArgumentOptions {
    std::string inputFilePath;
    std::string outputFilePath;
};

class CommandLineParser {
public:
    static void parseArguments(ArgumentOptions &programOptions, int argc, char* argv[]);

private:
    static void printUsageAndExit();
};

#endif //PROGRAM_HELPER_H
