/* Erster Test für das json_importer Modul
   Manueller Test ohne Framework 
   Prüft die drei öffentlichen Funktionen mit Dummy-Profilen unter data/vehicles/
   Erstellt auf Basis der gegebenen Funktionen mittels Claude Code Opus 4.7
*/

#include <stdio.h>
#include <string.h>
#include "json_importer.h"

// Zähler für Zusammenfassung am Ende
static int passes = 0;
static int fails = 0;

static void check_int(const char label[], int actual, int expected) {
    if (actual == expected) {
        printf("  [PASS] %s  (Ergebnis %d)\n", label, actual);
        passes++;
    } else {
        printf("  [FAIL] %s  (erwartet %d, bekommen %d)\n",
               label, expected, actual);
        fails++;
    }
}

static void check_string(const char label[], const char actual[], const char expected[]) {
    if (strcmp(actual, expected) == 0) {
        printf("  [PASS] %s  (\"%s\")\n", label, actual);
        passes++;
    } else {
        printf("  [FAIL] %s  (erwartet \"%s\", bekommen \"%s\")\n",
               label, expected, actual);
        fails++;
    }
}

static void check_double(const char label[], double actual, double expected) {
    // Floating Point Vergleich mit kleiner Toleranz
    double diff = actual - expected;
    if (diff < 0) {
        diff = -diff;
    }
    if (diff < 0.0001) {
        printf("  [PASS] %s  (%f)\n", label, actual);
        passes++;
    } else {
        printf("  [FAIL] %s  (erwartet %f, bekommen %f)\n",
               label, expected, actual);
        fails++;
    }
}

int main(void) {
    char buffer[2048];
    int result;

    /* ============================================================
       TEST 1: read_file_to_buffer mit echter Datei
       ============================================================ */
    printf("\n--- Test 1: read_file_to_buffer (Tesla) ---\n");
    result = read_file_to_buffer("data/vehicles/tesla_model_3.json",
                                 buffer, sizeof(buffer));
    check_int("Rueckgabewert", result, JSON_OK);
    printf("  Inhalt:\n%s\n", buffer);

    /* ============================================================
       TEST 2: find_string_field
       ============================================================ */
    printf("--- Test 2: find_string_field (name) ---\n");
    char name[64];
    result = find_string_field(buffer, "name", name, sizeof(name));
    check_int("Rueckgabewert", result, JSON_OK);
    check_string("name", name, "Tesla Model 3");

    /* ============================================================
       TEST 3: find_double_field (Kapazitaet)
       ============================================================ */
    printf("--- Test 3: find_double_field (battery_capacity_kwh) ---\n");
    double capacity = 0.0;
    result = find_double_field(buffer, "battery_capacity_kwh", &capacity);
    check_int("Rueckgabewert", result, JSON_OK);
    check_double("battery_capacity_kwh", capacity, 60.0);

    /* ============================================================
       TEST 4: find_double_field (Verbrauch)
       ============================================================ */
    printf("--- Test 4: find_double_field (base_consumption) ---\n");
    double consumption = 0.0;
    result = find_double_field(buffer, "base_consumption_kwh_per_100km",
                               &consumption);
    check_int("Rueckgabewert", result, JSON_OK);
    check_double("base_consumption_kwh_per_100km", consumption, 14.5);

    /* ============================================================
       TEST 5: Anderes Fahrzeug (Renault Zoe)
       ============================================================ */
    printf("--- Test 5: zweite Datei (Renault Zoe) ---\n");
    result = read_file_to_buffer("data/vehicles/renault_zoe.json",
                                 buffer, sizeof(buffer));
    check_int("Datei lesen", result, JSON_OK);
    char zoe_name[64];
    result = find_string_field(buffer, "name", zoe_name, sizeof(zoe_name));
    check_int("name lesen", result, JSON_OK);
    check_string("name", zoe_name, "Renault Zoe");
    double zoe_cap = 0.0;
    result = find_double_field(buffer, "battery_capacity_kwh", &zoe_cap);
    check_int("Kapazitaet lesen", result, JSON_OK);
    check_double("battery_capacity_kwh", zoe_cap, 52.0);

    /* ============================================================
       TEST 6: Fehlerfall - Datei existiert nicht
       ============================================================ */
    printf("--- Test 6: Fehlerfall - Datei existiert nicht ---\n");
    result = read_file_to_buffer("data/vehicles/gibt_es_nicht.json",
                                 buffer, sizeof(buffer));
    check_int("Rueckgabewert", result, JSON_ERR_FILE);

    /* ============================================================
       TEST 7: Fehlerfall - Key existiert nicht
       ============================================================ */
    printf("--- Test 7: Fehlerfall - Key existiert nicht ---\n");
    read_file_to_buffer("data/vehicles/tesla_model_3.json",
                        buffer, sizeof(buffer));
    char dummy[64];
    result = find_string_field(buffer, "unbekannter_key",
                               dummy, sizeof(dummy));
    check_int("Rueckgabewert", result, JSON_ERR_KEY_NOT_FOUND);

    /* ============================================================
       TEST 8: Fehlerfall - String-Buffer zu klein
       ============================================================ */
    printf("--- Test 8: Fehlerfall - out-Buffer zu klein ---\n");
    char tiny[3]; /* nur Platz fuer 2 Zeichen + '\0' */
    result = find_string_field(buffer, "name", tiny, sizeof(tiny));
    check_int("Rueckgabewert", result, JSON_ERR_BUFFER_SIZE);

    /* ============================================================
       TEST 9: Fehlerfall - falscher Typ (Zahl als String suchen)
       ============================================================ */
    printf("--- Test 9: Fehlerfall - falscher Typ ---\n");
    char wrong[64];
    result = find_string_field(buffer, "battery_capacity_kwh",
                               wrong, sizeof(wrong));
    check_int("Rueckgabewert", result, JSON_ERR_FORMAT);

    /* ============================================================
       Zusammenfassung
       ============================================================ */
    printf("\n========================================\n");
    printf("Ergebnis: %d PASS, %d FAIL\n", passes, fails);
    printf("========================================\n");

    return fails == 0 ? 0 : 1;
}

