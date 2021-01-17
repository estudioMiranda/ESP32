#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#elif defined(ESP32)
#include <WiFi.h>
#include <ESPmDNS.h>
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


  if (MDNS.begin("ESP")) { //esp.local/
    Serial.println("MDNS iniciado");
  }



  server.on("/", [](AsyncWebServerRequest * request)
  { 
   String mensaje = "hola munndo"; 
  request->send(200, "text/plain", mensaje);
  });

   server.on("/pagina1", HTTP_GET, [](AsyncWebServerRequest * request)
  { 
   String mensaje = "Bienvenido a la página 1"; 
  request->send(200, "text/plain", mensaje);
  });

  server.onNotFound(notFound);

  server.begin();
}


void loop(void)
{
}
