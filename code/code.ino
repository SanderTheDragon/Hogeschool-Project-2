#include <Stepper.h>

const int sensor1Trigger = 2;
const int sensor1Echo = 3;
const int sensor2Trigger = 4;
const int sensor2Echo = 5;

const int stepper1Pins[4] = { 6, 7, 8, 9 };
const int stepper2Pins[4] = { 10, 11, 12, 13 };

const int stepsPerMotorRev = 32;
const int stepsPerOutputRev = stepsPerMotorRev * 64;

Stepper stepper1(stepsPerMotorRev, stepper1Pins[0], stepper1Pins[1], stepper1Pins[2], stepper1Pins[3]);
Stepper stepper2(stepsPerMotorRev, stepper2Pins[0], stepper2Pins[1], stepper2Pins[2], stepper2Pins[3]);

void setup()
{
  Serial.begin(9600);
  
  pinMode(sensor1Trigger, OUTPUT);
  pinMode(sensor1Echo, INPUT);
  pinMode(sensor2Trigger, OUTPUT);
  pinMode(sensor2Echo, INPUT);
}

void loop()
{
  getDistance1();
  getDistance2();
  delay(1000);
}

int getDistance1()
{
  digitalWrite(sensor1Trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(sensor1Trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(sensor1Trigger, LOW);
  
  int duration = pulseIn(sensor1Echo, HIGH);
  int distance = duration / 58.2;
  
  if (distance > 200 || distance < 0)
    distance = -1;
  
  Serial.print("Sensor 1: ");
  Serial.print(distance);
  Serial.print("\n");

  return distance;
}

int getDistance2()
{
  digitalWrite(sensor2Trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(sensor2Trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(sensor2Trigger, LOW);
  
  int duration = pulseIn(sensor2Echo, HIGH);
  int distance = duration / 58.2;
  
  if (distance > 200 || distance < 0)
    distance = -1;
  
  Serial.print("Sensor 2: ");
  Serial.print(distance);
  Serial.print("\n");

  return distance;
}

void motorLeft(int direction, int time = 1000)
{
  int steps = stepsPerOutputRev * direction;
  stepper1.setSpeed(640);
  stepper1.step(steps);
  delay(time);
}

void motorRight(int direction, int time = 1000)
{
  int steps = stepsPerOutputRev * direction;
  stepper2.setSpeed(640);
  stepper2.step(steps);
  delay(time);
}

void goLeft()
{
  motorLeft(-1);
  motorRight(1);
}

void goRight()
{
  motorLeft(1);
  motorRight(-1);
}

void driveForwards()
{
  motorLeft(1);
  motorRight(1);
}

void driveBackwards()
{
  motorLeft(-1);
  motorRight(-1);
}

