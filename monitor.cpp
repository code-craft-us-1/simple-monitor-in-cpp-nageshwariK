#include "./monitor.h"
#include <assert.h>
#include <thread>
#include <chrono>
#include <iostream>

std::string CheckVitals::checkVitals(double temperature, double pulseRate, double spo2) {
    if (temperature > 102 || temperature < 95) {
        return "Temperature is critical!";
    }
    if (pulseRate < 60 || pulseRate > 100) {
        return "Pulse Rate is out of range!";
    }
    if (spo2 < 90) {
        return "Oxygen Saturation out of range!";
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

