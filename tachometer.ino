#define wheelRadius 0.033
#define calcSpeedEvery 20

int leftIntr = 0;
int rightIntr = 0;
float rotLeft, rotRight, rpmLeft, rpmRight, prvTimeLeft, prvTimeRight;

// Left motor tachometer interrupt handler
void leftIntrHandler() {
  leftIntr++;
  rotLeft++;

  int dtime = millis();

  if (rotLeft >= calcSpeedEvery) {
    int timeTaken = millis() - prvTimeLeft;
    //float timeTakenInMin = ((millis() - prvTimeLeft) / (60 * 1000));
    rpmLeft = (1000.0 / timeTaken)*60;
    prvTimeLeft = millis();
    rotLeft = 0;

//    publishLeftSpeed(rpmLeft);
  }

//  publishLeftStep();
}

// Left motor tachometer speed publisher to ROS
void publishLeftSpeed(){
  speedLeft.data = calculateSpeed(rpmLeft);
  
  pubSpeedLeft.publish( &speedLeft);

  // Send current distance from obstacle infront 
  readFrontDistance();
}

// Right motor tachometer interrupt handler
void rightIntrHandler() {
  rightIntr++;
  rotRight++;

  int dtime = millis();

  if (rotRight >= calcSpeedEvery) {
    int timeTaken = millis() - prvTimeRight;
//    float timeTakenInMin = ((millis() - prvTimeRight) / (60 * 1000));
    rpmRight = (1000.0 / timeTaken)*60;
    prvTimeRight = millis();
    rotRight = 0;

//    publishRightSpeed(rpmRight);
  }

//  publishRightStep();
}

// Right motor tachometer speed publisher to ROS
void publishRightSpeed(){
  speedRight.data = calculateSpeed(rpmRight);
  
  pubSpeedRight.publish( &speedRight);
  
  // Send current distance from obstacle infront 
  readFrontDistance();
}

// Right motor tachometer speed publisher to ROS
void publishLeftStep(){
  stepLeft.data = leftIntr;
  pubStepLeft.publish( &stepLeft);
}

// Right motor tachometer speed publisher to ROS
void publishRightStep(){
  stepRight.data = rightIntr;
  pubStepRight.publish( &stepRight);
}

void readFrontDistance(){
  // Send current distance from obstacle infront 
  distanceToObstacle.data = readUltrasonicDistance
  ();  
  pubObstacleDistance.publish(&distanceToObstacle);
}

float calculateSpeed(float rpm){
  return (wheelRadius * rpm * 0.104);  
}

// Initial setup for the tachometers
void tachometerSetup() {
  rotLeft = rotRight = rpmLeft = rpmRight = prvTimeLeft = prvTimeRight = 0;

  attachInterrupt(digitalPinToInterrupt(3), leftIntrHandler, CHANGE);
  attachInterrupt(digitalPinToInterrupt(2), rightIntrHandler, CHANGE);
}

void tachometerLoop(){
  publishLeftSpeed();
  publishRightSpeed();
  publishRightStep();
  publishLeftStep();
}
