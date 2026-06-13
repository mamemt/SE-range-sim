# Tests

## Test-Framework

[Unity](https://github.com/ThrowTheSwitch/Unity):
schlankes C-Test-Framework (drei Quelldateien, MIT-Lizenz).
Dateien unter `tests/unity/`.

Funktionsweise:

- **Assertion-Makros** wie `TEST_ASSERT_EQUAL_INT`,
  `TEST_ASSERT_EQUAL_STRING`, `TEST_ASSERT_EQUAL_DOUBLE`. 
  Schlägt Assertion fehl, wird der Test mit Datei, Zeile und erwarteten sowie tatsächlichen Ausgabe als `FAIL` markiert.
- **Test-Runner** über `UNITY_BEGIN()`, `RUN_TEST(...)` und
  `UNITY_END()`. Damit wird in `main` der Reihe nach jede Testfunktion
  aufgerufen.

## Aufbau einer Test-Datei

Pro Modul eine eigene Test-Datei, Namensschema `test_<modul>.c`
(z. B. `test_json_importer.c`). Jede Datei enthält:

- `#include "unity.h"` und den Header des getesteten Moduls
- `setUp()` und `tearDown()` (Pflicht-Hooks von Unity, dürfen leer sein)
- Eine Funktion pro Test, Naming nach Wiki-Schema:
  `<Function>_<Condition>_<ExpectedBehavior>`
- Eine `main`, die Tests per `RUN_TEST(...)` aufruft

## Ausführen

Alle Tests bauen und ausführen (aus dem Projekt-Root):

```
make test
```

Einzelnes Test-Modul bauen und ausführen, z. B.:

```
make test_json_importer
./test_json_importer
```

oder

```
make test_calculation
./test_calculation
```

Wichtig: Aus dem Projekt-Root starten, weil Tests JSON-Dateien über
relative Pfade laden (`data/vehicles/...`).

## Neues Test-Modul hinzufügen

1. Datei anlegen: `tests/test_<modul>.c`
2. Im `Makefile` ein neues Target nach dem Muster von
   `test_json_importer` ergänzen, zu den Abhängigkeiten von `test`
   hinzufügen.
3. Test laufen lassen: `make test`
