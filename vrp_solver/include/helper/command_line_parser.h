//
// Created by petkovic on 26.03.25.
//

#ifndef PROGRAM_HELPER_H
#define PROGRAM_HELPER_H

#include <iostream>
#include <getopt.h>
#include <string>

enum class AlgorithmType {
    NearestNeighbor,
    SavingsClarkWright
};

struct ArgumentOptions {
    std::string inputFilePath;
    std::string outputFilePath;
    AlgorithmType algorithm; // this would be the enum
};

class CommandLineParser {
public:
    static void parseArguments(ArgumentOptions &programOptions, int argc, char *argv[]);

private:
    static void printUsageAndExit();

    static AlgorithmType algorithmFromString(const std::string &str);
};

#endif //PROGRAM_HELPER_H
