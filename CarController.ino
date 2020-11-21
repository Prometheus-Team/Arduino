/*
* Publisher - Range scanner - sensor_msgs/Range - /arduino/range
*           - Tachometer Left - std_msgs/Float32 - /arduino/speed/left
*           - Tachometer Right - std_msgs/Float32 - /arduino/speed/right
* Subscriber - Scanner servo - std_msgs/Empty - /arduino/scanCmd
*            - DC motor Left - std_msgs/Float32 - /arduino/speed/leftCmd
*            - DC motor Right - std_msgs/Float32 - /arduino/speed/rightCmd
*/

#include <ros.h>
#include <geometry_msgs/Point.h>
#include <std_msgs/Empty.h>
#include <std_msgs/String.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Int32.h>
#include <sensor_msgs/Range.h>


// ===========================================================
// ************** ROS related definations ********************
// ===========================================================
// Define ROS handler
ros::NodeHandle nh;

// ******************* Publisher ********************************
// variables to publish data
std_msgs::Float32 speedLeft;
std_msgs::Float32 speedRight;
std_msgs::Int32 stepLeft;
std_msgs::Int32 stepRight;
std_msgs::Float32 distanceToObstacle;
sensor_msgs::Range range;

// define publisher with name and varible 
ros::Publisher pubSpeedLeft("/arduino/speed/left", &speedLeft);
ros::Publisher pubSpeedRight("/arduino/speed/right", &speedRight);
ros::Publisher pubStepLeft("/arduino/step/left", &stepLeft);
ros::Publisher pubStepRight("/arduino/step/right", &stepRight);
ros::Publisher pubRange("/arduino/range", &range);
ros::Publisher pubObstacleDistance("/arduino/obstacleDistance", &distanceToObstacle);

// ---------------------------------------------------------------

bool inMotion = false;

// **************** Subscriber *********************************
// functions to handle subscriber calls
void subScannerHandler(const std_msgs::Int16& steps){
  scanArea(steps.data);
}
void subMotorHandler(const geometry_msgs::Point& motorSpeed){
  moveMotor(motorSpeed.x, motorSpeed.y);  
  if(motorSpeed.x>0 && motorSpeed.y>0){
    inMotion = true;  
  } else{
    inMotion = false;
  }
}

// define subscriber with name and corresponding function
ros::Subscriber<std_msgs::Int16> subScanner("/arduino/scanCmd", &subScannerHandler);
ros::Subscriber<geometry_msgs::Point> subSpeed("/arduino/speedCmd", &subMotorHandler);

// ---------------------------------------------------------------------

// =================================================================
int l = 0;
void setup() {

  // put your setup code here, to run once:
  scannerSetup();
  tachometerSetup();
  motorSetup();

  nh.initNode();

  // Advertise publishers
  nh.advertise(pubRange);
  nh.advertise(pubSpeedLeft);
  nh.advertise(pubSpeedRight);
  nh.advertise(pubStepLeft);
  nh.advertise(pubStepRight);
  nh.advertise(pubObstacleDistance);

  // Register subscribers
  nh.subscribe(subScanner);
  nh.subscribe(subSpeed);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (inMotion==true){
    tachometerLoop();  
  }
  
  nh.spinOnce();
  
  delay(5);
}
