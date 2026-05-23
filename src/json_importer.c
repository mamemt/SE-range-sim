#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "json_importer.h"


int read_file_to_buffer(const char path[], char buffer[], int buffer_size) {
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        return JSON_ERR_FILE;
    }

    int count = (int)fread(buffer, 1, buffer_size - 1, file);

    int file_is_larger = !feof(file);
    fclose(file);

    if (file_is_larger) {
        return JSON_ERR_BUFFER_SIZE;
    }

    buffer[count] = '\0';
    return JSON_OK;
}

// Zum Filtern von Tabs, Leerzeichen, etc. 
static int is_whitespace(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

static int find_value_start_index(const char json[], const char key[]) {
    // key in " ", damit er nicht als Teil eines anderen Worts erkannt wird
    char buffer[64];
    int buffer_length = sizeof(buffer);
    int quoted_key_length = snprintf(buffer, sizeof(buffer), "\"%s\"", key);

    if (quoted_key_length < 0) {
        return -1;
    }

    if (quoted_key_length >= buffer_length) {
        return -1;
    }

    // key in JSON finden und bis Start des eigentlichen Werts springen
    int key_position = -1;

    for (int j = 0; json[j] != '\0'; j++) {
        int match = 1;
        
        for (int k = 0; k < quoted_key_length; k++) {
            if (json[j + k] != buffer[k]) {
                match = 0;
                break;
            }
        }

        if (match == 1) {
            key_position = j;
            break;
        }
    }

    if (key_position == -1) {
        return -1;
    }
    
    // skip hinter key
    int i = key_position + quoted_key_length;

    // skip Whitespaces bis Doppelpunkt 
    while (is_whitespace(json[i])) {
        i++;
    }

    // skip hinter Doppelpunkt
    if (json[i] != ':') {
        return -1;
    }
    i++;

    // skip Whitespaces nach Doppelpunkt
    while (is_whitespace(json[i])) {
        i++;
    }

    // gefundener Index, an dem sich Wert befindet
    return i;
}

int find_string_field(const char json[], const char key[], char out[], int out_size) {
    int i = find_value_start_index(json, key);
    if (i < 0) {
        return JSON_ERR_KEY_NOT_FOUND;
    }

    // skip öffnendes Anführungszeichen
    if (json[i] != '"') {
        return JSON_ERR_FORMAT;
    }
    i++;

    // Inhalt bis schließendes Anführungszeichen kopieren
    int out_index = 0;
    while (json[i] != '"' && json[i] != '\0') {
        if (out_index >= out_size - 1) {
            return JSON_ERR_BUFFER_SIZE;
        }
        out[out_index] = json[i];
        out_index++;
        i++;
    }
    if (json[i] != '"') {
        return JSON_ERR_FORMAT;
    }
    out[out_index] = '\0';
    return JSON_OK;
}

int find_double_field(const char json[], const char key[], double *out) {
    int i = find_value_start_index(json, key);
    if (i < 0) {
        return JSON_ERR_KEY_NOT_FOUND;
    }

    // sscanf liest Zeichen ab Index und konvertiert in einen double-Wert
    // Rückgabe ist Anzahl erfolgreich gelesener Werte (hier 1)
    int count = sscanf(&json[i], "%lf", out);
    if (count != 1) {
        return JSON_ERR_FORMAT;
    }
    return JSON_OK;
}
