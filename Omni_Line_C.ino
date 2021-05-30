#include <STTODRobot.h>
STTODRobot myOmni = STTODRobot();

int ss[16] =   {A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15};
double irAngle[16] = {0, 22.5, 45, 67.5, 90, 112.5, 135, 157.5, 190, 202.5, 225, 247.5, 290, 292.5, 315 , 337.5 };

int IN1  = 22;
int IN2 = 23;
int IN3  = 24;
int IN4 = 25;
int IN5  = 26;
int IN6 = 27;
int EN1 = 5;
int EN2 = 6;
int EN3 = 7;

const int irThreshold = 200;
const int angleRange = 60;  // degrees
const int delayDuration = 5;
int angle = 0;
double newAngle = 0;
int count = 0;

void setup() {
  myOmni.init(IN1,  IN2,  EN1,  IN3,  IN4,  EN2,  IN5,  IN6,  EN3);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(IN5, OUTPUT);
  pinMode(IN6, OUTPUT);
  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);
  pinMode(EN3, OUTPUT);

//Rotate Omni: true (clockwise), false (anti-clockwise)  
  myOmni.rotate_omni(true, 150);
   delay (1000);
  myOmni.stop_omni();
   delay (1000);

  myOmni.move_omni(0, 200);
}

void loop() {
  find_angle();
  if(count != 0){
    newAngle = (int)(newAngle * 1.0 / count); 
    if(newAngle < 0)
      newAngle += 360;
    angle = round(newAngle);
    myOmni.move_omni(angle, 200);
    delay(delayDuration);
  }
  else 
    delay(delayDuration);
  count = 0;
  newAngle = 0;
}    

void find_angle(void){
  int minAngle = angle - angleRange;
  if(minAngle < 0) 
    minAngle += 360;    
  int maxAngle = angle + angleRange;
  if(maxAngle >= 360)
    maxAngle -= 360;
  int value;
  if(minAngle < maxAngle) {    
    for(int i = 0; i < 16; i++) {
      if(irAngle[i] >= minAngle && irAngle[i] <= maxAngle) {
        value = analogRead(ss[i]);
        if(value > irThreshold) {
          newAngle += irAngle[i];
          count++;          
        } 
      }     
    }
  }
  else {
    for(int i = 0; i < 16; i++) {
      if(irAngle[i] >= minAngle || irAngle[i] <= maxAngle) {
        value = analogRead(ss[i]);
        if(value > irThreshold) {
          if(irAngle[i] <= maxAngle)
            newAngle += irAngle[i];
          else
            newAngle += (irAngle[i] - 360);
          count++;
        } 
      }       
    }
  }
}
//Code 2018 

