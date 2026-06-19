#include <stdio.h>
#include "route.h"
#include "menu.h"

char* select_route(void) {
    int input;

    //printf("Du hast 'Strecke auswaehlen' gewaehlt.\n");

    printf("Waehle zwischen folgenden Strecken:\n");
    printf("1 - stuttgart_muenchen\n");
    printf("2 - stuttgart_ulm\n");

    while (1) {
        if (scanf("%d", &input) != 1) {
            clear_input_buffer();
            printf("Ungueltige Eingabe. Bitte erneut versuchen.\n");
            continue;}

        if (input == 1) {
            printf("Du hast 'stuttgart_muenchen' ausgewaehlt.\n\n");
            return "data/routes/stuttgart_muenchen.json";} 
        else if (input == 2) {
            printf("Du hast 'stuttgart_ulm' ausgewaehlt.\n\n");
            return "data/routes/stuttgart_ulm.json";} 
        else {
            printf("Ungueltige Eingabe. Bitte erneut versuchen.\n");}
    }
}