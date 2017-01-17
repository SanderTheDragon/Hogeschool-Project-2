#include <CustomStepper.h>

const int sensor1Trigger = 2;
const int sensor1Echo = 3;
const int sensor2Trigger = 4;
const int sensor2Echo = 5;

const int stepper1Pins[4] = { 6, 7, 8, 9 };
const int stepper2Pins[4] = { 10, 11, 12, 13 };

CustomStepper stepper1(stepper1Pins[0], stepper1Pins[1], stepper1Pins[2], stepper1Pins[3], (byte[]){8, B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001});
CustomStepper stepper2(stepper2Pins[0], stepper2Pins[1], stepper2Pins[2], stepper2Pins[3], (byte[]){8, B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001});

void setup()
{
  //Serial.begin(9600);

  stepper1.setRPM(15);
  stepper1.setSPR(4075.7728395);
  
  stepper2.setRPM(15);
  stepper2.setSPR(4075.7728395);
  
  pinMode(sensor1Trigger, OUTPUT);
  pinMode(sensor1Echo, INPUT);
  pinMode(sensor2Trigger, OUTPUT);
  pinMode(sensor2Echo, INPUT);
}

void loop()
{
  if (getDistance1() < 10)
  {
    driveStop();
    driveBackwards();
  }
  else
  {
    driveStop();
    driveForwards();
  }
  
  stepper1.run();
  stepper2.run();
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
  
  //Serial.print("Sensor 1: ");
  //Serial.print(distance);
  //Serial.print("\n");

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
  
  //Serial.print("Sensor 2: ");
  //Serial.print(distance);
  //Serial.print("\n");

  return distance;
}

void motorLeft(int direction)
{
  if (stepper1.isDone())
  {
    //Serial.print("Motor left: ");
    //Serial.print(direction);
    //Serial.print("\n");
    
    stepper1.setDirection(CW);
    
    if (direction < 0)
      stepper1.setDirection(CCW);

    if (direction == 0)
    {
      stepper1.setDirection(STOP);
      return;
    }
    
    stepper1.rotate(1);
  }
}

void motorRight(int direction)
{
  if (stepper2.isDone())
  {
    //Serial.print("Motor right: ");
    //Serial.print(direction);
    //Serial.print("\n");
    
    stepper2.setDirection(CW);
    
    if (direction < 0)
      stepper2.setDirection(CCW);
    
    if (direction == 0)
    {
      stepper2.setDirection(STOP);
      return;
    }
     
    stepper2.rotate(1);
  }
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
  //Serial.println("Forwards");
  
  motorLeft(-1);
  motorRight(1);
}

void driveBackwards()
{
  //Serial.println("Backwards");
  
  motorLeft(1);
  motorRight(-1);
}

void driveStop()
{
  motorLeft(0);
  motorRight(0);
}

