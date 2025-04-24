//
// Created by petkovic on 24.04.25.
//

#ifndef LOG_HELPER_H
#define LOG_HELPER_H

#include <fstream>
#include <string>
#include <iostream>

class LogHelper {
public:
    static void init(const std::string &filepath);

    static void log(double best, double current, double temp);

private:
    static std::ofstream logfile;
};


#endif //LOG_HELPER_H
