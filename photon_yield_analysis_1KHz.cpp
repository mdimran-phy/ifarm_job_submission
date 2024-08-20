#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cmath>
#include <filesystem> // C++17 standard header for filesystem operations
namespace fs = std::filesystem;

// Function to parse each line of the log file and extract detected photon count
int parseLogFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 0; // Return 0 to indicate failure
    }

    std::string line;
    int totalEvents = 0;
    int totalDetectedPhotons = 0;

    while (std::getline(file, line)) {
        if (line.find("Cherenkov photons:") != std::string::npos) {
            // Extracting detected photon count
            std::istringstream iss(line);
            std::string token;
            while (iss >> token) {
                if (token == ":") {
                    iss >> token;
                    totalDetectedPhotons += std::stoi(token);
                    totalEvents++;
                    break;
                }
            }
        }
    }

    file.close();

    if (totalEvents > 0) {
        int averageDetectedPhotons = totalDetectedPhotons / totalEvents;
        std::cout << "Average detected photons in file " << filename << ": " << averageDetectedPhotons << std::endl;
        return averageDetectedPhotons;
    } else {
        std::cerr << "No valid data found in file: " << filename << std::endl;
        return 0; // Return 0 if no valid data was found
    }
}

int main() {
    std::string directory = "/w/halld-scshelf2101/halld3/home/ihossain/ti_dn_1KHz_32_pixel_out/log/";

    int totalFiles = 0;
    int totalDetectedPhotons = 0;

    for (const auto& entry : fs::directory_iterator(directory)) {
        if (entry.is_regular_file()) {
            std::string filename = entry.path().string();
            if (filename.find("slurm-") != std::string::npos && filename.find("_events.out") != std::string::npos) {
                int detectedPhotons = parseLogFile(filename);
                totalDetectedPhotons += detectedPhotons;
                
                totalFiles++;
            }
        }
    }

    if (totalFiles > 0) {
        int overallAverageDetectedPhotons = totalDetectedPhotons / totalFiles;
        std::cout << "Overall average detected photons: " << overallAverageDetectedPhotons << std::endl;
    } else {
        std::cerr << "No log files found in directory: " << directory << std::endl;
    }

    return 0;
}