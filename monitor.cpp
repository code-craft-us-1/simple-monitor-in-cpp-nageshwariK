#include "./monitor.h"
#include <assert.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <string>
#include <vector>

void CheckVitals::displayWarning(const std::string& message) {
    std::cout << message << "\n";
    for (int i = 0; i < 6; i++) {
        std::cout << "\r* " << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "\r *" << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

// Helper functions to check each vital
bool isTemperatureCritical(double temperature) {
    return temperature > 102 || temperature < 95;
}

bool isPulseRateOutOfRange(double pulseRate) {
    return pulseRate < 60 || pulseRate > 100;
}

bool isSpo2OutOfRange(double spo2) {
    return spo2 < 90;
}

bool CheckVitals::checkVital(double value, bool (*checkFunc)(double), const std::string& message) {
    if (checkFunc(value)) {
        displayWarning(message);
        return false; // Indicates a vital is not okay
    }
    return true; // Indicates the vital is okay
}

// Function to check if vitals are ok
int CheckVitals::vitalsOk(double temperature, double pulseRate, double spo2) {
    bool tempCheck = checkVital(temperature, isTemperatureCritical, "Temperature is critical!");
    bool pulseCheck = checkVital(pulseRate, isPulseRateOutOfRange, "Pulse Rate is out of range!");
    bool spo2Check = checkVital(spo2, isSpo2OutOfRange, "Oxygen Saturation out of range!");

    // If all checks passed
    return (tempCheck && pulseCheck && spo2Check) ? 1 : 0;
}