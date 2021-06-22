#include <Motor.h>
Motor motor = Motor(5, 6, motor2, motor2, velocidad, activado);

uint8_t Velocidad = 255;

void setup() {}

void loop() 
{
    motor.Avanzar(Velocidad);
    delay(1000);
    motor.GirarIzquierda(Velocidad);
    delay(1000);
    motor.GirarDerecha(Velocidad);
    delay(1000);
    motor.Retroceder(Velocidad);
    delay(1000);
    motor.Parar(velocidad);
    delay(1000);
}
