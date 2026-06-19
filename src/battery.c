#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "battery.h"

#define INPUT_BUFFER_SIZE 16

static void clear_input_buffer(void) {
    while (getchar() != '\n');
}

double enter_battery_level(void) {
    char input[INPUT_BUFFER_SIZE];
    double charge_percent;
    char *endptr;

    while (1) {
        printf("Ladezustand eingeben (1-100): ");
        fgets(input, sizeof(input), stdin);

        if (strchr(input, '\n') == NULL) {
            clear_input_buffer();
            printf("Ungueltige Eingabe. Bitte eine Zahl zwischen 1 und 100 eingeben.\n");
            continue;
        }

        // strtod erkennt ungueltige Zeichen (endptr == input) -> gar keine Zahl gefunden "abc" // (*endptr != '\n') -> Zahl gefolgt von Müll "80abc"
        charge_percent = strtod(input, &endptr);

        if (endptr == input || (*endptr != '\n' && *endptr != '\0')) {
            printf("Ungueltige Eingabe. Bitte eine Zahl zwischen 1 und 100 eingeben.\n");
            continue;
        }

        if (charge_percent < 1.0 || charge_percent > 100.0) {
            printf("Ungueltige Eingabe. Bitte eine Zahl zwischen 1 und 100 eingeben.\n");
            continue;
        }

        printf("Ladezustand gespeichert: %.1f%%\n\n", charge_percent);
        return charge_percent;
    }
}