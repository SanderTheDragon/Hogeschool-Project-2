#include <NewPing.h>
#include <CustomStepper.h>

const int sensor1Trigger = 2;
const int sensor1Echo = 3;
const int sensor2Trigger = 5;
const int sensor2Echo = 4;

const int stepper1Pins[4] = { 6, 7, 8, 9 };
const int stepper2Pins[4] = { 10, 11, 12, 13 };

CustomStepper stepper1(stepper1Pins[0], stepper1Pins[1], stepper1Pins[2], stepper1Pins[3], (byte[]){8, B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001});
CustomStepper stepper2(stepper2Pins[0], stepper2Pins[1], stepper2Pins[2], stepper2Pins[3], (byte[]){8, B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001});

NewPing sensor1(sensor1Trigger, sensor1Echo, 200);
NewPing sensor2(sensor2Trigger, sensor2Echo, 200);

int distance1 = 0, distance2 = 0, leftSteps = 0, rightSteps = 0, straightSteps = 0;
bool reqDistance = true;

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
  if (reqDistance)
  {
    distance1 = sensor1.ping_cm();
    distance2 = sensor2.ping_cm();
    
    if (distance1 == 0)
    {
      distance1 = 0;
    }
    
    if (distance2 == 0)
    {
      distance2 = 200;
    }

    //Serial.print("Sensor 1: ");
    //Serial.println(distance1);
    
    //Serial.print("Sensor 2: ");
    //Serial.println(distance2);

    if (rightSteps > 0)
      goRight();
    else if (leftSteps > 0)
      goLeft();
    else if (straightSteps > 0)
      goStraight();
    else
    {
      if ((distance1 < 5 || distance1 > 10) && distance2 < 10)
      {
        leftSteps = 35;
        straightSteps = 72;
      }
      
      if (distance2 > 10)
      {
        rightSteps = 35;
        straightSteps = 72;
      }
      
      if (distance1 > 5 && distance2 < 10)
      {
        goStraight();
      }
    }
    
    reqDistance = false;
  }

  if (stepper1.isDone() && stepper2.isDone())
  {
    reqDistance = true;
  }
  
  stepper1.run();
  stepper2.run();
}

void goRight()
{
  stepper1.setDirection(CCW);
  stepper2.setDirection(CCW);
  
  stepper1.rotateDegrees(5);
  stepper2.rotateDegrees(5);

  rightSteps--;
}

void goLeft()
{
  stepper1.setDirection(CW);
  stepper2.setDirection(CW);
     
  stepper1.rotateDegrees(5);
  stepper2.rotateDegrees(5);

  leftSteps--;
}

void goStraight()
{
  stepper1.setDirection(CW);
  stepper2.setDirection(CCW);
        
  stepper1.rotateDegrees(5);
  stepper2.rotateDegrees(5);

  straightSteps--;
}


