# Funktionen

Dieses Dokument listet alle öffentlichen Funktionen des Projekts mit einer
kurzen Beschreibung. Pro Modul ein Abschnitt. Neue Funktionen werden gemäß
Definition of Done hier ergänzt.

## Modul `json_importer`

Generisches Modul zum Einlesen von einfachen JSON-Files.
Wiederverwendbar für Fahrzeug-, Strecken- und Wetterprofile.

- `read_file_to_buffer(path, buffer, buffer_size)`
  Liest eine Datei vollständig in den übergebenen Buffer. Gibt `JSON_OK` bei Erfolg zurück
- `find_string_field(json, key, out, out_size)`
  Sucht in JSON nach dem Schlüssel `key` und kopiert den zugehörigen String-Wert nach `out`.
- `find_double_field(json, key, out)`
  Sucht in JSON nach dem Schlüssel `key` und schreibt den zugehörigen Zahlenwert nach `*out`.

