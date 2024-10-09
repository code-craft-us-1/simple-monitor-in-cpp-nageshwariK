#include "./monitor.h"
#include <assert.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <string>

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
bool CheckVitals::isTemperatureCritical(double temperature) {
    return temperature > 102 || temperature < 95;
}

bool CheckVitals::isPulseRateOutOfRange(double pulseRate) {
    return pulseRate < 60 || pulseRate > 100;
}

bool CheckVitals::isSpo2OutOfRange(double spo2) {
    return spo2 < 90;
}

// Function to check if vitals are ok
int CheckVitals::vitalsOk(double temperature, double pulseRate, double spo2) {
    // Store condition functions and messages in pairs
    struct Check {
        bool (*func)(double);
        const char* message;
    };

    Check checks[] = {
        { isTemperatureCritical, "Temperature is critical!" },
        { isPulseRateOutOfRange, "Pulse Rate is out of range!" },
        { isSpo2OutOfRange, "Oxygen Saturation out of range!" }
    };

    // Corresponding values for each check
    double values[] = { temperature, pulseRate, spo2 };

    // Iterate through each check
    for (int i = 0; i < 3; ++i) {
        if (checks[i].func(values[i])) {
            displayWarning(checks[i].message);
            return 0;  // Return 0 if any condition is met
        }
    }

    return 1;  // Return 1 if all vitals are normal
}

