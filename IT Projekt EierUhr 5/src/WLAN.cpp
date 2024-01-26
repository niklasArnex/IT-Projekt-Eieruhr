// WLAN.cpp

#include "WLAN.h"
#include <WiFi.h>
#include <ESPAsyncWebServer.h>

// Definiere die WiFi-Zugangsdaten für das lokale Netzwerk
const char *localSSID = "DEIN_LOKALER_SSID";
const char *localPassword = "DEIN_LOKALES_PASSWORT";

// Definiere die WiFi-Zugangsdaten für den Access Point
const char *apSSID = "ESP32_ACCESS_POINT";
const char *apPassword = "ACCESS_POINT_PASSWORT";

// Definiere die AsyncWebServer-Instanz
AsyncWebServer server(80);

void connectToWiFi()
{
  // Verbinde nur, wenn nicht bereits verbunden
  if (WiFi.status() != WL_CONNECTED)
  {
    // Verbinde mit dem lokalen WLAN
    WiFi.begin(localSSID, localPassword);

    // Warte maximal 10 Sekunden, bis die Verbindung hergestellt ist
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 10)
    {
      delay(1000);
      Serial.println("Verbindung wird hergestellt...");
      attempts++;
    }

    // Zeige die IP-Adresse an, wenn die Verbindung hergestellt wurde
    if (WiFi.status() == WL_CONNECTED)
    {
      Serial.println("Verbunden mit dem lokalen WLAN!");
      Serial.print("IP-Adresse: ");
      Serial.println(WiFi.localIP());
    }
    else
    {
      Serial.println("Verbindung mit dem lokalen WLAN fehlgeschlagen.");
    }
  }
  else
  {
    Serial.println("Bereits verbunden mit dem WLAN.");
  }
}

void startAccessPoint()
{
  // Starte den Access Point
  WiFi.softAP(apSSID, apPassword);

  Serial.println("Access Point gestartet:");
  Serial.print("IP-Adresse: ");
  Serial.println(WiFi.softAPIP());
}

void setupWebServer()
{
  // Beispiel-Handler für die Startseite des Webservers
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(200, "text/html", "<h1>Hallo vom ESP32 Webserver!</h1>"); });

  // Hier kannst du weitere Handler für deine spezifischen Anforderungen hinzufügen

  // Starte den Webserver
  server.begin();
}

void setupWiFi()
{
  // Versuche, dich mit dem lokalen WLAN zu verbinden
  connectToWiFi();

  // Starte den Access Point, falls nicht mit dem lokalen WLAN verbunden
  if (WiFi.status() != WL_CONNECTED)
  {
    startAccessPoint();
    setupWebServer(); // Starte den Webserver nur, wenn im Access Point-Modus
  }
}
