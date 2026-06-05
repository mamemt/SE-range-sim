#include <stdio.h>
#include "weather.h"
#include "menu.h"

char* select_weather_profile(void) {
    int input;

    printf("Du hast 'Wetterprofil auswaehlen' gewaehlt.\n");

    printf("Waehle zwischen folgenden Wetterprofilen:\n");
    printf("1 - kalt, starker Regen/Sturm\n");
    printf("2 - kalt, regnerisch mit Wind\n");
    printf("3 - heiß, trockener Wind\n");
    printf("4 - mild, regenrisch mit leichtem Wind\n");
    printf("5 - warm, trocken und windstill\n");

    while (1) {
        if (scanf("%d", &input) != 1) {
            clear_input_buffer();
            printf("Ungueltige Eingabe. Bitte erneut versuchen.\n");
            continue;}

        if (input == 1) {
            printf("Du hast 'kalt, starker Regen/Sturm' ausgewaehlt.\n");
            return "cold_heavy_rain_storm.json";} 
        else if (input == 2) {
            printf("Du hast 'kalt, regnerisch mit Wind' ausgewaehlt.\n");
            return "cold_rain_wind.json";} 
        else if (input == 3) {
            printf("Du hast 'heiß, trockener Wind' ausgewaehlt.\n");
            return "hot_dry_wind.json";} 
        else if (input == 4) {
            printf("Du hast 'mild, regenrisch mit leichtem Wind' ausgewaehlt.\n");
            return "mild_rain_light_wind.json";} 
        else if (input == 5) {
            printf("Du hast 'warm, trocken und windstill' ausgewaehlt.\n");
            return "warm_dry_calm.json";} 
        else {
            printf("Ungueltige Eingabe. Bitte erneut versuchen.\n");}
    }
}