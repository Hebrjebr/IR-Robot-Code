/*
==INTERFERENCE_ROAMING==
- This program should have the robot roam EXCEPT:
  - When IR interference has been detected, sound an alarm very briefly.
  - Then continue roaming.
==END COMMENT CODE==
*/

#include <Servo.h>
Servo servoLeft;
Servo servoRight;

//initialization code
void setup(){
  //PIN assignment
  pinMode(10, INPUT); pinMode(9, OUTPUT);
  pinMode(3, INPUT); pinMode(2, OUTPUT);
  pinMode(8, OUTPUT); pinMode(7, OUTPUT);
  
  tone(4, 3000, 1000);
  delay(1000);
  //attach servos
  servoLeft.attach(13);
  servoRight.attach(12);
}

//loop code
void loop(){
  //initiate interference detection
  int irLeft = digitalRead(10);
  int irRight = digitalRead(3);
  
  if((irLeft == 0) || (irRight == 0)){
    for(int i = 0; i <= 5; i++){
      digitalWrite(7, HIGH);
      digitalWrite(8, HIGH);
      tone(4, 4000, 10);
      delay(20);
      digitalWrite(7, LOW);
      digitalWrite(8, LOW);
    }
  }
  //initiate roaming agenda
  irLeft = irDetect(9, 10, 38000);
  irRight = irDetect(2, 3, 38000);
  
  if((irLeft == 0) && (irRight == 0)){
    maneuver(-200, -200, 50);
  } else if(irLeft == 0){
    maneuver(200, -200, 50);
  } else if(irRight == 0){
    maneuver(-200, 200, 50);
  } else {
    maneuver(200, 200, 50);
  }
}

//FUNCTION: IRDETECT
int irDetect(int irLedPin, int irReceiverPin, long frequency){
  tone(irLedPin, frequency, 8);
  delay(1);
  int ir = digitalRead(irReceiverPin);
  delay(1);
  return ir;
}

//FUNCTION: MANEUVER
void maneuver(int speedLeft, int speedRight, int msTime){
  servoLeft.writeMicroseconds(1500 + speedLeft);
  servoRight.writeMicroseconds(1500 - speedRight);
  if(msTime == 1){
    servoLeft.detach();
    servoRight.detach();
  }
  delay(msTime);
}
