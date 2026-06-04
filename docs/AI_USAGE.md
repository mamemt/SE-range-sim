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

### 2026-06-03 – tests/test_json_importer.c, Makefile, tests/README.md - Gabriel, Kvesic
- **Werkzeug:** Claude Code (Opus 4.7)
- **Wofür:** Über mögliche Test Frameworks abgewogen, unity ausgewählt. Wichtigste Prinzipien und grundsätzlichen Syntax erklären lassen. Erklären lassen, wie manueller Test für Framework umgebaut werden kann. Namen für Testfunktionen nach unity Vorgabe erstellen lassen. Makefile um `test`- und `test_json_importer`-Target ergänzt.
- **Geprüft:** Code manuell angepasst und verstanden, alte Tests in Framework-Form umgesetzt. `make test` lokal ausgeführt, 10 Tests grün.
