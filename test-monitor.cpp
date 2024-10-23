#include "./monitor.h"

#include "gtest/gtest.h"


TEST(Monitor, OkWhenAllVitalInRange) {
    CheckVitals vitals;
    ASSERT_TRUE(vitals.vitalsOk(98.1, 70, 98));
}

TEST(Monitor, NotOkWhenAnyVitalIsOffRange) {
    CheckVitals vitals;

    ASSERT_FALSE(vitals.vitalsOk(99, 102, 70));
}

TEST(Monitor, NotOkWhenTempVitalIsOffRange) {
    CheckVitals vitals;

    ASSERT_FALSE(vitals.vitalsOk(102.5, 70, 100));
}

TEST(Monitor, NotOkWhenSPO2VitalIsOffRange) {
    CheckVitals vitals;

    ASSERT_FALSE(vitals.vitalsOk(98, 70, 70));
}

TEST(Monitor, TempApprochingHigherRange) {
    CheckVitals vitals;

    ASSERT_FALSE(vitals.vitalsOk(101, 70, 100));
}

TEST(Monitor, TempApprochingLowerRange) {
    CheckVitals vitals;

    ASSERT_FALSE(vitals.vitalsOk(96, 70, 100));
}

TEST(Monitor, PulseRateApprochingLowerRange) {
    CheckVitals vitals;

    ASSERT_FALSE(vitals.vitalsOk(98.1, 60.5, 100));
}

TEST(Monitor, PulseRateApprochingHigherRange) {
    CheckVitals vitals;

    ASSERT_FALSE(vitals.vitalsOk(98.1, 98.5, 100));
}

TEST(Monitor, TempCriticalwarniginGerman) {
    CheckVitals vitals;
    vitals.SetLanguage(CheckVitals::Language::German);
    ASSERT_FALSE(vitals.vitalsOk(102.5, 70, 100));
    std::string msg = "";
    if (translations.find("temp_critical") != translations.end()) {
        const Translation& translation = translations["temp_critical"];
        msg = translation.german;
    }
    std::string message = vitals.checks[0].message;
    ASSERT_EQ(msg, message);

}

TEST(Monitor, TempHigherWarningGerman) {
    CheckVitals vitals;
    vitals.SetLanguage(CheckVitals::Language::German);
    ASSERT_FALSE(vitals.vitalsOk(101, 70, 100));
    std::string msg = "";
    if (translations.find("warning_hyperthermia") != translations.end()) {
        const Translation& translation = translations["warning_hyperthermia"];
        msg = translation.german;
    }
    std::string message = vitals.checks[0].message;
    ASSERT_EQ(msg, message);
}

TEST(Monitor, TempLowerWarningGerman) {
    CheckVitals vitals;
    vitals.SetLanguage(CheckVitals::Language::German);
    ASSERT_FALSE(vitals.vitalsOk(96, 70, 100));
    std::string msg = "";
    if (translations.find("warning_hypothermia") != translations.end()) {
        const Translation& translation = translations["warning_hypothermia"];
        msg = translation.german;
    }
    std::string message = vitals.GetMessage();
    ASSERT_EQ(msg, message);
}

TEST(Monitor, PulseRateCriticalWarningGerman) {
    CheckVitals vitals;
    vitals.SetLanguage(CheckVitals::Language::German);
    ASSERT_FALSE(vitals.vitalsOk(99, 102, 70));
    std::string msg = "";
    if (translations.find("pulse_critical") != translations.end()) {
        const Translation& translation = translations["pulse_critical"];
        msg = translation.german;
    }
    std::string message = vitals.GetMessage();
    ASSERT_EQ(msg, message);
}

TEST(Monitor, SPO2VitalWarningInGerman) {
    CheckVitals vitals;
    vitals.SetLanguage(CheckVitals::Language::German);
    ASSERT_FALSE(vitals.vitalsOk(98, 70, 70));
    std::string msg = "";
    if (translations.find("spo2_critical") != translations.end()) {
        const Translation& translation = translations["spo2_critical"];
        msg = translation.german;
    }
    std::string message = vitals.GetMessage();
    ASSERT_EQ(msg, message);
}


