# Datenformate

Dieses Dokument beschreibt das JSON-Format der Profil-Dateien unter `data/`.
Es legt den Vertrag zwischen den Beispieldaten und dem späteren Importer-Modul fest.

## Fahrzeugprofile (`data/vehicles/*.json`)

Ein Fahrzeugprofil beschreibt dauerhafte Eigenschaften eines Elektrofahrzeugs.
Der aktuelle Ladezustand gehört **nicht** zum Profil, sondern wird zur Fahrtzeit
vom Benutzer eingegeben.

Eine Datei pro Fahrzeug. Dateiname in `snake_case` (z. B. `tesla_model_3.json`).

### Felder

| Feld                              | Typ    | Einheit       | Pflicht | Beschreibung                            |
|-----------------------------------|--------|---------------|---------|-----------------------------------------|
| `name`                            | String | –             | ja      | Anzeigename des Fahrzeugs               |
| `battery_capacity_kwh`            | Float  | kWh           | ja      | Nutzbare Batteriekapazität              |
| `base_consumption_kwh_per_100km`  | Float  | kWh / 100 km  | ja      | Durchschnittlicher Basisverbrauch       |

### Beispiel

```json
{
  "name": "Tesla Model 3",
  "battery_capacity_kwh": 60.0,
  "base_consumption_kwh_per_100km": 14.5
}
```

### Annahmen

- Einheit `kWh` wird gewählt, da gut lesbar und in Fahrzeug-Datenblättern üblich.
- `base_consumption_kwh_per_100km` ist ein Durchschnittswert ohne Wetter- oder
  Streckeneinflüsse. Diese werden später über Strecken- und Wetterprofile
  aufgeschlagen.
- Werte sind als `Float` mit einer Nachkommastelle angegeben (z. B. `60.0`),
  damit der spätere Parser einheitlich Fließkommazahlen erwartet.

## Geplante weitere Profile

Analoge Unterordner sind vorgesehen, sobald die zugehörigen Issues bearbeitet
werden:

- `data/routes/*.json` – Streckenprofile (Name, Gesamtdistanz, Segmente, Höhenmeter)
- `data/weather/*.json` – Wetterprofile (Temperatur, Regen, Windgeschwindigkeit)

Die genauen Felder dieser Profile werden in den jeweiligen Issues festgelegt
und hier ergänzt.
