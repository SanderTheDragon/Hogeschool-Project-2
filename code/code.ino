const int sensor1Trigger = 2;
const int sensor1Echo = 3;
const int sensor2Trigger = 4;
const int sensor2Echo = 5;

void setup()
{
  Serial.begin (9600);
  
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
}

void goLeft()
{
  
}

void goRight()
{
  
}

void driveForwards()
{
  
}

void driveBackwards()
{
  
}

