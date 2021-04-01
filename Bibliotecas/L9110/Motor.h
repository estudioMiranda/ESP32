#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
class Motor
{
  public:
    Motor(uint8_t _motor1Pin1,
          uint8_t _motor1Pin2,
          uint8_t _motor2Pin1,
          uint8_t _motor2Pin2,
          uint8_t _motorActivado, 
          uint8_t _motorVelocidad);

    void Avanzar(Velocidad);
    void Retroceder(Velocidad);
    void GirarIzquierda(Velocidad);
    void GirarDerecha(Velocidad)
    void Parar();
  private:
    uint8_t motor1Pin1,motor1Pin2,motor2Pin1,motor2Pin2,motorVelocidad,motorActivado;
};
#endif
