# ESP32 Arduino

Es una placa de desarrollo IoT creada por la empresa espressif que destaca por permitirnos el creación de proyectos electrónicos a través de redes WiFi. En esta guia veremos algunos de ellos en el entorno de desarrollo Arduino. 

## Configuración

### Arduino IDE

Descarga el [Arduino IDE](https://www.arduino.cc/en/software)

### USB to UART Bridge

Descarga el [Driver CP210x](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers)


### Configurar la placa en Arduino

Selecciona **File > Preferences** e introduce la siguiente línea:
```
https://dl.espressif.com/dl/package_esp32_index.json
```
Selecciona **Tools > Board > Boards Manager…** y busca:
```
ESP32 by Espressif Systems
```
una vez instalado seleccionaremos la placa en **Tools > Board** en mi caso es: **DOIT ESP32 DEVKIT V1** en **Tools > Port** seleccionaremos el puerto, depende del sistema operativo lo veremos como **COM y un número** para windows y  **/dev/cu.SLAB_/USBtoUART** en Mac.

Finalmente selecciona un ejemplo **File > Examples > WiFi (ESP32) > WiFiScan** y realiza un test.

## Conexión WiFi

### Blibiotecas

Biblioteca [#include <WiFi.h>](https://www.arduino.cc/en/Reference/WiFiServer)

Biblioteca [#include <ESP8266WiFi.h>](https://esp8266-arduino-spanish.readthedocs.io/es/latest/esp8266wifi/readme.html)

### Modo Soft Access Point

Un punto de acceso inalámbrico (AP) es un dispositivo que proporciona acceso a la red WiFi a otros dispositivos (estaciones) y los conecta a una red cableada. 

``` cpp
#ifdef ESP8266
#include <ESP8266WiFi.h>
#elif defined(ESP32)
#include <WiFi.h>
#else
#error "Placa de desarrollo no encontrada"
#endif

void setup(void)
{
  Serial.begin(115200);
  
  WiFi.softAP("nombreRed", "contrasena");
  Serial.println("soft Access Point: ");
  Serial.println(WiFi.softAPIP());
  
}

void loop(void)
{
}
``` 

### Modo Station

El modo estación (STA) se utiliza para conectar el módulo ESP a una red WiFi establecida por un punto de acceso.  

```cpp
#ifdef ESP8266
#include <ESP8266WiFi.h>
#elif defined(ESP32)
#include <WiFi.h>
#else
#error "Placa de desarrollo no encontrada"
#endif

void setup(void)
{
  Serial.begin(115200);
  Serial.println();
  
  WiFi.begin("nombre-red", "contraseña-red");

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

void loop(void)
{
}
```

## Servidor Web Asíncrono

### Biblioteca

Biblioteca [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer)

### Método HTTP_GET texto

```cpp
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
  request->send(404, "text/plain", "Page Not found");
}

void setup(void)
{
  
  Serial.begin(115200);
  
  WiFi.softAP("PuntoAcceso", "");
  Serial.println("softAP");
  Serial.println("");
  Serial.println(WiFi.softAPIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
  { 
  request->send(200, "text/plain", "hola mundo");
  });

  server.onNotFound(notFound);

  server.begin();
}


void loop(void)
{
}
```

### Método HTTP_GET html

Tutorial de HTML [w3school](https://www.w3schools.com/html/)

Función [server.on](https://techtutorialsx.com/2017/12/17/esp32-arduino-http-server-getting-query-parameters/)

```cpp
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

char paginaweb[] PROGMEM = R"=====(

<!DOCTYPE html>
<html>
<body>

<center>

<h1>ESP32 HTML</h1>

<h3> LED </h3>

<button onclick="window.location = 'http://'+location.hostname+'/led/on'">On</button>
<button onclick="window.location = 'http://'+location.hostname+'/led/off'">Off</button>

</center>
</body>
</html>

)=====";

#include <ESPAsyncWebServer.h>

AsyncWebServer server(80); // server port 80

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
  
  server.on("/", [](AsyncWebServerRequest * request)
  { 
   
  request->send_P(200, "text/html", paginaweb);
  });

   server.on("/led/on", HTTP_GET, [](AsyncWebServerRequest * request)
  { 
    digitalWrite(Led, HIGH);
  request->send_P(200, "text/html", paginaweb);
  });

  server.on("/led/off", HTTP_GET, [](AsyncWebServerRequest * request)
  { 
    digitalWrite(Led, LOW);
  request->send_P(200, "text/html", paginaweb);
  });

  server.onNotFound(notFound);

  server.begin();  // Finalmente inciamos el servidor
}


void loop(void)
{
}
```

### Método HTTP_GET SPIFFS

Descarga [esp32fs plugin](https://github.com/me-no-dev/arduino-esp32fs-plugin/releases/)

Guárdala en la carpeta en mi caso Documentos/Arduino
```
/tools/ESP32FS/tool/esp32fs.jar
```
Reinicia el programa y vete a la menú **Herramientas** (Tools) y aparecerá una nueva función llamada **ESP32 Sketch Data Upload**

En la misma carpeta del sketch de arduino crea una carpeta llamada **data** e intruduce el archivo para subir a la memoria de tu ESP32, ejecuta la nueva funcionalidad y listo.

```cpp
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

#include "SPIFFS.h"
#include <ESPAsyncWebServer.h>

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

  // Initialize SPIFFS
  if(!SPIFFS.begin(true)){
    Serial.println("A ocurrido un error al montando SPIFFS");
    return;
  }
  
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request){
    request->send(SPIFFS, "/index.html", "text/html");
  });

   server.on("/led/on", HTTP_GET, [](AsyncWebServerRequest * request)
  { 
    digitalWrite(Led, HIGH);
  request->send(SPIFFS, "/index.html", "text/html");
  });

  server.on("/led/off", HTTP_GET, [](AsyncWebServerRequest * request)
  { 
    digitalWrite(Led, LOW);
  request->send(SPIFFS, "/index.html", "text/html");
  });

  server.onNotFound(notFound);

  server.begin();  // Finalmente inciamos el servidor
}


void loop(void)
{
}
```

### WebSockets JavaScript SPIFFS

Biblioteca [WebSocketsServer](https://github.com/Links2004/arduinoWebSockets)

#### Arduino Sketch

```cpp
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
#include "SPIFFS.h"
#include <ESPAsyncWebServer.h>

#define Led 2

AsyncWebServer server(80); 
WebSocketsServer websockets(81);

void notFound(AsyncWebServerRequest *request)
{
  request->send(404, "text/plain", "¡Página no encontrada!");
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

        websockets.sendTXT(num, "Conectado en servidor:");
      }
      break;
    case WStype_TEXT:
      Serial.printf("[%u] Recibe el texto: %s\n", num, payload);
      String mensaje = String((char*)( payload));
      Serial.println(mensaje);

      if(mensaje == "Led esta en OFF"){
        digitalWrite(Led,LOW);
      }

      if(mensaje == "Led esta en ON"){
        digitalWrite(Led,HIGH);
      }
  }
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
    Serial.println("MDNS responder started");
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
}

void loop(void)
{
 websockets.loop();
}
```
#### data HTML

``` html
<!DOCTYPE html>
<html>

<script>

var connection = new WebSocket('ws://'+location.hostname+':81/');

function button_1_on()
{
  console.log("Led esta en ON");
  connection.send("Led esta en ON");
}

function button_1_off()
{
console.log("Led esta en OFF");
connection.send("Led esta en OFF");
}


</script>
<body>

<center>
<h1>ESP32 Led on/off</h1>

<h3> LED </h3>
<button onclick= "button_1_on()" >On</button>
<button onclick="button_1_off()" >Off</button>
</center>
</body>
</html>
```