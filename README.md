# ESP32 Arduino
 
Hola y bienvenidos a este tutorial,

[![Introducción](../.vuepress/public/img/introduccion.png)](https://www.youtube.com/watch?v=dZ59MDPcrqo&list=PLgh8bcLDakt3KLia5B5ZIEbvhxp41EPiE)


En este tutorial aprenderemos a programar el microcontrolador ESP32 de espressif con el IDE de Arduino. Este microcontrolador programable es muy popular por que integra conectividad WiFi y Bluetooth a un precio muy económico que lo hace ideal para proyectos IoT “internet de las cosas”.

Podemos encontrar DevKits o placas de desarrollo, que además, integran cámara y micrófono para proyectos de video vigilancia o también micrófono y salida de audio para crear nuestro propio asistente de voz. 

Como vemos las posibilidades son infinitas.

Hablemos ahora de su precio y donde comprarlas, rondan desde 6 €/$ (en tiendas chinas) hasta unos 10 €/$ en amazon.

Yo utilizo esta que recomiendan aquí:

RandomNerdTutorials [DOIT ESP32 DEVKIT V1](https://randomnerdtutorials.com/getting-started-with-esp32/)

Donde comprar [DOIT ESP32 DEVKIT V1](https://makeradvisor.com/tools/esp32-dev-board-wi-fi-bluetooth/)

que utilizo para el desarrollo de los tutoriales


## Configuración

### Arduino IDE

Descarga el [Arduino IDE](https://www.arduino.cc/en/software)

### USB to UART Bridge

Descarga el [Driver CP210x](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers)

[![Instalación](../.vuepress/public/img/instalacion.png)](https://youtu.be/HYHlZOjQw4Q)



### Configurar la placa en Arduino

Aquí os dejo dos direcciones que utilizo y funcionan, a día de hoy claro.

Desde [randomnerdtutorials.com](https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/)

Selecciona **File > Preferences** e introduce la siguiente línea:
```
https://dl.espressif.com/dl/package_esp32_index.json
```
ó desde [github.com/espressif](https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/boards_manager.md)

```
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
```
[![Configuración](../.vuepress/public/img/configuracion.png)](https://youtu.be/KuRgwLvH9WY)

Selecciona **Tools > Board > Boards Manager…** y busca:
```
ESP32 by Espressif Systems
```
una vez instalado seleccionaremos la placa en **Tools > Board** en mi caso es: **DOIT ESP32 DEVKIT V1** en **Tools > Port** seleccionaremos el puerto, depende del sistema operativo lo veremos como **COM y un número** para windows y  **/dev/cu.SLAB_/USBtoUART** en Mac.

Finalmente selecciona un ejemplo **Archivo > Ejemplos > Basics > Blink** y realiza un test.

Si quieres comprobar la conexión WiFi selecciona el ejemplo **File > Examples > WiFi (ESP32) > WiFiScan** y realiza un test.

[![Test](../.vuepress/public/img/test.png)](https://youtu.be/_WU5XLTfZTY)

## Bibliotecas

### Instalación

Existen tres formas de incorporar **bibliotecas**:

1. Abre un panel de búsqueda e instalación de bibliotecas en:

  **Programa > Incluir Librerías > Administrar bibliotecas**

2. Descarga de internet la biblioteca en formato zip

  **Programa > Incluir Librerías > Añadir biblioteca .ZIP**

3. Descomprime el fichero ZIP, copia y pega (elimina **master** del nombre de la carpeta) en:

  **Documentos > Arduino > libraries**  

[![Bibliotecas](../.vuepress/public/img/bibliotecas.png)](https://youtu.be/lUjWCWW0IRg)


### Descarga Bibliotecas

Descarga [Paquete de Bibliotecas](https://github.com/espressif/arduino-esp32)

Descarga [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer)

Descarga [AsyncTCP](https://github.com/me-no-dev/AsyncTCP)

Descarga [SPIFFS](https://github.com/espressif/arduino-esp32/tree/master/libraries/SPIFFS)

Descarga [ArduinoJson](https://github.com/bblanchon/ArduinoJson)

Descarga [ArduinoWebSockets](https://github.com/Links2004/arduinoWebSockets)

## Conexión WiFi

### Modo Soft Access Point

Un punto de acceso inalámbrico (AP) proporciona acceso a través de su red WiFi a otros dispositivos (estaciones). La placa de desarrollo crea su propia red WiFi y permite la comunicación directa a un dispositivo (movil, computadora o una tablet)

Biblioteca [#include <WiFi.h>](https://www.arduino.cc/en/Reference/WiFiServer)

Biblioteca [#include <ESP8266WiFi.h>](https://esp8266-arduino-spanish.readthedocs.io/es/latest/esp8266wifi/readme.html)

[![Access Point](../.vuepress/public/img/ap.png)](https://youtu.be/OEH6mfhxB70)

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

El modo estación (STA) se utiliza para conectar el módulo ESP a una red WiFi mediante un router o punto de acceso que conecta con otros dispositivos que estan en la red local o bien a través de internet. 

[![Station](../.vuepress/public/img/station.png)](https://www.youtube.com/watch?v=HYHlZOjQw4Q&list=PLgh8bcLDakt3KLia5B5ZIEbvhxp41EPiE&index=2)


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

[![HTTP_GET texto](../.vuepress/public/img/texto.png)](https://youtu.be/bastIzh3v1U)

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

### Método HTTP_GET HTML

Tutorial de HTML [w3school](https://www.w3schools.com/html/)

Función [server.on](https://techtutorialsx.com/2017/12/17/esp32-arduino-http-server-getting-query-parameters/)

[![HTTP_GET HTML](../.vuepress/public/img/html.png)](https://youtu.be/nErkSCEuSOA)

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

[![HTTP_GET SPIFFS](../.vuepress/public/img/spiffs.png)](https://youtu.be/k2VoVac-arM)

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

[![WebSockets JavaScript](../.vuepress/public/img/websockets.png)](https://www.youtube.com/watch?v=HYHlZOjQw4Q&list=PLgh8bcLDakt3KLia5B5ZIEbvhxp41EPiE&index=2)

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
### WebSockets Json

Biblioteca [ArduinoJson](https://github.com/bblanchon/ArduinoJson)

Biblioteca DHT sensor library (Instalar del Gestor de Bibliotecas de Arduino)

Biblioteca Ticker (Instalar del Gestor de Bibliotecas de Arduino)

[Ticker](https://www.arduino.cc/reference/en/libraries/ticker/)
Llama funciones en un intervalo establecido

[![WebSockets Json](../.vuepress/public/img/websockets.png)](https://www.youtube.com/watch?v=HYHlZOjQw4Q&list=PLgh8bcLDakt3KLia5B5ZIEbvhxp41EPiE&index=2)

#### Arduino Sketch

```cpp


#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <WebSocketsServer.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>
#include <DHT.h> 
#include <Ticker.h>

#define DHTPIN 4
#define Led 2

#define DHTTYPE    DHT11
DHT dht(DHTPIN, DHTTYPE);

void enviarDatosSensor();

Ticker timer;

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
      
      DynamicJsonDocument doc(200); // documento (capacidad)
      DeserializationError error = deserializeJson(doc, mensaje);
      if (error) {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.c_str());
        return;
        }
        
      int estadoLed = doc["Led"]; // el estado será de 0 o 1
      digitalWrite(Led,estadoLed);
      }
}

void setup(void)
{
  
  Serial.begin(115200);
  pinMode(Led, OUTPUT);
  dht.begin();
  
  WiFi.softAP("PuntoAcceso", "");
  Serial.println("softAP");
  Serial.println("");
  Serial.println(WiFi.softAPIP());
  
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
  
  timer.attach(2,enviarDatosSensor); // Ticker timer (Llama funciones en un intervalo establecido)

}

void loop(void) {
  websockets.loop();
}

void enviarDatosSensor() {
  
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
   websockets.broadcastTXT(JSON_Data);  // envia datos a todos los clientes conectados
}
```
#### Arduino Sketch

```html
<!DOCTYPE html>
<meta charset="UTF-8">

<script>

var connection = new WebSocket('ws://'+location.hostname+':81/');

var estado_boton = 0;
var temperatura = 0;
var humedad = 0;

connection.onmessage = function(event){

  var datos_sensores = event.data;
  var data = JSON.parse(datos_sensores);
  temperatura = data.temp;
  humedad = data.hum;
  document.getElementById("temp_meter").value = temperatura;
  document.getElementById("temp_value").innerHTML = temperatura;
  document.getElementById("hum_meter").value = humedad;
  document.getElementById("hum_value").innerHTML = humedad;
}

function button_on()
{
   estado_boton = 1; 
  console.log("Led is ON");
  send_data();
}

function button_off()
{
  estado_boton = 0;
console.log("Led is OFF");
send_data();
}

function send_data()
{
  var led_estado= '{"Led" :'+estado_boton+'}';
  connection.send(led_estado);
}

</script>

<body>
<center>

<h1>ESP32 Digital output Botón y PWM input sensor Temperatura y Humedad</h1>

<h3> Led </h3>
<button onclick= "button_on()">On</button>
<button onclick= "button_off()">Off</button>

<h3>Temperatura</h3>
<meter value="2" min="0" max="100" id="temp_meter"> </meter>
<h3 id="temp_value" style="display: inline-block;"> 2 </h3>

<h3>Humedad</h3>
<meter value="2" min="0" max="100" id="hum_meter"> </meter>
<h3 id="hum_value" style="display: inline-block;"> 2 </h3>

</center>
</body>

</html>
```

### WebSockets Vue.js SPIFFS

JavaScript Framework [Vue.js v.3](https://v3.vuejs.org/)

[![WebSockets Vue.js](../.vuepress/public/img/websocketsVue.png)](https://www.youtube.com/watch?v=HYHlZOjQw4Q&list=PLgh8bcLDakt3KLia5B5ZIEbvhxp41EPiE&index=2)

#### Arduino Sketch

```cpp
Arduino Sketch
```
HTML Vue.js
```html
<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ESP32</title> 
    <script src="https://unpkg.com/vue@next"></script>
</head>
<body>
    <div id="app">
      <center>
            <h1>ESP32 Digital output Botón y PWM input sensor Temperatura y Humedad</h1>
                <h3> Led </h3>
                    <button @click= "buttonOn" >On</button>
                    <button @click= "buttonOff" >Off</button>
                    <div style="text-align: center;">
                <h3>Temperatura</h3>
                    <meter :value="temperatura" min="0" max="100"> </meter>
                    <h3 style="display: inline-block;"> {{ temperatura }} </h3>
                <h3>Humedad</h3>
                    <meter :value="humedad" min="0" max="100"> </meter>
                    <h3 style="display: inline-block;"> {{ humedad }} </h3>
          </center>      
    </div>
    <script>
        const app = {
    data() {
      return {
        temperatura: 0,
        humedad: 0,
        buttonStatus: 0,
        connection : new WebSocket('ws://'+location.hostname+':81/')
      }
    },
    
    methods: {

      onMessage(event){
        var datosTH = event.data;
        console.log(datosTH);
        // Convertimos el JSON en datos
        var data = JSON.parse(datosTH);
        this.temperatura = data.temp;
        this.humedad = data.hum;
      },
      
      buttonOn(){
        this.buttonStatus = 1; 
        console.log("Led is ON")
        this.send_data()
      },

      buttonOff(){
        this.buttonStatus = 0;
        console.log("Led is OFF")
        this.send_data()
      },
      
      send_data(){
        var full_data = '{"Led" :'+this.buttonStatus+'}'
        this.connection.send(full_data)
      },
    },
    
    mounted() {
      this.connection.onmessage = event => {
        this.onMessage(event)
      }
  }
}

Vue.createApp(app).mount('#app')
    </script>  
</body>
</html>
```
## Crear una Biblioteca en Arduino

Morse [Library](https://www.arduino.cc/en/Hacking/LibraryTutorial)

Necesitamos al menos de dos archivos para una biblioteca: 
- Morse.h
- Morse.cpp


### Encabezado (Morse.h)

El archivo de encabezado tiene definiciones para la biblioteca: básicamente una lista de todo lo que hay dentro.

[![Crear Biblioteca](../.vuepress/public/img/crearBiblioteca.png)](https://www.youtube.com/watch?v=HYHlZOjQw4Q&list=PLgh8bcLDakt3KLia5B5ZIEbvhxp41EPiE&index=2)

```cpp
#ifndef Morse_h
#define Morse_h

#include "Arduino.h"

class Morse
{
  public:
    Morse(int pin);
    void dot();
    void dash();
  private:
    int _pin;
};

#endif
```

Es común envolver todo el archivo de encabezado en una construcción de aspecto extraño
```cpp
#ifndef Morse_h
#define Morse_h

#endif
```
Básicamente, esto evita problemas si alguien # incluye accidentalmente su biblioteca dos veces.

```cpp
#include "Arduino.h"
```

Una es una declaración **#include** que le da acceso a los tipos y constantes estándar del lenguaje Arduino.

Una clase es simplemente una colección de funciones y variables que se mantienen juntas en un solo lugar. Pueden ser públicas , lo que significa que son accesibles desde cualquier parte a ellas, o privadas , lo que significa que solo se puede acceder a ellas desde la propia clase. Cada clase tiene una función especial conocida como constructor , que se utiliza para crear una instancia de la clase. El constructor tiene el mismo nombre que la clase y no tiene tipo de retorno.

### Origen (*.cpp)

El archivo fuente tiene el código real:

```cpp
#include "Arduino.h"
#include "Morse.h"

Morse::Morse(int pin)
{
  pinMode(pin, OUTPUT);
  _pin = pin;
}

void Morse::dot()
{
  digitalWrite(_pin, HIGH);
  delay(250);
  digitalWrite(_pin, LOW);
  delay(250);  
}

void Morse::dash()
{
  digitalWrite(_pin, HIGH);
  delay(1000);
  digitalWrite(_pin, LOW);
  delay(250);
}
```
Primero vienen un par de declaraciones #include. Estos le dan al resto del código acceso a las funciones estándar de Arduino y a las definiciones en su archivo de encabezado:

```cpp
#include "Arduino.h"
#include "Morse.h"
```
Luego viene el constructor. Nuevamente, esto explica lo que debería suceder cuando alguien crea una instancia de su clase. En este caso, el usuario especifica qué pin le gustaría usar. Configuramos el pin como una salida y lo guardamos en una variable privada para usar en las otras funciones:

```cpp
Morse::Morse(int pin)
{
  pinMode(pin, OUTPUT);
  _pin = pin;
}
```

Luego viene el código real del boceto que está convirtiendo en una biblioteca

```cpp
void Morse::dot()
{
  digitalWrite(_pin, HIGH);
  delay(250);
  digitalWrite(_pin, LOW);
  delay(250);  
}

void Morse::dash()
{
  digitalWrite(_pin, HIGH);
  delay(1000);
  digitalWrite(_pin, LOW);
  delay(250);
}
```
### Sketch + Biblioteca

```cpp
#include <Morse.h>

Morse morse(13);

void setup()
{
}

void loop()
{
  morse.dot(); morse.dot(); morse.dot(); // ...

  morse.dash(); morse.dash(); morse.dash(); // ---

  morse.dot(); morse.dot(); morse.dot(); // ...

  delay(3000);
}
```
Incluimos la librería y llamamos al constructor

```cpp
#include <Morse.h>

Morse morse(13);
```
Ejecutamos las funciones (métodos) de la clase:

```cpp
morse.dot();
morse.dash();
```
