// README beachten

#include "unity.h"
#include "json_importer.h"

static char json_buffer[2048];

void setUp(void) {}
void tearDown(void) {}

/* ============================================================
   read_file_to_buffer
   ============================================================ */

void read_file_to_buffer_with_existing_file_should_return_ok(void) {
    int result = read_file_to_buffer("data/vehicles/tesla_model_3.json", json_buffer, sizeof(json_buffer));
    TEST_ASSERT_EQUAL_INT(JSON_OK, result);
}

void read_file_to_buffer_with_missing_file_should_return_file_error(void) {
    int result = read_file_to_buffer("data/vehicles/gibt_es_nicht.json", json_buffer, sizeof(json_buffer));
    TEST_ASSERT_EQUAL_INT(JSON_ERR_FILE, result);
}

/* ============================================================
   find_string_field
   ============================================================ */

void find_string_field_with_valid_key_should_return_value(void) {
    read_file_to_buffer("data/vehicles/tesla_model_3.json", json_buffer, sizeof(json_buffer));
    char name[64];
    int result = find_string_field(json_buffer, "name", name, sizeof(name));
    TEST_ASSERT_EQUAL_INT(JSON_OK, result);
    TEST_ASSERT_EQUAL_STRING("Tesla Model 3", name);
}

void find_string_field_with_missing_key_should_return_key_not_found(void) {
    read_file_to_buffer("data/vehicles/tesla_model_3.json", json_buffer, sizeof(json_buffer));
    char out[64];
    int result = find_string_field(json_buffer, "unbekannter_key", out, sizeof(out));
    TEST_ASSERT_EQUAL_INT(JSON_ERR_KEY_NOT_FOUND, result);
}

void find_string_field_with_too_small_buffer_should_return_buffer_size(void) {
    read_file_to_buffer("data/vehicles/tesla_model_3.json", json_buffer, sizeof(json_buffer));
    char tiny[3];
    int result = find_string_field(json_buffer, "name", tiny, sizeof(tiny));
    TEST_ASSERT_EQUAL_INT(JSON_ERR_BUFFER_SIZE, result);
}

void find_string_field_on_numeric_value_should_return_format_error(void) {
    read_file_to_buffer("data/vehicles/tesla_model_3.json", json_buffer, sizeof(json_buffer));
    char out[64];
    int result = find_string_field(json_buffer, "battery_capacity_kwh", out, sizeof(out));
    TEST_ASSERT_EQUAL_INT(JSON_ERR_FORMAT, result);
}

/* ============================================================
   find_double_field
   ============================================================ */

void find_double_field_with_valid_key_should_return_value(void) {
    read_file_to_buffer("data/vehicles/tesla_model_3.json", json_buffer, sizeof(json_buffer));
    double capacity = 0.0;
    int result = find_double_field(json_buffer, "battery_capacity_kwh", &capacity);
    TEST_ASSERT_EQUAL_INT(JSON_OK, result);
    TEST_ASSERT_EQUAL_DOUBLE(60.0, capacity);
}

void find_double_field_with_second_value_should_return_value(void) {
    read_file_to_buffer("data/vehicles/tesla_model_3.json", json_buffer, sizeof(json_buffer));
    double consumption = 0.0;
    int result = find_double_field(json_buffer, "base_consumption_kwh_per_100km", &consumption);
    TEST_ASSERT_EQUAL_INT(JSON_OK, result);
    TEST_ASSERT_EQUAL_DOUBLE(14.5, consumption);
}

void find_double_field_with_missing_key_should_return_key_not_found(void) {
    read_file_to_buffer("data/vehicles/tesla_model_3.json", json_buffer, sizeof(json_buffer));
    double out = 0.0;
    int result = find_double_field(json_buffer, "unbekannter_key", &out);
    TEST_ASSERT_EQUAL_INT(JSON_ERR_KEY_NOT_FOUND, result);
}

/* ============================================================
   Andere Datei
   ============================================================ */

void find_string_field_with_second_file_should_return_value(void) {
    read_file_to_buffer("data/vehicles/renault_zoe.json", json_buffer, sizeof(json_buffer));
    char name[64];
    int result = find_string_field(json_buffer, "name", name, sizeof(name));
    TEST_ASSERT_EQUAL_INT(JSON_OK, result);
    TEST_ASSERT_EQUAL_STRING("Renault Zoe", name);
}

/* ============================================================
   Test-Runner
   ============================================================ */

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(read_file_to_buffer_with_existing_file_should_return_ok);
    RUN_TEST(read_file_to_buffer_with_missing_file_should_return_file_error);

    RUN_TEST(find_string_field_with_valid_key_should_return_value);
    RUN_TEST(find_string_field_with_missing_key_should_return_key_not_found);
    RUN_TEST(find_string_field_with_too_small_buffer_should_return_buffer_size);
    RUN_TEST(find_string_field_on_numeric_value_should_return_format_error);

    RUN_TEST(find_double_field_with_valid_key_should_return_value);
    RUN_TEST(find_double_field_with_second_value_should_return_value);
    RUN_TEST(find_double_field_with_missing_key_should_return_key_not_found);

    RUN_TEST(find_string_field_with_second_file_should_return_value);

    return UNITY_END();
}
