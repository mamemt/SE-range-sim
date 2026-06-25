# Modellannahmen

Dieses Dokument beschreibt die Annahmen und Formeln, die in `calculate_feasibility` zur Berechnung des Energieverbrauchs verwendet werden. Die Faktoren sind vereinfacht und erheben keinen Anspruch auf physikalische Genauigkeit.

Alle Faktoren sind dimensionslos. Werte > 1 erhöhen den Verbrauch, Werte < 1 senken ihn.

## Temperaturfaktor

    temperature_factor = 1 + (50 - temperature_celsius) * 0.0005

Bei 20 °C ergibt sich 1,015 (+1,5 %). Kältere Temperaturen erhöhen den Verbrauch, wärmere senken ihn leicht. Neutralpunkt liegt bei 50 °C.

## Windfaktor

    wind_factor = 1 + wind_speed_kmh * 0.0005

Jeder km/h Wind erhöht den Verbrauch um 0,05 %. Bei 60 km/h ergibt sich 1,03 (+3 %). Windrichtung wird nicht berücksichtigt (immer Gegenwind).

## Regenfaktor

    rain_factor = 1 + precipitation_mm_per_h * 0.0005

Regen erhöht den Verbrauch leicht. Bei 10 mm/h ergibt sich 1,005 (+0,5 %).

## Gesamtwetterfaktor

    weather_factor = temperature_factor * wind_factor * rain_factor

    Die drei Einzelfaktoren werden multipliziert.

## Höhenmeter-Faktor

    elevation_factor = 1 + elevation_gain_m * 0.0001

Nur Höhengewinn wird berücksichtigt, kein Rekuperationsgewinn bei Gefälle. Bei 500 m ergibt sich 1,05 (+5 %).

## Streckentyp-Faktoren

Je nach Streckentyp wird ein Faktor angesetzt:

- Stadt: 1,3 -> häufiges Bremsen/Beschleunigen und Stau erhöhen den Verbrauch
- Land: 0,9 -> gleichmäßige mittlere Geschwindigkeit ist energetisch günstig
- Autobahn: 1,1 -> hohe Geschwindigkeit erhöht den Luftwiderstand

Die gewichtete Kombination:

    route_factor = (share_city_percent * 1.3 + share_rural_percent * 0.9 + share_highway_percent * 1.1) / 100.0

## Gesamtfaktor und Verbrauch

    total_factor              = weather_factor * elevation_factor * route_factor
    consumption_kwh_per_100km = base_consumption_kwh_per_100km * total_factor
    total_consumption_kwh     = consumption_kwh_per_100km * distance_km / 100.0
    