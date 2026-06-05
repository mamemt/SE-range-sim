#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "vehicle.h"
#include "route.h"
#include "weather.h"
#include "battery.h"

#define INPUT_BUFFER_SIZE 16

static void clear_input_buffer(void) {
    while (getchar() != '\n');
}

static void show_menu(void) {
    printf("\n------ range-sim ------\n");
    printf("1 - Fahrzeug auswaehlen\n");
    printf("2 - Strecke auswaehlen\n");
    printf("3 - Wetterprofil auswaehlen\n");
    printf("4 - Ladezustand eingeben\n");
    printf("5 - Beenden\n");
    printf("-----------------------\n");
}

int wait_for_start_command(void) {
    char input[INPUT_BUFFER_SIZE];

    while (1) {
        printf("Eingabe (start/exit): ");
        fgets(input, sizeof(input), stdin);
        if (strchr(input, '\n') == NULL) {
            clear_input_buffer();
        }
        if (strcmp(input, "start\n") == 0) {
            printf("range-sim gestartet\n");
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

    while (1) {
        show_menu();
        printf("Auswahl: ");
        fgets(input, sizeof(input), stdin);
        if (strchr(input, '\n') == NULL) {
            clear_input_buffer();
        }

        if (strcmp(input, "1\n") == 0) {
            char* vehicle_file = select_vehicle();
        } else if (strcmp(input, "2\n") == 0) {
            select_route();
        } else if (strcmp(input, "3\n") == 0) {
            select_weather_profile();
        } else if (strcmp(input, "4\n") == 0) {
            double battery_charge_percent = enter_battery_level();
            printf("Aktueller Ladezustand: %.1f%%\n", battery_charge_percent);
        } else if (strcmp(input, "5\n") == 0) {
            printf("range-sim beendet\n");
            return;
        } else {
            printf("Falsche Eingabe. Bitte eine Zahl zwischen 1 und 5 eingeben.\n");
        }
    }
}