//
// Created by petkovic on 26.03.25.
//

#ifndef PROGRAM_HELPER_H
#define PROGRAM_HELPER_H

#include <iostream>
#include <getopt.h>
#include <string>

struct ProgramOptions {
    std::string inputFilePath;
    std::string outputFilePath;
};

class ProgramHelper {
public:
    static void parseArguments(ProgramOptions &programOptions, int argc, char* argv[]);

private:
    static void printUsageAndExit() const;
};

#endif //PROGRAM_HELPER_H
