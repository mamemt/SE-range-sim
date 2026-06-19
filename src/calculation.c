#include <stdio.h>
#include <string.h>
#include "calculation.h"
#include "json_importer.h"

#define VEHICLE_DIR "data/vehicles/"
#define ROUTE_DIR   "data/routes/"
#define WEATHER_DIR "data/weather/"

double calculation(char* vehicle_file, char* route_file, char* weather_file, double battery_level) {
    //char vehicle_path[256];
    //char route_path[256];
    //char weather_path[256];
    //snprintf(vehicle_path, sizeof(vehicle_path), "%s%s", VEHICLE_DIR, vehicle_file);
    //snprintf(route_path,   sizeof(route_path),   "%s%s", ROUTE_DIR,   route_file);
    //snprintf(weather_path, sizeof(weather_path), "%s%s", WEATHER_DIR, weather_file);

    char vehicle_json[1000] = {0};
    char route_json[1000] = {0};
    char weather_json[1000] = {0};
    read_file_to_buffer(vehicle_file, vehicle_json, sizeof(vehicle_json));
    read_file_to_buffer(route_file,   route_json,   sizeof(route_json));
    read_file_to_buffer(weather_file, weather_json, sizeof(weather_json));

    //auslesen Fahrzeugdaten
    double battery_capacity = 0.0;
    double base_consumption_kwh_per_100km = 0.0;
    find_double_field(vehicle_json, "battery_capacity_kwh", &battery_capacity);
    find_double_field(vehicle_json, "base_consumption_kwh_per_100km", &base_consumption_kwh_per_100km);

    //auslesen Streckendaten
    double distance_km = 0.0;
    double elevation_gain_m = 0.0;
    double share_city_percent = 0.0;
    double share_rural_percent = 0.0;
    double share_highway_percent = 0.0;
    double speed_city_kmh = 0.0;
    double speed_rural_kmh = 0.0;
    double speed_highway_kmh = 0.0;
    find_double_field(route_json, "distance_km", &distance_km);
    find_double_field(route_json, "elevation_gain_m", &elevation_gain_m);
    find_double_field(route_json, "share_city_percent", &share_city_percent);
    find_double_field(route_json, "share_rural_percent", &share_rural_percent);
    find_double_field(route_json, "share_highway_percent", &share_highway_percent);
    find_double_field(route_json, "speed_city_kmh", &speed_city_kmh);
    find_double_field(route_json, "speed_rural_kmh", &speed_rural_kmh);
    find_double_field(route_json, "speed_highway_kmh", &speed_highway_kmh);

    //auslesen Wetterdaten
    double temperature_celsius = 0.0;
    double wind_speed_kmh = 0.0;
    double precipitation_mm_per_h = 0.0;
    find_double_field(weather_json, "temperature_celsius", &temperature_celsius);
    find_double_field(weather_json, "wind_speed_kmh", &wind_speed_kmh);
    find_double_field(weather_json, "precipitation_mm_per_h", &precipitation_mm_per_h);

    //Berechnung

    //Wetterfaktor
    double temperature_factor = 1 + (50-temperature_celsius) * 0.0005;
    double wind_factor = 1 + (wind_speed_kmh * 0.0005);
    double rain_factor = 1 + (precipitation_mm_per_h * 0.0005);
    double weather_factor = temperature_factor * wind_factor * rain_factor;

    //Hoehenmeterfaktor
    double elevation_factor = 1 + (elevation_gain_m * 0.0001);

    //Streckenfaktor
    double city_factor = 1.3;
    double rural_factor = 0.9;
    double highway_factor = 1.1;
    double route_factor = (share_city_percent * city_factor + share_rural_percent * rural_factor
                             + share_highway_percent * highway_factor)/100.0;

    //Gesamtfaktor
    double total_factor = weather_factor * elevation_factor * route_factor;

    //Verbrauchsberechnung
    double consumption_kwh_per_100km = base_consumption_kwh_per_100km * total_factor;
    double total_consumption_kwh = (consumption_kwh_per_100km * distance_km) / 100.0;
    printf("Geschätzter Verbrauch: %.2f kWh\n", total_consumption_kwh);
    double remaining_battery_kwh = (battery_level / 100.0) * battery_capacity;
    if (total_consumption_kwh > remaining_battery_kwh) {
        return 0;
    } else {
        return 1;
    }
}