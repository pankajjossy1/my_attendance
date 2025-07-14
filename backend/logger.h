#pragma once

#include <fstream>
#include <string>
#include <ctime>
#include <filesystem>

inline void write_log(const std::string& message) {
    // Ensure the logs directory exists
    std::filesystem::create_directories("backend/logs");

    // Open log file in append mode
    std::ofstream log_file("backend/logs/server.log", std::ios::app);

    if (log_file.is_open()) {
        // Get current time for timestamp
        std::time_t now = std::time(nullptr);
        char timestamp[100];
        std::strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", std::localtime(&now));

        // Write the timestamped message to the log file
        log_file << "[" << timestamp << "] INFO: " << message << std::endl;
    }
}
