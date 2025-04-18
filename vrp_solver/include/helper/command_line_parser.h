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
    NNLambdaOpt,
    SavingsLambdaOpt,
    NNImprovement,
    SavingsImprovement
};

inline std::string to_string(const AlgorithmType algo) {
    switch (algo) {
        case AlgorithmType::NearestNeighbor: return "nearest_neighbor";
        case AlgorithmType::SavingsClarkWright: return "savings_clark_wright";
        case AlgorithmType::NNLambdaOpt: return "nn_lambda_opt";
        case AlgorithmType::SavingsLambdaOpt: return "savings_lambda_opt";
        case AlgorithmType::NNImprovement: return "nn_improvement";
        case AlgorithmType::SavingsImprovement: return "savings_improvement";
        default: return "Unknown";
    }
}

inline AlgorithmType algorithmFromString(const std::string &str) {
    if (str == "nearest_neighbor") return AlgorithmType::NearestNeighbor;
    if (str == "savings_clark_wright") return AlgorithmType::SavingsClarkWright;
    if (str == "nn_lambda_opt") return AlgorithmType::NNLambdaOpt;
    if (str == "savings_lambda_opt") return AlgorithmType::SavingsLambdaOpt;
    if (str == "nn_improvement") return AlgorithmType::NNImprovement;
    if (str == "savings_improvement") return AlgorithmType::SavingsImprovement;
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
