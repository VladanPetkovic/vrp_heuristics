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
    SavingsClarkWright,
    LambdaOptNN,
    LambdaOptSavings,
    LambdaInterchangeNN,
    LambdaInterchangeSavings
};

inline std::string to_string(const AlgorithmType algo) {
    switch (algo) {
        case AlgorithmType::NearestNeighbor: return "nearest_neighbor";
        case AlgorithmType::SavingsClarkWright: return "savings_clark_wright";
        case AlgorithmType::LambdaOptNN: return "lambda_opt_nn";
        case AlgorithmType::LambdaOptSavings: return "lambda_opt_savings";
        case AlgorithmType::LambdaInterchangeNN: return "lambda_interchange_nn";
        case AlgorithmType::LambdaInterchangeSavings: return "lambda_interchange_savings";
        default: return "Unknown";
    }
}

inline AlgorithmType algorithmFromString(const std::string &str) {
    if (str == "nearest_neighbor") return AlgorithmType::NearestNeighbor;
    if (str == "savings_clark_wright") return AlgorithmType::SavingsClarkWright;
    if (str == "lambda_opt_nn") return AlgorithmType::LambdaOptNN;
    if (str == "lambda_opt_savings") return AlgorithmType::LambdaOptSavings;
    if (str == "lambda_interchange_nn") return AlgorithmType::LambdaInterchangeNN;
    if (str == "lambda_interchange_savings") return AlgorithmType::LambdaInterchangeSavings;
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
