#include "./monitor.h"
#include <assert.h>
#include <thread>
#include <chrono>
#include <iostream>

std::string CheckVitals::checkVitals(double temperature, double pulseRate, double spo2) {
    // Array of checks
    VitalCheck checks[] = {
        {temperature >= 102 || temperature < 95, "Temperature is critical!"},
        {pulseRate < 60 || pulseRate >= 100, "Pulse Rate is out of range!"},
        {spo2 < 90, "Oxygen Saturation out of range!"}
    };

    // Loop through checks
    for (const auto& check : checks) {
        if (check.condition) {
            return check.message;
        }
    }
    return ""; // No issues
}
void CheckVitals::displayWarning(const std::string& message) {
    std::cout << message << "\n";
    for (int i = 0; i < 6; i++) {
        std::cout << "\r* " << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "\r *" << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int CheckVitals::vitalsOk(double temperature, double pulseRate, double spo2) {
    std::string warningMessage = checkVitals(temperature, pulseRate, spo2);
    if (!warningMessage.empty()) {
        displayWarning(warningMessage);
        return 0;
    }
    return 1;
}

