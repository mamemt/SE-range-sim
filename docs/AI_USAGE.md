# KI-Nutzung im Projekt

## Format

- **Datum** – wann wurde ... eingesetzt (YYYY-MM-DD)
- **Wo** – Datei / Modul
- **Nutzer** - Wer hat die KI genutzt
- **Werkzeug** – verwendetes Tool mit Modell-Bezeichnung
- **Wofür** – kurz KI Beitrag beschreiben
- **Geprüft** – Ergebnisverifikation

## Einträge

### 2026-05-23 – src/json_importer.c (find_double_field) - Gabriel, Kvesic
- **Werkzeug:** Claude Code (Opus 4.7)
- **Wofür:** Vorschlag: Implementierung von `find_double_field` mit `sscanf("%lf")` und Out-Parameter, um Fehlercodes sauber von Werten zu trennen. Alternativen (eigener Mini-Parser, Sentinel-Return, Result-Struct) gegeneinander abgewogen.
- **Geprüft:** Code gelesen, verstanden und manuell angepasst. Manueller Smoke-Test `tests/json_importer_test.c` mit allen drei Dummy-Fahrzeugprofilen und vier Fehlerfällen, alle 16 Checks bestanden.
