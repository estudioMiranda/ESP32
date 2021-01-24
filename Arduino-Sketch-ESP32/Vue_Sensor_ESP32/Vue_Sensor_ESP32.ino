#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#elif defined(ESP32)
#include <WiFi.h>
#include <ESPmDNS.h>
#else
#error "Placa de desarrollo no encontrada"
#endif

#include <WebSocketsServer.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>
#include <DHT.h> 
#include <Ticker.h>

#define DHTPIN 4
#define Led 2

#define DHTTYPE    DHT11
DHT dht(DHTPIN, DHTTYPE);

void send_sensor();

Ticker timer;

#include <ESPAsyncWebServer.h>

AsyncWebServer server(80); 
WebSocketsServer websockets(81);

void notFound(AsyncWebServerRequest *request)
{
  request->send(404, "text/plain", "Página no encontrada");
}


void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {

  switch (type) 
  {
    case WStype_DISCONNECTED:
      Serial.printf("[%u] ¡Desconectado!\n", num);
      break;
    case WStype_CONNECTED: {
        IPAddress ip = websockets.remoteIP(num);
        Serial.printf("[%u] Conectado en %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
      }
      break;
    case WStype_TEXT:
      Serial.printf("[%u] Texto: %s\n", num, payload);
      String mensaje = String((char*)( payload));
      Serial.println(mensaje);

      
     DynamicJsonDocument doc(200);
  
    DeserializationError error = deserializeJson(doc, mensaje);
   
  if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    return;
  }

  int Led_status = doc["Led"];
 
  digitalWrite(Led,Led_status);

  }
}

void setup(void)
{
  
  Serial.begin(115200);
  pinMode(Led, OUTPUT);
  dht.begin();
  
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



  if (MDNS.begin("ESP")) { //esp.local/
    Serial.println("MDNS iniciado");
  }
  
  if(!SPIFFS.begin(true)){
    Serial.println("A ocurrido un error al montar SPIFFS");
    return;
  }

   server.on("/", HTTP_GET, [](AsyncWebServerRequest * request)
  { 
   request->send(SPIFFS, "/index.html", "text/html");
  });

  server.onNotFound(notFound);

  server.begin();
  websockets.begin();
  websockets.onEvent(webSocketEvent);
  timer.attach(2,send_sensor);

}

void loop(void)
{
 websockets.loop();
}

void send_sensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
    if (isnan(h) || isnan(t) ) {
    Serial.println(F("Fallo de lectura en sensor DHT11!"));
    return;
  }
  String JSON_Data = "{\"temp\":";
         JSON_Data += t;
         JSON_Data += ",\"hum\":";
         JSON_Data += h;
         JSON_Data += "}";
   Serial.println(JSON_Data);     
  websockets.broadcastTXT(JSON_Data);
}
