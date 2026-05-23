#ifndef JSON_IMPORTER_H
#define JSON_IMPORTER_H

// JSON_OK = Erfolg, alles andere = Fehler. 
#define JSON_OK                 0
#define JSON_ERR_FILE          -1
#define JSON_ERR_BUFFER_SIZE   -2
#define JSON_ERR_KEY_NOT_FOUND -3
#define JSON_ERR_FORMAT        -4


int read_file_to_buffer(const char path[], char buffer[], int buffer_size);

int find_string_field(const char json[], const char key[], char out[], int out_size);

int find_double_field(const char json[], const char key[], double *out);

#endif
