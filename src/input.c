#include <stdio.h>
#include "input.h"

void clear_input_buffer(void) {
    while (getchar() != '\n');
}
