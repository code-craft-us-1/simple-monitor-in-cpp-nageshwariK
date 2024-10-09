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
        return false;  // Indicates a vital is not okay
    }
    return true;  // Indicates the vital is okay
}

// Function to check if vitals are ok
int CheckVitals::vitalsOk(double temperature, double pulseRate, double spo2) {
    VitalCheck checks[] = {
         {temperature, isTemperatureCritical, "Temperature is critical!"},
         {pulseRate, isPulseRateOutOfRange, "Pulse Rate is out of range!"},
         {spo2, isSpo2OutOfRange, "Oxygen Saturation out of range!"}
    };

    // Iterate through each vital check
    for (int i = 0; i < 3; ++i) {
        if (checks[i].checkFunc(checks[i].value)) {
            displayWarning(checks[i].message);
            return 0;  // Return 0 if any condition fails
        }
    }

    return 1;  // Return 1 if all vitals are normal
}
