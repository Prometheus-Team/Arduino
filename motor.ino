#define enLeft 6
#define inLeft1 13
#define inLeft2 12

#define enRight 5
#define inRight1 7
#define inRight2 8

// Left motor direction and speed adjustment
void moveMotor(float speedL, float speedR){
  if(speedL == 0){
    digitalWrite(inLeft1, LOW);
    digitalWrite(inLeft2, LOW);
  } else if(speedL > 0){
    digitalWrite(inLeft1, LOW);
    digitalWrite(inLeft2, HIGH);  
  } else{
    digitalWrite(inLeft1, HIGH);
    digitalWrite(inLeft2, LOW);  
  }

  if(speedR == 0){
    digitalWrite(inRight1, LOW);
    digitalWrite(inRight2, LOW);
  } else if(speedR > 0){
    digitalWrite(inRight1, LOW);
    digitalWrite(inRight2, HIGH);  
  } else{
    digitalWrite(inRight1, HIGH);
    digitalWrite(inRight2, LOW);  
  }

  analogWrite(enLeft, abs(speedL)); // Send PWM signal to left motor
  analogWrite(enRight, abs(speedR)); // Send PWM signal to right motor
 }


void motorSetup() {
  pinMode(enLeft, OUTPUT);
  pinMode(inLeft1, OUTPUT);
  pinMode(inLeft2, OUTPUT);
  
  pinMode(enRight, OUTPUT);
  pinMode(inRight1, OUTPUT);
  pinMode(inRight2, OUTPUT);
}
