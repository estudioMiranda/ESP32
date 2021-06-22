#include "Motor.h"

Motor::Motor( uint8_t _motor1Pin1,
              uint8_t _motor1Pin2,
              uint8_t _motor2Pin1,
              uint8_t _motor2Pin2,
              uint8_t _motorVelocidad,
              uint8_t _motorActivado,
              uint8_t _Velocidad
            )

{
  motor1Pin1=_motor1Pin1;
  motor1Pin2=_motor1Pin2;
  motor2Pin1=_motor2Pin1;
  motor2Pin2=_motor2Pin2;
  motorActivado=_motorActivado;
  motorVelocidad=_motorVelocidad;
  Velocidad=_Velocidad;
  pinMode(motor1Pin1,OUTPUT);
  pinMode(motor1Pin2,OUTPUT);
  pinMode(motor2Pin1,OUTPUT);
  pinMode(motor2Pin2,OUTPUT);
  pinMode(motorActivado,OUTPUT);
  pinMode(motorVelocidad,OUTPUT);
}

void Motor::Avanzar()
{
  digitalWrite(motor1Pin1,HIGH);
  digitalWrite(motor1Pin2,LOW);
  digitalWrite(motor2Pin1,HIGH);
  digitalWrite(motor2Pin2,LOW);
  digitalWrite(motorActivado,HIGH);
  analogWrite(motorVelocidad,Velocidad);
}
void Motor::Retroceder()
{
  digitalWrite(motor1Pin1,LOW);
  digitalWrite(motor1Pin2,HIGH);
  digitalWrite(motor2Pin1,LOW);
  digitalWrite(motor2Pin2,HIGH);
  digitalWrite(motorActivado,HIGH);
  analogWrite(motorVelocidad,Velocidad);
}
void Motor::GirarIzquierda()
{
  digitalWrite(motor1Pin1,HIGH);
  digitalWrite(motor1Pin2,LOW);
  digitalWrite(motor2Pin1,LOW);
  digitalWrite(motor2Pin2,HIGH);
  digitalWrite(motorActivado,HIGH);
  analogWrite(motorVelocidad,Velocidad);
}
void Motor::GirarDerecha()
{
  digitalWrite(motor1Pin1,LOW);
  digitalWrite(motor1Pin2,HIGH);
  digitalWrite(motor2Pin1,HIGH);
  digitalWrite(motor2Pin2,LOW);
  digitalWrite(motorActivado,HIGH);
  analogWrite(motorVelocidad,Velocidad);
}

void Motor::Parar()
{
  digitalWrite(motor1Pin1,LOW);
  digitalWrite(motor1Pin2,LOW);
  digitalWrite(motor2Pin1,LOW);
  digitalWrite(motor2Pin2,LOW);
  digitalWrite(motorActivado,LOW);
  analogWrite(motorVelocidad,0);
}

