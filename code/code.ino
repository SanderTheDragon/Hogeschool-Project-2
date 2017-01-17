#include <NewPing.h>
#include <CustomStepper.h>

const int sensor1Trigger = 2;
const int sensor1Echo = 3;
const int sensor2Trigger = 4;
const int sensor2Echo = 5;

const int stepper1Pins[4] = { 6, 7, 8, 9 };
const int stepper2Pins[4] = { 10, 11, 12, 13 };

CustomStepper stepper1(stepper1Pins[0], stepper1Pins[1], stepper1Pins[2], stepper1Pins[3], (byte[]){8, B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001});
CustomStepper stepper2(stepper2Pins[0], stepper2Pins[1], stepper2Pins[2], stepper2Pins[3], (byte[]){8, B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001});

NewPing sensor1(sensor1Trigger, sensor1Echo, 200);
NewPing sensor2(sensor2Trigger, sensor2Echo, 200);

int distance1 = 0, distance2 = 0;
bool reqDistance = true;

void setup()
{
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

    if (distance1 < 10)
    {
      stepper1.setDirection(CCW);
      stepper2.setDirection(CW);
      
      stepper1.rotateDegrees(5);
      stepper2.rotateDegrees(5);
    }
    else
    {
      if (distance2 > 10)
      {
        stepper1.setDirection(CW);
        stepper2.setDirection(CW);
        
        stepper1.rotateDegrees(5);
        stepper2.rotateDegrees(5);
      }
      else
      {
        stepper1.setDirection(CW);
        stepper2.setDirection(CCW);
        
        stepper1.rotateDegrees(5);
        stepper2.rotateDegrees(5);
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
