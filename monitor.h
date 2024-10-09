#pragma once
#include <iostream>

class CheckVitals{

public:
    bool isTemperatureCritical(double temperature);
    bool isPulseRateOutOfRange(double pulseRate);
    bool isSpo2OutOfRange(double spo2);
    void displayWarning(const std::string& message);
    int vitalsOk(double temperature, double pulseRate, double spo2);
};