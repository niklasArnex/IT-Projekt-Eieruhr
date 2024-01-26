#ifndef WLAN_H
#define WLAN_H

#include <ESPAsyncWebServer.h>

// Deklariere die WiFi-Zugangsdaten für das lokale Netzwerk
extern const char *localSSID;
extern const char *localPassword;

// Deklariere die WiFi-Zugangsdaten für den Access Point
extern const char *apSSID;
extern const char *apPassword;

// Funktion zur WLAN-Verbindung
void connectToWiFi();

// Funktion zum Starten des Access Points
void startAccessPoint();

void setupWiFi();

#endif