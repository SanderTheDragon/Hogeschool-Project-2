#include <NewPing.h>
#include <CustomStepper.h>

const int sensor1Trigger = 5;
const int sensor1Echo = 4;
const int sensor2Trigger = 2;
const int sensor2Echo = 3;
const int sensor3Trigger = 0;
const int sensor3Echo = 1;

const int stepper1Pins[4] = { 6, 7, 8, 9 };
const int stepper2Pins[4] = { 10, 11, 12, 13 };

CustomStepper stepper1(stepper1Pins[0], stepper1Pins[1], stepper1Pins[2], stepper1Pins[3], (byte[]){8, B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001});
CustomStepper stepper2(stepper2Pins[0], stepper2Pins[1], stepper2Pins[2], stepper2Pins[3], (byte[]){8, B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001});

NewPing sensor1(sensor1Trigger, sensor1Echo, 200);
NewPing sensor2(sensor2Trigger, sensor2Echo, 200);
NewPing sensor3(sensor3Trigger, sensor3Echo, 200);

int distance1 = 0, distance2 = 0, distance3 = 0, leftSteps = 0, rightSteps = 0, straightSteps = 12, straightstepsbefore = 0, backSteps = 0;
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
  pinMode(sensor3Trigger, OUTPUT);
  pinMode(sensor3Echo, INPUT);
}

void loop()
{
  if (reqDistance)
  {
    distance1 = sensor1.ping_cm();
    distance2 = sensor2.ping_cm();
    distance3 = sensor3.ping_cm();
    
    if (distance1 == 0)
    {
      distance1 = 10;
    }
    
    if (distance2 == 0)
    {
      distance2 = 200;
    }

    //Serial.print("Sensor 1: ");
    //Serial.println(distance1);
    
    //Serial.print("Sensor 2: ");
    //Serial.println(distance2);

    if (backSteps > 0)
      goBack();
    else if (straightstepsbefore > 0 && rightSteps <= 0)
      goStraight();
    else if (rightSteps > 0)
      goRight();
    else if (leftSteps > 0)
      goLeft();
    else if (straightSteps > 0)
    {
      goStraight();
    
      if (distance1 < 5)
      {
        leftSteps = 35;
        straightSteps = 36;
      }
    }
    else
    {
      
    if (distance3 > 10)
    {
      backSteps = 32;
      leftSteps = 35;
    } else if (distance2 > 10)
      {
        straightstepsbefore = 5;
        rightSteps = 35;
        straightSteps = 72;
      } else if ((distance1 < 5) && distance2 < 10)
      {
        straightstepsbefore = 5;
        leftSteps = 35;
        straightSteps = 72;
      } else if (distance1 > 5 && distance2 < 10)
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
  
  straightstepsbefore--;
  straightSteps--;
}

void goBack()
{
  stepper1.setDirection(CCW);
  stepper2.setDirection(CW);

  stepper1.rotateDegrees(5);
  stepper2.rotateDegrees(5);

  backSteps--;
}



