#include <stdio.h>
#include "vehicle.h"
#include "input.h"

char* select_vehicle(void) {
    int input;

    //printf("Du hast 'Fahrzeug auswaehlen' gewaehlt.\n");

    printf("Waehle zwischen folgenden Fahrzeugen:\n");
    printf("1 - Renault Zoe\n");
    printf("2 - Tesla Model 3\n");
    printf("3 - VW ID.3\n");

    while (1) {
        if (scanf("%d", &input) != 1) {
            clear_input_buffer();
            printf("Ungueltige Eingabe. Bitte erneut versuchen.\n");
            continue;}

        if (input == 1) {
            printf("Du hast 'Renault Zoe' ausgewaehlt.\n\n");
            return "data/vehicles/renault_zoe.json";} 
        else if (input == 2) {
            printf("Du hast 'Tesla Model 3' ausgewaehlt.\n\n");
            return "data/vehicles/tesla_model_3.json";} 
        else if (input == 3) {
            printf("Du hast 'VW ID.3' ausgewaehlt.\n\n");
            return "data/vehicles/vw_id3.json";} 
        else {
            printf("Ungueltige Eingabe. Bitte erneut versuchen.\n");}
    }
}