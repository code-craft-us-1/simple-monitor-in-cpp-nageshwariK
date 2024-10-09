#pragma once
#include <iostream>
#include <string>

class CheckVitals {
    struct VitalCheck {
        double value;
        bool (*checkFunc)(double);
        const char* message;
    };

 public:
    void displayWarning(const std::string& message);
    int vitalsOk(double temperature, double pulseRate, double spo2);
    bool checkVital(double value, bool (*checkFunc)(double), const std::string& message);
};
