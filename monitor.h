#pragma once
#include <iostream>

class CheckVitals
{
public:
    std::string checkVitals(double temperature, double pulseRate, double spo2);
    void displayWarning(const std::string& message);
    int vitalsOk(double temperature, double pulseRate, double spo2);
};

