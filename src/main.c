#include <stdio.h>
#include <string.h>

static void clear_input_buffer(void) {
    while (getchar() != '\n');
}

int main(void) {
    char input[16];

    printf("Willkommen bei range-sim!\n");

    while (1) {
        printf("Eingabe (start/exit)");

        fgets(input, sizeof(input), stdin);

        /* Puffer leeren falls Eingabe laenger als 15 Zeichen */
        if (strchr(input, '\n') == NULL) {
            clear_input_buffer();
        }

        if (strcmp(input, "start\n") == 0) {
            printf("range-sim gestartet\n");
            break;
        }

        if (strcmp(input, "exit\n") == 0) {
            printf("range-sim beendet\n");
            break;
        }

        printf("Falsche Eingabe. Bitte 'start' oder 'exit' eingeben.\n");
    }

    return 0;
}