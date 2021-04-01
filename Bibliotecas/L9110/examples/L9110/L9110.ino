#include <Motor.h>
Motor motor = Motor(27,26,25,33);

void setup() {}

void loop()
{
    motor.Avanzar();
    delay(1000);
    motor.GirarDerecha();
    delay(1000);
    motor.GirarIzquierda();
    delay(1000);
    motor.Retroceder();
    delay(1000);
    motor.Parar();
    delay(4000);
}
