#include <WiFi.h>

void setup(void)
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

void loop(void)
{
}
