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

inline std::string to_string(const AlgorithmType algo) {
    switch (algo) {
        case AlgorithmType::NearestNeighbor: return "nearest_neighbor";
        case AlgorithmType::SavingsClarkWright: return "savings_clark_wright";
        default: return "Unknown";
    }
}

inline AlgorithmType algorithmFromString(const std::string &str) {
    if (str == "nearest_neighbor") return AlgorithmType::NearestNeighbor;
    if (str == "savings_clark_wright") return AlgorithmType::SavingsClarkWright;
    throw std::invalid_argument("Unknown algorithm: " + str);
}

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
};

#endif //PROGRAM_HELPER_H
