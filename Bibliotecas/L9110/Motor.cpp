#include "Motor.h"

Motor::Motor( uint8_t _motor1Pin1,
              uint8_t _motor1Pin2,
              uint8_t _motor2Pin1,
              uint8_t _motor2Pin2,
              uint8_t _motorVelocidad,
              uint8_t _motorActivado
            )

{
  motor1Pin1=_motor1Pin1;
  motor1Pin2=_motor1Pin2;
  motor2Pin1=_motor2Pin1;
  motor2Pin2=_motor2Pin2;
  motorActivado=_motorActivado;
  motorVelocidad=_motorVelocidad;
  pinMode(motorPin1,OUTPUT);
  pinMode(motorPin2,OUTPUT);
  pinMode(motorActivado,OUTPUT);
  PinMode(motorSpeed, OUTPUT)
}

void Motor::Avanzar(Velocidad)
{
  digitalWrite(motor1Pin1,HIGH);
  digitalWrite(motor1Pin2,LOW);
  digitalWrite(motor2Pin1,HIGH);
  digitalWrite(motor2Pin2,LOW);
  digitalWrite(motorActivado,HIGH);
  analogWrite(motorVelocidad,Velocidad)
}
void Motor::Retroceder(Velocidad)
{
  digitalWrite(motor1Pin1,LOW);
  digitalWrite(motor1Pin2,HIGH);
  digitalWrite(motor2Pin1,LOW);
  digitalWrite(motor2Pin2,HIGH);
  digitalWrite(motorActivado,HIGH);
  analogWrite(motorVelocidad,Velocidad)
}
void Motor::GirarIzquierda(Velocidad)
{
  digitalWrite(motor1Pin1,HIGH);
  digitalWrite(motor1Pin2,LOW);
  digitalWrite(motor2Pin1,LOW);
  digitalWrite(motor2Pin2,HIGH);
  digitalWrite(motorActivado,HIGH);
  analogWrite(motorVelocidad,Velocidad)
}
void Motor::GirarDerecha(Velocidad)
{
  digitalWrite(motor1Pin1,LOW);
  digitalWrite(motor1Pin2,HIGH);
  digitalWrite(motor2Pin1,HIGH);
  digitalWrite(motor2Pin2,LOW);
  digitalWrite(motorActivado,HIGH);
  analogWrite(motorVelocidad,Velocidad)
}

void Motor::Parar()
{
  digitalWrite(motor1Pin1,LOW);
  digitalWrite(motor1Pin2,LOW);
  digitalWrite(motor2Pin1,LOW);
  digitalWrite(motor2Pin2,LOW);
  digitalWrite(motorActivado,LOW);
  analogWrite(motorVelocidad,0)
}

