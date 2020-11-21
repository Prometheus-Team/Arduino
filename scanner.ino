#include <Servo.h>
#include <std_msgs/Int32.h>

// Servo for rotating ultrasonic to scan area
Servo sensorRotate;
#define sensorServoPin 11

// Ultrasonic sensor data
// defines pins numbers
#define trigPin 9
#define echoPin 10

#define delayTime 45

// defines variables
long duration;
int distance;


// ===========================================================
// ************** Servo and ultrasonic definations ***********
// ===========================================================


float readUltrasonicDistance() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;

  return distance;
}

// Rotate servo motor slowly 180 degrees to scan the area
void scanArea(int steps) {
  float dis = 0;
  int pos = 0;

  for (pos = 90; pos >= 0; pos -= 2) { // goes from 180 degrees to 0 degrees
    sensorRotate.write(pos);              // tell servo to go to position in variable 'pos'
    delay(delayTime);                       // waits 15ms for the servo to reach the position
//    dis = readUltrasonicDistance();
//    publishRange(dis, pos);
  }
  delay(delayTime);

  for (pos = 0; pos <= 180; pos += steps) { // goes from 0 degrees to 180 degrees
    // in steps of 2 degree    
    sensorRotate.write(pos);              // tell servo to go to position in variable 'pos'
    delay(delayTime);                       // waits 100ms for the servo to reach the position
    dis = readUltrasonicDistance();

    if(pos + steps > 180){
      publishRange(dis, pos, 1);  
    }else{
      publishRange(dis, pos, 0);
    }
  }
  delay(delayTime);

  for (pos = 180; pos >= 90; pos -= 2) { // goes from 180 degrees to 0 degrees
    sensorRotate.write(pos);              // tell servo to go to position in variable 'pos'
    delay(delayTime);                       // waits 15ms for the servo to reach the position
//    dis = readUltrasonicDistance();
//    publishRange(dis, pos);
  }
  delay(delayTime);
}

void publishRange(float dis, int pos, int last) {
  range.range = dis;
  range.field_of_view = pos;
  range.radiation_type = last;
  pubRange.publish(&range);
}

void checkObstacle() {
  float d = readUltrasonicDistance();

  if (d < 50) {
    publishRange(d, 90, 0);
  }
}

// *********** Servo and ultrasonic end ************************
// =============================================================

void scannerSetup() {
  // Servo motor
  sensorRotate.attach(sensorServoPin);

  // make the starting angle of the servo to 90  degree
  sensorRotate.write(90);

  // Ultrasonic sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
