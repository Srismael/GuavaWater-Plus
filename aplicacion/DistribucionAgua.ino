#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

// URL de la API
const char* api_url = "http://api.example.com/valve";

// Pin de la válvula
const int valvePin = 26;

void setup() {
  Serial.begin(115200);
  
  // Conectar a WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Configurar el pin de la válvula como salida
  pinMode(valvePin, OUTPUT);

  // Asegurarse de que la válvula esté cerrada al inicio
  digitalWrite(valvePin, LOW);
}

void loop() {
  // Verificar y activar la válvula según la API
  checkAndActivateValve(api_url, valvePin);

  // Esperar un tiempo antes de volver a comprobar
  delay(10000);  // 10 segundos de espera entre comprobaciones
}

void checkAndActivateValve(const char* api_url, int valvePin) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(api_url);
    int httpResponseCode = http.GET();

    if (httpResponseCode == 200) {
      String payload = http.getString();
      Serial.println("Received payload: " + payload);

      // Parsear el JSON recibido
      StaticJsonDocument<200> doc;
      DeserializationError error = deserializeJson(doc, payload);

      if (error) {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.c_str());
        return;
      }

      // Extraer los datos del JSON
      const char* zone = doc["zone"];
      int duration = doc["duration"];  // Duración en minutos

      Serial.print("Zone: ");
      Serial.println(zone);
      Serial.print("Duration: ");
      Serial.println(duration);

      if (String(zone) == "zona 1" && duration > 0) {
        Serial.print("Activating valve for ");
        Serial.print(duration);
        Serial.println(" minutes");

        // Abrir la válvula
        digitalWrite(valvePin, HIGH);
        delay(duration * 60000);  // Convertir minutos a milisegundos
        // Cerrar la válvula
        digitalWrite(valvePin, LOW);
      }
    } else {
      Serial.print("Error on HTTP request: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  } else {
    Serial.println("WiFi not connected");
  }
}