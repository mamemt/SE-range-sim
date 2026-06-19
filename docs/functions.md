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

## Modul `feasibility`

- `calculate_feasibility(vehicle_file, route_file, weather_file, battery_level)`
  Liest Fahrzeug-, Strecken- und Wetterdaten aus JSON-Dateien und berechnet,
  ob die Fahrt mit dem aktuellen Ladestand möglich ist.
  Gibt `1` zurück wenn machbar, `0` wenn nicht.

## Modul `battery`

- `enter_battery_level(void)`
  Fragt den Benutzer nach dem aktuellen Ladestand in Prozent (0–100).
  Gibt den validierten Wert als `double` zurück.

## Modul `vehicle`

- `select_vehicle(void)`
  Zeigt eine Liste verfügbarer Fahrzeugprofile an und lässt den Benutzer eines auswählen.
  Gibt den Dateipfad zum gewählten Profil zurück.

## Modul `route`

- `select_route(void)`
  Zeigt eine Liste verfügbarer Streckenprofile an und lässt den Benutzer eines auswählen.
  Gibt den Dateipfad zum gewählten Profil zurück.

## Modul `weather`

- `select_weather_profile(void)`
  Zeigt eine Liste verfügbarer Wetterprofile an und lässt den Benutzer eines auswählen.
  Gibt den Dateipfad zum gewählten Profil zurück.

## Modul `menu`

- `wait_for_start_command(void)`
  Wartet auf eine Benutzereingabe zum Starten. Gibt `1` zurück wenn gestartet werden soll.
- `run_main_menu(void)`
  Steuert den Hauptablauf der Anwendung: Fahrzeug, Strecke, Wetter, Ladestand,
  Berechnung und Ausgabe des Ergebnisses.
- `clear_input_buffer(void)`
  Leert den stdin-Puffer, um fehlerhafte Folgeeingaben zu verhindern.
  