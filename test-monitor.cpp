#include "./monitor.h"

#include "gtest/gtest.h"


TEST(Monitor, OkWhenAllVitalInRange) {
    CheckVitals vitals;
    ASSERT_TRUE(vitals.vitalsOk(98.1, 70, 98));
}

TEST(Monitor, NotOkWhenAnyVitalIsOffRange){
    CheckVitals vitals;

    ASSERT_FALSE(vitals.vitalsOk(99, 102, 70));
}

TEST(Monitor, NotOkWhenTempVitalIsOffRange) {
    CheckVitals vitals;

    ASSERT_FALSE(vitals.vitalsOk(102.5, 55, 70));
}

TEST(Monitor, NotOkWhenSPO2VitalIsOffRange) {
    CheckVitals vitals;

    ASSERT_FALSE(vitals.vitalsOk(98, 70, 70));
}

