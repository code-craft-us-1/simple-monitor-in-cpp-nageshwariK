#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>

struct Translation {
    std::string key;
    std::string english;
    std::string german; // Add more languages as needed
};

static std::map<std::string, Translation> translations = {
    {"greeting", {"greeting", "Hello", "Hola"}},
    {"warning_hypothermia", {"warning_hypothermia", "Warning: Approaching hypothermia!", "Advertencia: Aproximándose a la hipotermia!"}},
    {"warning_hyperthermia", {"warning_hyperthermia", "Warning: Approaching hyperthermia!", "Advertencia: Aproximándose a la hipertermia!"}},
    {"temp_critical", {"temp_critical","Temperature is critical!", "Die Temperatur ist entscheidend!"}},
    {"warning_higherpulse", {"warning_higherpulse","Warning: Approaching Higher Pulse Rate", "Warnung: Annäherung an höhere Pulsfrequenz"}},
    {"warning_lowerpulse", {"warning_lowerpulse","Warning: Approaching Lower Pulse Rate", "Warnung: Annäherung an niedrigere Pulsfrequenz"}},
    {"pulse_critical", {"pulse_critical","Pulse Rate is out of range!", "Pulsfrequenz liegt außerhalb des zulässigen Bereichs!"}},
    {"warning_lowSPO2",{"warning_lowSPO2","Warning: Approaching Lower spo2","Warnung: Unterer Spo2-Wert nähert sich"}},
    {"spo2_critical",{"spo2_critical","Oxygen Saturation out of range!","Sauerstoffsättigung außerhalb des zulässigen Bereichs!"}} // Add more translations as needed
};



class CheckVitals {
    struct VitalCheck {
        double value;
        bool (*checkFunc)(double);
        std::string message;
    };


public:

    enum Language
    {
        English,
        German
    };

    enum Vitals
    {
        Temp,
        PulseRate,
        SPO2
    };

    std::vector<VitalCheck> checks;

    void displayWarning(const std::string& message);
    bool vitalsOk(double temperature, double pulseRate, double spo2);
    void SetLanguage(Language language);
    std::string GetMessage();
};
