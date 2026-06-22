# SE-range-sim

## Kurzbeschreibung

Bewertet eine geplante Elektrofahrzeug-Fahrt anhand von Fahrzeugdaten, Streckenprofil und Wetterdaten. Zeigt, ob die Fahrt mit dem aktuellen Ladezustand möglich ist.

## Architektur

Architekturdiagramme liegen unter [docs/architecture/](docs/architecture/):

- [Use-Case-Diagramm](docs/architecture/use-case/use-caseUML.svg) – Überblick, was der Benutzer mit dem System tun kann
- [Sequenzdiagramm](docs/architecture/sequence/sequenceUML.svg) – Aufrufkette des Hauptablaufs (Programm starten → Eingaben → Berechnung → Ergebnis)

Die `.puml`-Quelldateien können mit [PlantUML](https://www.plantuml.com/plantuml/uml) bearbeitet und neu gerendert werden.

## Buildanleitung

Voraussetzung: `gcc` und `make` müssen installiert sein.

```bash
make
```

Erzeugt die ausführbare Datei `range-sim` im Projektverzeichnis.

Zum Ausführen der Tests:

```bash
make test
```

## Startanleitung

```bash
./range-sim
```

Die Anwendung muss aus dem Projektverzeichnis gestartet werden, da sie die Datendateien unter `data/` sucht.

## Beispiele

```text
Willkommen bei range-sim!
Eingabe (start/exit): start
range-sim gestartet

Waehle zwischen folgenden Fahrzeugen:
1 - Renault Zoe
2 - Tesla Model 3
3 - VW ID.3
2
Du hast 'Tesla Model 3' ausgewaehlt.

Waehle zwischen folgenden Strecken:
1 - stuttgart_muenchen
2 - stuttgart_ulm
2
Du hast 'stuttgart_ulm' ausgewaehlt.

Waehle zwischen folgenden Wetterprofilen:
1 - kalt, starker Regen/Sturm
2 - kalt, regnerisch mit Wind
3 - heiß, trockener Wind
4 - mild, regenrisch mit leichtem Wind
5 - warm, trocken und windstill
5
Du hast 'warm, trocken und windstill' ausgewaehlt.

Ladezustand eingeben (1-100): 80
Ladezustand gespeichert: 80.0%

Geschätzter Verbrauch: 14.90 kWh
Die Strecke ist mit dem aktuellen Ladezustand möglich.
```
