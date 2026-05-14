#include <stdio.h>
#include <string.h>

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

int main(void) {
    char input[16];

    printf("Willkommen bei range-sim!\n");

    while (1) {
        printf("Eingabe (start/exit)");

        fgets(input, sizeof(input), stdin);

        if (strchr(input, '\n') == NULL) {
            clear_input_buffer();
        }

        if (strcmp(input, "start\n") == 0) {
            printf("range-sim gestartet\n");
            break;
        }

        if (strcmp(input, "exit\n") == 0) {
            printf("range-sim beendet\n");
            return 0;
        }

        printf("Falsche Eingabe. Bitte 'start' oder 'exit' eingeben.\n");
    }

    while (1) {
        show_menu();
        printf("Auswahl: ");

        fgets(input, sizeof(input), stdin);

        if (strchr(input, '\n') == NULL) {
            clear_input_buffer();
        }

        if (strcmp(input, "1\n") == 0) {
            printf("Du hast 'Fahrzeug auswaehlen' gewaehlt.\n");
        } else if (strcmp(input, "2\n") == 0) {
            printf("Du hast 'Strecke auswaehlen' gewaehlt.\n");
        } else if (strcmp(input, "3\n") == 0) {
            printf("Du hast 'Wetterprofil auswaehlen' gewaehlt.\n");
        } else if (strcmp(input, "4\n") == 0) {
            printf("Du hast 'Ladezustand eingeben' gewaehlt.\n");
        } else if (strcmp(input, "5\n") == 0) {
            printf("range-sim beendet\n");
            break;
        } else {
            printf("Falsche Eingabe. Bitte eine Zahl zwischen 1 und 5 eingeben.\n");
        }
    }

    return 0;
}