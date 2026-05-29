# Datenformate

Dieses Dokument beschreibt das JSON-Format der Profil-Dateien unter `data/`.

## Fahrzeugprofile (`data/vehicles/*.json`)

Ein Fahrzeugprofil beschreibt dauerhafte Eigenschaften eines Elektrofahrzeugs.
Aktueller Ladezustand gehört **nicht** zum Profil, sondern wird vom Benutzer eingegeben.

Eine Datei pro Fahrzeug. Dateiname in `snake_case` (z. B. `tesla_model_3.json`).

### Felder

| Feld                              | Typ    | Einheit       | Pflicht | Beschreibung                            |
|-----------------------------------|--------|---------------|---------|-----------------------------------------|
| `name`                            | String | –             | ja      | Anzeigename des Fahrzeugs               |
| `battery_capacity_kwh`            | Float  | kWh           | ja      | Nutzbare Batteriekapazität              |
| `base_consumption_kwh_per_100km`  | Float  | kWh / 100 km  | ja      | Durchschnittlicher Basisverbrauch       |

### Beispiel Fahrzeugprofile

```json
{
  "name": "Tesla Model 3",
  "battery_capacity_kwh": 60.0,
  "base_consumption_kwh_per_100km": 14.5
}
```

### Annahmen Fahrzeugprofile

- Einheit `kWh` wird gewählt, da gut lesbar und in Fahrzeug-Datenblättern üblich.
- `base_consumption_kwh_per_100km` ist ein Durchschnittswert ohne Wetter- oder
  Streckeneinflüsse. Diese werden später über Strecken- und Wetterprofile
  aufgeschlagen.
- Werte sind als `Float` mit einer Nachkommastelle angegeben (z. B. `60.0`),
  damit der spätere Parser einheitlich Fließkommazahlen erwartet.

## Streckenprofile (`data/routes/*.json`)

Ein Streckenprofil beschreibt eine Fahrstrecke als Ganzes.
Die Aufteilung in Stadt/Land/Autobahn erfolgt über Prozentwerte.
Durchschnittsgeschwindigkeiten pro Typ sind Modellannahmen im Code, nicht im JSON.

Eine Datei pro Strecke. Dateiname in `snake_case` nach Schema `start_ziel` (z. B. `stuttgart_ulm.json`).

### Felder Streckenprofile

| Feld                    | Typ     | Einheit | Pflicht | Beschreibung                                      |
|-------------------------|---------|---------|---------|---------------------------------------------------|
| `name`                  | String  | –       | ja      | Anzeigename der Strecke                           |
| `distance_km`           | Float   | km      | ja      | Einfache Streckenlänge                            |
| `elevation_gain_m`      | Float   | m       | ja      | Gesamter Höhengewinn (Summe aller Anstiege)       |
| `share_city_percent`    | Integer | %       | ja      | Anteil Stadtfahrt (Summe aller drei = 100)        |
| `share_rural_percent`   | Integer | %       | ja      | Anteil Landstraße (Summe aller drei = 100)        |
| `share_highway_percent` | Integer | %       | ja      | Anteil Autobahn (Summe aller drei = 100)          |
| `speed_city_kmh`        | Float   | km/h    | ja      | Durchschnittsgeschwindigkeit Stadt                |
| `speed_rural_kmh`       | Float   | km/h    | ja      | Durchschnittsgeschwindigkeit Landstraße           |
| `speed_highway_kmh`     | Float   | km/h    | ja      | Durchschnittsgeschwindigkeit Autobahn             |

### Beispiel Streckenprofile

```json
{
  "name": "Stuttgart -> Ulm",
  "distance_km": 90.0,
  "elevation_gain_m": 320.0,
  "share_city_percent": 15,
  "share_rural_percent": 20,
  "share_highway_percent": 65
}
```

### Annahmen Streckenprofile

- `distance_km` ist die einfache Strecke, keine Hin- und Rückfahrt.
- `elevation_gain_m` ist der Gesamthöhengewinn (nur Anstiege, Gefälle wird nicht als Rekuperation modelliert).
- Die drei `share_*_percent`-Felder müssen zusammen 100 ergeben.
- Streckenwerte basieren auf Schätzungen, keine vermessenen Daten.

## Geplante weitere Profile

Entsprechene Unterordner sind vorgesehen, sobald die zugehörigen Issues bearbeitet werden:

- `data/weather/*.json` – Wetterprofile (Temperatur, Regen, Windgeschwindigkeit)
