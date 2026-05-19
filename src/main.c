#include <stdio.h>
#include "menu.h"

int main(void) {
    printf("Willkommen bei range-sim!\n");
    if (wait_for_start_command() != 0) {
        return 0;
    }
    run_main_menu();
    return 0;
}