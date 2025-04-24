//
// Created by petkovic on 24.04.25.
//

#include <helper/log_helper.h>

std::ofstream LogHelper::logfile;

void LogHelper::init(const std::string &filepath) {
    if (filepath.empty()) {
        return;
    }
    logfile.open(filepath, std::ios::app);
    if (!logfile.is_open()) {
        std::cerr << "Failed to open log file: " << filepath << std::endl;
    }
}

void LogHelper::log(double best, double current, double temp) {
    if (logfile.is_open()) {
        logfile << best << "\t" << current << "\t" << temp << std::endl;
    }
}
