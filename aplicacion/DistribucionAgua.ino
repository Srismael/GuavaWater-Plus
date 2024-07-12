#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "TU_SSID";
const char* password = "TU_PASSWORD";
const char* apiUrl = "http://tu-api-url.com/get_times";  // Cambia esto por la URL de tu API

const int relayPins[] = {26};  // Pines del ESP32 conectados a los relés
const int numRelays = 1;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }
  Serial.println("Conectado a WiFi");

  for (int i = 0; i < numRelays; i++) {
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], HIGH);  // Asegúrate de que los relés estén inicialmente apagados
  }
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(apiUrl);
    int httpCode = http.GET();

    if (httpCode > 0) {
      String payload = http.getString();
      Serial.println(payload);

      // Parse the payload to get the times and control the relays
      // Supongamos que el payload es un JSON como {"relay1": 1000, "relay2": 2000}
      DynamicJsonDocument doc(512);
      deserializeJson(doc, payload);

      for (int i = 0; i < numRelays; i++) {
        int time = doc["relay" + String(i + 1)];
        digitalWrite(relayPins[i], LOW);  // Abre la válvula
        delay(time);
        digitalWrite(relayPins[i], HIGH);  // Cierra la válvula
      }
    }

    http.end();
  }

  delay(60000);  // Espera un minuto antes de la siguiente consulta
}
