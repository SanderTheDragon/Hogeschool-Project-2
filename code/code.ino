#include <Servo.h>
#define trigPin1 7
#define echoPin1 6
#define trigPin2 11
#define echoPin2 10
#define trigPin3 9
#define echoPin3 8
int centerint = 0;
Servo left;
Servo right;

void setup() {
  Serial.begin (9600);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  left.attach(3);
  right.attach(5);
  Stop();
  delay(3000);

}

void debug(int distanceFront, int distanceLeft, int distanceDown){
  Serial.print("F: ");
  Serial.print(distanceFront);
  Serial.print(" L: ");
  Serial.print(distanceLeft);
  Serial.print(" D: ");
  Serial.print(distanceDown);
  Serial.println(" ");
}

void loop() {
  delay(20);

  if ((sensorVoor() >= 10 && sensorOnder() < 9) || sensorLinks() > 13) {
   Serial.println("geen muur geen afgrond");
    if (sensorLinks() <= 13 && sensorVoor() >= 10) { //muur links. 13
      center();
    }

    else if (sensorLinks() > 13) { //geen muur links.
      Serial.println("links > 13");
      int i = 0;
      while(i <= 5){
        vooruit();
        delay(80);
        if (sensorOnder() >= 9){
          achteruit();
          delay(500);
          turnRightAfgrond();
        }
        i++;
      }
      
      i=0;
      turnLeft();
       while(i <= 5){
        vooruit();
        delay(80);
        if (sensorOnder() >= 9){
          achteruit();
          delay(500);
          turnRightAfgrond();
        }
        i++;
      }
      
    }
  }

  if (sensorOnder() >= 15){
    Serial.println("DEPRESSION");
    achteruit();
      delay(500);
      turnRightAfgrond();
              Serial.println("muur suicide");
        slideR();
        delay(2000);
        achteruit();
        delay(300);
        turnRight();
  }
  

  if ((sensorVoor() <= 10 || sensorOnder() >= 9) && sensorLinks() <= 12 ) { //muur of afgrond en muur links.
    Serial.println("te lange shit");
    int i = 0;
    if (sensorOnder() >= 9) { //indien afgrond ga eerst achteruit.
      achteruit();
      delay(500);
      i = 1;
    }
    
    if (i == 0){
      turnRight();
    } else{ 
      turnRightAfgrond();
              Serial.println("muur suicide");
        slideR();
        delay(2000);
        achteruit();
        delay(300);
        turnRight();
        i = 0;
    }

    if (sensorVoor() > 8) { //rij tegen de muur aan die aan de rechterkant van de greppel staat.
      
      if (i == 0){
      vooruit();
      delay(200);
      }
      if (i == 1) {
        Serial.println("muur suicide");
        slideR();
        delay(2000);
        achteruit();
        delay(300);
        turnRight();
      }
    }
    else if (sensorVoor() <= 5) { //indien de robot bij de muur is gekomen, draai nog een keer rechts. 8
      //Serial.println("s <= 5");
      turnRight();
    }
  }

}

int sensorVoor() {             
  int duration, distance;
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration = pulseIn(echoPin1, HIGH);
  distance = (duration / 2) / 29.1;
  
      Serial.println("sensor voor");
      Serial.println(distance);
  if (distance < 0) { //indien distance negatief is.
    distance = 13;
  }
  return distance;
}

double sensorOnder() {               
  int duration, distance;
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration = pulseIn(echoPin2, HIGH);
  distance = (duration / 2) / 29.1;

      Serial.println("sensor onder");
      Serial.println(distance);
  if (distance < 0) { //indien distance negatief is.
    distance = 5;       //10
  }
  return distance;
}


int sensorLinks() {             
  int duration, distance;
  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);
  duration = pulseIn(echoPin3, HIGH);
  distance = (duration / 2) / 29.1;

      Serial.println("sensor links");
      Serial.println(distance);
  if (distance < 0) { //indien distance negatief is.
    distance = 0;
  }
  return distance;
}

void vooruit() {
  left.writeMicroseconds(1570);
  right.writeMicroseconds(1400);
}
void Stop() {
  left.writeMicroseconds(1532);
  right.writeMicroseconds(1505);
}
void achteruit() {
  left.writeMicroseconds(1500);
  right.writeMicroseconds(1900);
}

void turnRight() {
  if (sensorVoor() < 5){
  achteruit();
  delay(200);
  }
  left.writeMicroseconds(1570);
  right.writeMicroseconds(1590);
  delay(585);
  left.writeMicroseconds(1532);
  right.writeMicroseconds(1505);
  delay(450);
}

void turnRightAfgrond() {
  left.writeMicroseconds(1570);
  right.writeMicroseconds(1590);
  delay(585);
  left.writeMicroseconds(1532);
  right.writeMicroseconds(1505);
  delay(450);
}

void turnLeft() {
  if (sensorVoor() < 5){
  achteruit();
  delay(200);
  }
  left.writeMicroseconds(1500);
  right.writeMicroseconds(0);
  delay(525);
  left.writeMicroseconds(1532);
  right.writeMicroseconds(1505);
  delay(550);
}

void checkDL() { // afwijken naar links
  left.writeMicroseconds(1550);
  right.writeMicroseconds(40);
}

void checkDR() { // afwijken naar rechts
  left.writeMicroseconds(1580);
  right.writeMicroseconds(300);
}

void slideR() { // afwijken naar rechts, voor afgrond gebruiken
  left.writeMicroseconds(1590);
  right.writeMicroseconds(600);
}

void center() {
  Serial.println("centerint");
  Serial.println(centerint);
  if (sensorLinks() < 7) {
    checkDR();
    centerint = 0;
  }
  else if (sensorLinks() >= 7 && centerint <= 0) {
    checkDL();
    centerint = 5;
  } else {
    vooruit();
    centerint--;
  
  }
}
