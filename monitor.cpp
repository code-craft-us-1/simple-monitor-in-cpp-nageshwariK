#include "./monitor.h"
#include <assert.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <string>
#include <vector>

CheckVitals::Language currentLanguage = CheckVitals::Language::English; // Default language
static std::string transMessage = "";

//CheckVitals::~CheckVitals()
//{
//     delete message;
//}

void CheckVitals::displayWarning(const std::string& message) {
    std::cout << message << "\n";
    for (int i = 0; i < 6; i++) {
        std::cout << "\r* " << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "\r *" << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

bool isVitalInRange(const double min, const double max, const double value) {
    return value >= min && value <= max;
}

// Function to retrieve the translation for the given key
std::string getTranslation(const std::string& key) {
    std::string str = "";
    if (translations.find(key) != translations.end()) {
        const Translation& translation = translations[key];
        
        switch (currentLanguage){
        case CheckVitals::Language::English:
            str = translation.english;
            break;
        case CheckVitals::Language::German:
            str = translation.german;
            break;
        }
    }
    return str;
}

// Helper functions to check each vital
bool isTemperatureNotNormal(double temperature) {
    bool val = false;
    std::string str = "";
    if (!isVitalInRange(95, 102, temperature))
    {
        str = "temp_critical";
        
        val = true;
    }
    else if (isVitalInRange(102 - (102.0 * 0.015), 102, temperature))
    {
        str = "warning_hyperthermia";
        val = true;
    }
    else if (isVitalInRange(95, 95 + (95 * 0.015), temperature))
    {
        str = "warning_hypothermia";
        val = true;
    }
    if (!str.empty())
    {
       transMessage = getTranslation(str);
    }
    return val;
}

bool isPulseRateNotNormal(double pulseRate) {
    bool val = false;
    std::string str = "";
    if (!isVitalInRange(60, 100, pulseRate)) {
        str = "pulse_critical";
        val = true;
    }
    else if (isVitalInRange(100 - (100.0 * 0.015), 100, pulseRate)) {
        str = "warning_higherpulse";
        val = true;
    }
    else if (isVitalInRange(60, 60 + (60 * 0.015) , pulseRate)) {
        str = "warning_lowerpulse";
        val = true;
    }
    if (!str.empty()) {
       transMessage = getTranslation(str);
    }
    return val;
}

bool isSpo2NotNormal(double spo2) {
    bool val = false;
    std::string str = "";
    if (!isVitalInRange(90, std::numeric_limits<float>::max(), spo2)) {
        str = "spo2_critical";
        val = true;
    }
    else if (isVitalInRange(90, 90 + (90 * 0.015), spo2)) {
        str = "warning_lowSPO2";
        val = true;
    }
    if (!str.empty()) {
        transMessage = getTranslation(str);
    }
    return val;
}

// Function to check if vitals are ok
bool CheckVitals::vitalsOk(double temperature, double pulseRate, double spo2) {
    checks = {
          {temperature, isTemperatureNotNormal, transMessage},
          {pulseRate, isPulseRateNotNormal, transMessage},
          {spo2, isSpo2NotNormal, transMessage}
    };

    // Iterate through each vital check
    for (int i = 0; i < checks.size(); ++i) {
        if (checks[i].checkFunc(checks[i].value)) {
            checks[i].message = transMessage;
            displayWarning(checks[i].message);
            return false;  // Return 0 if any condition fails
        }
    }

    return true;  // Return 1 if all vitals are normal
}

void CheckVitals::SetLanguage(CheckVitals::Language language) {
    currentLanguage = language;
}

std::string CheckVitals::GetMessage()
{
    return transMessage;
}
