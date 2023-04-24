#include <Servo.h>
Servo servo;

const int piezoPin = A1;
const int potPin = A0;
const int servoPin = 3;
const int motorPin = 5;
const int buttonGreen = 8;
const int ledGreen = 9;
const int buttonYellow = 10;
const int ledYellow = 11;
const int buttonRed = 12;
const int ledRed = 13;

const int lowSpeed = 85;
const int mediumSpeed = 170;
const int highSpeed = 255;

int speed = 0;


enum MotorState { MOTOR_OFF, MOTOR_ON };
enum LedState { RED, YELLOW, GREEN };

MotorState motorState = MOTOR_OFF;
LedState ledState = RED;

void setup() {
  pinMode(servoPin, OUTPUT);
  pinMode(motorPin, OUTPUT);
  pinMode(buttonGreen, INPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(buttonYellow, INPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(buttonRed, INPUT);
  pinMode(ledRed, OUTPUT);

  servo.attach(servoPin);
}

void loop() {
  //Machine 1: Mirror potentiometer to servo motor.
  servo.write(map(analogRead(potPin), 0, 1023, 0, 179));

  //Machine 2: Start and stop DC motor using the piezo.
  if (motorState == MOTOR_OFF){
    analogWrite(motorPin, 0);
    if (analogRead(piezoPin) > 100){
      motorState = MOTOR_ON;
    }
  } else if (motorState == MOTOR_ON){
    analogWrite(motorPin, speed);
    delay(5000);
    motorState = MOTOR_OFF;
  }

  //Machine 3: Read the buttons to set the LEDs and the DC motor speed.
  if (ledState == RED){
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledYellow, LOW);
    digitalWrite(ledGreen, LOW);  
    speed = lowSpeed;
    if (digitalRead(buttonYellow) == HIGH){
      ledState = YELLOW;      
    } else if (digitalRead(buttonGreen) == HIGH){
      ledState = GREEN;
    }
  } else if (ledState == YELLOW){
    digitalWrite(ledRed, LOW);
    digitalWrite(ledYellow, HIGH);
    digitalWrite(ledGreen, LOW);  
    speed = mediumSpeed;
    if (digitalRead(buttonRed) == HIGH){
      ledState = RED;      
    } else if (digitalRead(buttonGreen) == HIGH){
      ledState = GREEN;
    }
  } else if (ledState == GREEN){
    digitalWrite(ledRed, LOW);
    digitalWrite(ledYellow, LOW);
    digitalWrite(ledGreen, HIGH);  
    speed = highSpeed;
    if (digitalRead(buttonYellow) == HIGH){
      ledState = YELLOW;      
    } else if (digitalRead(buttonRed) == HIGH){
      ledState = RED;
    }
  }

}