#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "input.h"
#include "vehicle.h"
#include "route.h"
#include "weather.h"
#include "battery.h"
#include "feasibility.h"

#define INPUT_BUFFER_SIZE 16


int wait_for_start_command(void) {
    char input[INPUT_BUFFER_SIZE];

    while (1) {
        printf("Eingabe (start/exit): ");
        fgets(input, sizeof(input), stdin);
        if (strchr(input, '\n') == NULL) {
            clear_input_buffer();
        }
        if (strcmp(input, "start\n") == 0) {
            printf("range-sim gestartet\n\n");
            return 0;
        }
        if (strcmp(input, "exit\n") == 0) {
            printf("range-sim beendet\n");
            return 1;
        }
        printf("Falsche Eingabe. Bitte 'start' oder 'exit' eingeben.\n");
    }
}

void run_main_menu(void) {
    char input[INPUT_BUFFER_SIZE];
    char* vehicle_file = NULL;
    char* route_file = NULL;
    char* weather_file = NULL;
    double battery_charge_percent = 0.0;
    double is_route_possible = 0.0;

    while (1) {
            vehicle_file = select_vehicle();
            route_file = select_route();
            weather_file = select_weather_profile();
            battery_charge_percent = enter_battery_level();
         is_route_possible = calculate_feasibility(vehicle_file, route_file, weather_file, battery_charge_percent);
            if (is_route_possible) {
                printf("Die Strecke ist mit dem aktuellen Ladezustand möglich.\n");
            } else {
                printf("Die Strecke ist mit dem aktuellen Ladezustand nicht möglich.\n");
            }
            return;
    }
}