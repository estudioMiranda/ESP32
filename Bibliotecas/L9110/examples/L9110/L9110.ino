#include <Motor.h>
Motor motor = Motor(5, 6, 7, 8, 4, 3, 5);
uint8_t Velocidad = 255;

void setup() {}

void loop() 
{
    motor.Avanzar();
    delay(1000);
    motor.GirarIzquierda();
    delay(1000);
    motor.GirarDerecha();
    delay(1000);
    motor.Retroceder();
    delay(1000);
    motor.Parar();
    delay(1000);
}
