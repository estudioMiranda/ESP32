#ifdef ESP8266
#include <ESP8266WiFi.h>
#elif defined(ESP32)
#include <WiFi.h>
#else
#error "Placa de desarrollo no encontrada"
#endif

#include <ESPAsyncWebServer.h>

AsyncWebServer server(80);

void notFound(AsyncWebServerRequest *request)
{
  request->send(404, "text/plain", "Página no encontrada");
}

void setup(void)
{
  
  Serial.begin(115200);
  
  WiFi.softAP("PuntoAcceso", "");
  Serial.println("softAP");
  Serial.println("");
  Serial.println(WiFi.softAPIP());

  server.on("/", [](AsyncWebServerRequest * request)
  { 
  request->send(200, "text/plain", "hola mundo");
  });

  server.onNotFound(notFound);

  server.begin();
}


void loop(void)
{
}
