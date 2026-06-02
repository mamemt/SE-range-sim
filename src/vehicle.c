#include <stdio.h>
#include "vehicle.h"

char* select_vehicle(void) {
    int input;

    printf("Du hast 'Fahrzeug auswaehlen' gewaehlt.\n");

    printf("Waehle zwischen folgenden Fahrzeugen:\n");
    printf("1 - Renault Zoe\n");
    printf("2 - Tesla Model 3\n");
    printf("3 - VW ID.3\n");

    while (1) {
        scanf("%d", &input);

        if (input == 1) {
            printf("Du hast 'Renault Zoe' ausgewaehlt.\n");
            return "Renault Zoe";} 
        else if (input == 2) {
            printf("Du hast 'Tesla Model 3' ausgewaehlt.\n");
            return "Tesla Model 3";} 
        else if (input == 3) {
            printf("Du hast 'VW ID.3' ausgewaehlt.\n");
            return "VW ID.3";} 
        else {
            printf("Ungueltige Eingabe. Bitte erneut versuchen.\n");}
    }
}