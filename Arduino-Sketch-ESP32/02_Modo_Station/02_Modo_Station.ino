#ifdef ESP8266
#include <ESP8266mDNS.h>
#elif defined(ESP32)
#include <WiFi.h>
#else
#error "Placa de desarrollo no encontrada"
#endif

void setup()
{
  Serial.begin(115200);
  Serial.println();

  WiFi.begin("studiomiranda", "88888888");

  Serial.print("Conectando");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Conectado, dirección IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {}
