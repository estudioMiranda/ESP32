#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#elif defined(ESP32)
#include <WiFi.h>
#include <ESPmDNS.h>
#else
#error "Placa de desarrollo no encontrada"
#endif

#define Led 2

#include <ESPAsyncWebServer.h>

char pagina[] PROGMEM = R"=====(

<!DOCTYPE html>
<html>
<body>

<center>
<h1> ESP HTML </h1>

<h3> LED </h3>
<button onclick="window.location = 'http://'+location.hostname+'/led/on'">On</button>
<button onclick="window.location = 'http://'+location.hostname+'/led/off'">Off</button>

</center>
</body>
</html>

)=====";

AsyncWebServer server(80);

void notFound(AsyncWebServerRequest *request)
{
  request->send(404, "text/plain", "Página no encontrada");
}

void setup(void)
{
  
  Serial.begin(115200);
  pinMode(Led, OUTPUT);

  
  WiFi.softAP("PuntoAcceso", "");
  Serial.println("softAP");
  Serial.println("");
  Serial.println(WiFi.softAPIP());


  if (MDNS.begin("ESP")) { //esp.local/
    Serial.println("MDNS iniciado");
  }
  
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request){
    request->send_P(200, "text/html", pagina);
  });

   server.on("/led/on", HTTP_GET, [](AsyncWebServerRequest * request)
  { 
    digitalWrite(Led, HIGH);
  request->send_P(200, "text/html", pagina);
  });

  server.on("/led/off", HTTP_GET, [](AsyncWebServerRequest * request)
  { 
    digitalWrite(Led, LOW);
  request->send_P(200, "text/html", pagina);
  });

  server.onNotFound(notFound);

  server.begin();  // Finalmente inciamos el servidor
}


void loop(void)
{
}
