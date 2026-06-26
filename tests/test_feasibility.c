// README beachten

#include "unity.h"
#include "feasibility.h"

void setUp(void) {}
void tearDown(void) {}

/* ============================================================
   Strecke moeglich
   ============================================================ */
/* Erwartungswert:
   temperature_factor = 1 + (50 - 20) * 0.0005 = 1.0150
   wind_factor        = 1.0000, rain_factor = 1.0000
   weather_factor     = 1.0150
   elevation_factor   = 1 + (320 * 0.0001) = 1.0320
   route_factor       = (15*1.3 + 20*0.9 + 65*1.1) / 100 = 1.0900
   total_factor       = 1.0150 * 1.0320 * 1.0900 = 1.1418
   total_consumption  = 14.5 * 1.1418 * 90 / 100 = 14.90 kWh
   total_pct          = (14.90 / 60) * 100 = 24.83%
   remaining          = 100 - 24.83 = 75.17% */
void calculate_feasibility_with_full_battery_and_mild_weather_should_return_positive_remaining(void) {
    double result = calculate_feasibility("data/vehicles/tesla_model_3.json", "data/routes/stuttgart_ulm.json", "data/weather/warm_dry_calm.json", 100.0);
    TEST_ASSERT_DOUBLE_WITHIN(0.01, 75.17, result);
}
/* Erwartungswert:
   temperature_factor = 1 + (50 - 20) * 0.0005 = 1.0150
   wind_factor        = 1.0000, rain_factor = 1.0000
   weather_factor     = 1.0150
   elevation_factor   = 1 + (510 * 0.0001) = 1.0510
   route_factor       = (10*1.3 + 15*0.9 + 75*1.1) / 100 = 1.0900
   total_factor       = 1.0150 * 1.0510 * 1.0900 = 1.1628
   total_consumption  = 14.5 * 1.1628 * 230 / 100 = 38.78 kWh
   total_pct          = (38.78 / 60) * 100 = 64.63%
   remaining          = 90 - 64.63 = 25.37% */
void calculate_feasibility_with_high_battery_on_long_route_should_return_positive_remaining(void) {
    double result = calculate_feasibility("data/vehicles/tesla_model_3.json", "data/routes/stuttgart_muenchen.json", "data/weather/warm_dry_calm.json", 90.0);
    TEST_ASSERT_DOUBLE_WITHIN(0.01, 25.37, result);
}

/* ============================================================
   Strecke nicht moeglich
   ============================================================ */
/* Erwartungswert:
   temperature_factor = 1 + (50 - 20) * 0.0005 = 1.0150
   wind_factor        = 1.0000, rain_factor = 1.0000
   weather_factor     = 1.0150
   elevation_factor   = 1 + (320 * 0.0001) = 1.0320
   route_factor       = (15*1.3 + 20*0.9 + 65*1.1) / 100 = 1.0900
   total_factor       = 1.0150 * 1.0320 * 1.0900 = 1.1418
   total_consumption  = 15.8 * 1.1418 * 90 / 100 = 16.24 kWh
   total_pct          = (16.24 / 58) * 100 = 27.99%
   remaining          = 5 - 27.99 = -22.99% */
void calculate_feasibility_with_low_battery_should_return_negative_remaining(void) {
    double result = calculate_feasibility("data/vehicles/vw_id3.json", "data/routes/stuttgart_ulm.json", "data/weather/warm_dry_calm.json", 5.0);
    TEST_ASSERT_DOUBLE_WITHIN(0.01, -22.99, result);
}
/* Erwartungswert:
   temperature_factor = 1 + (50 - (-10)) * 0.0005 = 1.0300
   wind_factor        = 1 + (80 * 0.0005) = 1.0400
   rain_factor        = 1 + (40 * 0.0005) = 1.0200
   weather_factor     = 1.0300 * 1.0400 * 1.0200 = 1.0926
   elevation_factor   = 1 + (510 * 0.0001) = 1.0510
   route_factor       = (10*1.3 + 15*0.9 + 75*1.1) / 100 = 1.0900
   total_factor       = 1.0926 * 1.0510 * 1.0900 = 1.2517
   total_consumption  = 17.2 * 1.2517 * 230 / 100 = 49.52 kWh
   total_pct          = (49.52 / 52) * 100 = 95.23%
   remaining          = 20 - 95.23 = -75.23% */
void calculate_feasibility_with_bad_weather_and_low_battery_should_return_negative_remaining(void) {
    double result = calculate_feasibility("data/vehicles/renault_zoe.json", "data/routes/stuttgart_muenchen.json", "data/weather/cold_heavy_rain_storm.json", 20.0);
    TEST_ASSERT_DOUBLE_WITHIN(0.01, -75.23, result);
}

/* ============================================================
   Andere Fahrzeuge
   ============================================================ */
/* Erwartungswert:
   temperature_factor = 1 + (50 - 20) * 0.0005 = 1.0150
   wind_factor        = 1.0000, rain_factor = 1.0000
   weather_factor     = 1.0150
   elevation_factor   = 1 + (320 * 0.0001) = 1.0320
   route_factor       = (15*1.3 + 20*0.9 + 65*1.1) / 100 = 1.0900
   total_factor       = 1.0150 * 1.0320 * 1.0900 = 1.1418
   total_consumption  = 17.2 * 1.1418 * 90 / 100 = 17.67 kWh
   total_pct          = (17.67 / 52) * 100 = 33.99%
   remaining          = 100 - 33.99 = 66.01% */
void calculate_feasibility_with_renault_zoe_and_full_battery_should_return_positive_remaining(void) {
    double result = calculate_feasibility("data/vehicles/renault_zoe.json", "data/routes/stuttgart_ulm.json", "data/weather/warm_dry_calm.json", 100.0);
    TEST_ASSERT_DOUBLE_WITHIN(0.01, 66.01, result);
}
/* Erwartungswert:
   temperature_factor = 1 + (50 - 20) * 0.0005 = 1.0150
   wind_factor        = 1.0000, rain_factor = 1.0000
   weather_factor     = 1.0150
   elevation_factor   = 1 + (320 * 0.0001) = 1.0320
   route_factor       = (15*1.3 + 20*0.9 + 65*1.1) / 100 = 1.0900
   total_factor       = 1.0150 * 1.0320 * 1.0900 = 1.1418
   total_consumption  = 15.8 * 1.1418 * 90 / 100 = 16.24 kWh
   total_pct          = (16.24 / 58) * 100 = 27.99%
   remaining          = 100 - 27.99 = 72.01% */
void calculate_feasibility_with_vw_id3_and_full_battery_should_return_positive_remaining(void) {
    double result = calculate_feasibility("data/vehicles/vw_id3.json", "data/routes/stuttgart_ulm.json", "data/weather/warm_dry_calm.json", 100.0);
    TEST_ASSERT_DOUBLE_WITHIN(0.01, 72.01, result);
}

/* ============================================================
   Test-Runner
   ============================================================ */

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(calculate_feasibility_with_full_battery_and_mild_weather_should_return_positive_remaining);
    RUN_TEST(calculate_feasibility_with_high_battery_on_long_route_should_return_positive_remaining);

    RUN_TEST(calculate_feasibility_with_low_battery_should_return_negative_remaining);
    RUN_TEST(calculate_feasibility_with_bad_weather_and_low_battery_should_return_negative_remaining);

    RUN_TEST(calculate_feasibility_with_renault_zoe_and_full_battery_should_return_positive_remaining);
    RUN_TEST(calculate_feasibility_with_vw_id3_and_full_battery_should_return_positive_remaining);

    return UNITY_END();
}
