// README beachten

#include "unity.h"
#include "calculation.h"

void setUp(void) {}
void tearDown(void) {}

/* ============================================================
   Strecke moeglich
   ============================================================ */

void calculation_with_full_battery_and_mild_weather_should_return_possible(void) {
    double result = calculation("tesla_model_3.json", "stuttgart_ulm.json", "warm_dry_calm.json", 100.0);
    TEST_ASSERT_EQUAL_DOUBLE(1.0, result);
}

void calculation_with_high_battery_on_long_route_should_return_possible(void) {
    double result = calculation("tesla_model_3.json", "stuttgart_muenchen.json", "warm_dry_calm.json", 90.0);
    TEST_ASSERT_EQUAL_DOUBLE(1.0, result);
}

/* ============================================================
   Strecke nicht moeglich
   ============================================================ */

void calculation_with_low_battery_should_return_not_possible(void) {
    double result = calculation("vw_id3.json", "stuttgart_ulm.json", "warm_dry_calm.json", 5.0);
    TEST_ASSERT_EQUAL_DOUBLE(0.0, result);
}

void calculation_with_bad_weather_and_low_battery_should_return_not_possible(void) {
    double result = calculation("renault_zoe.json", "stuttgart_muenchen.json", "cold_heavy_rain_storm.json", 20.0);
    TEST_ASSERT_EQUAL_DOUBLE(0.0, result);
}

/* ============================================================
   Andere Fahrzeuge
   ============================================================ */

void calculation_with_renault_zoe_and_full_battery_should_return_possible(void) {
    double result = calculation("renault_zoe.json", "stuttgart_ulm.json", "warm_dry_calm.json", 100.0);
    TEST_ASSERT_EQUAL_DOUBLE(1.0, result);
}

void calculation_with_vw_id3_and_full_battery_should_return_possible(void) {
    double result = calculation("vw_id3.json", "stuttgart_ulm.json", "warm_dry_calm.json", 100.0);
    TEST_ASSERT_EQUAL_DOUBLE(1.0, result);
}

/* ============================================================
   Test-Runner
   ============================================================ */

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(calculation_with_full_battery_and_mild_weather_should_return_possible);
    RUN_TEST(calculation_with_high_battery_on_long_route_should_return_possible);

    RUN_TEST(calculation_with_low_battery_should_return_not_possible);
    RUN_TEST(calculation_with_bad_weather_and_low_battery_should_return_not_possible);

    RUN_TEST(calculation_with_renault_zoe_and_full_battery_should_return_possible);
    RUN_TEST(calculation_with_vw_id3_and_full_battery_should_return_possible);

    return UNITY_END();
}
